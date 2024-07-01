/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:05:03 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/21 16:12:01 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int Server::_serverPort;
int Server::_socketDescriptor;
pollfd *Server::_pollfd;
sockAddrIn Server::_serverAddr;
std::string Server::_password;

std::vector<pollfd> Server::_activeConnections;
std::vector<Client> Server::_clients;
std::vector<Channel> Server::_channels;

Server::Server() {
	_activeConnections.reserve(100);
}

Server::~Server() {}

void	Server::setPort(char *input)
{
	int port = std::atoi(input);

	if (port <= 0 || port > MAX_PORT_NUMBER)
		throw std::logic_error("Invalid port number");
	_serverPort = port;
}

std::string Server::getPassword()
{
	return (Server::_password);
}

static bool isPrintable(const std::string &s) {
	for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
		if (!std::isprint(static_cast<unsigned char>(*it))) {
			return false;
		}
	}
	return true;
}

void Server::setPassword(char *password)
{
	if (!isPrintable(password) || !password[0])
		throw std::logic_error("Invalid password");
	Server::_password = std::string(password);
}

void Server::bindSocketToAddress() {
	if (bind(Server::_socketDescriptor, (sockAddr *) &_serverAddr, sizeof(_serverAddr)) < 0)
		throw std::runtime_error("Failed to bind server fd to socket");
};

void Server::createSocket() {
	const int	ENABLE = 1;

	Server::_socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (Server::_socketDescriptor < 0)
		throw std::runtime_error("Socket creation failed");

	if (setsockopt(Server::_socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) < 0)
		throw std::runtime_error("It was not possible to set socket options");

	if (fcntl(Server::_socketDescriptor, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("It was not possible to set the non-blocking mode on socket fd");
};


void Server::configureAddress() {

	std::memset(&_serverAddr, 0, sizeof(_serverAddr));

	_serverAddr.sin_family = AF_INET;

	_serverAddr.sin_addr.s_addr = INADDR_ANY;

	_serverAddr.sin_port = htons(_serverPort);
};


void Server::listenForClients() {
	if(listen(Server::_socketDescriptor, CLIENT_LIMIT) == -1)
		throw std::runtime_error("Failed to listen on socket");
};

void Server::sigHandler(int)
{
	close(Server::_socketDescriptor);
	throw std::runtime_error("\nServer stopped due to SIGINT");
}

Server& Server::getInstance() {

	static Server instance;

	return instance;
};


void Server::setUpTCP() {
	LOG("The server is being set up...")
	createSocket();
	configureAddress();
	bindSocketToAddress();
	listenForClients();
	LOG("Server was properly set up")
};

void	Server::pollActiveConnections(void) {
	int activity = poll(_activeConnections.data(), _activeConnections.size(), TIMEOUT_MS);
	if (activity < 0)
		throw std::runtime_error("Polling error");
};

void	Server::acceptNewClients(void) {
	if ((Server::_activeConnections[0].revents & POLLIN) == POLLIN)
	{
		sockAddrIn newClientAddress;
		socklen_t addressLength = sizeof(newClientAddress);

		int newClientSocketDescriptor = accept(_socketDescriptor, (sockAddr *) &newClientAddress, &addressLength);

		if (newClientSocketDescriptor < 0)
			throw std::runtime_error("Unable to accept new client connection");

		if (fcntl(newClientSocketDescriptor, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Failed to set client's socket fd to non-blocking mode");

		_activeConnections.push_back((pollfd) {.fd = newClientSocketDescriptor, .events = POLLIN});

		Client newClient(newClientSocketDescriptor);
		_clients.push_back(newClient);
	}
};

std::ostream &operator<<(std::ostream &oss, std::queue<std::string> queue) {
	if (queue.empty()) {
		oss << "Queue is empty!";
		return oss;
	}
	for (size_t i = 0; i < queue.size(); i++) {
		oss << "[" << i << "] " << queue.front() << std::endl;
		queue.pop();
	}
	return oss;
}

bool operator==(const pollfd &pollfd, const int &clientFd) {
	return (pollfd.fd == clientFd);
}

bool Server::detectedActivity(const int &clientFd) {
	std::vector<pollfd>::iterator pollfd =
		std::find(_activeConnections.begin(), _activeConnections.end(), clientFd);
	return ((pollfd->revents & POLLIN) == POLLIN);
}

void Server::disconnectClient(const Client &client, const int &clientPosition) {

	for (size_t i = 0; i < _channels.size(); i++)
		_channels[i].removeClient(client);

	close(client.getFd());

	_activeConnections.erase(std::find(_activeConnections.begin(), _activeConnections.end(), client.getFd()));

	_clients.erase(_clients.begin() + clientPosition);

	Client::decrementIdCounter();
}

void	Server::processClientsActivity(void) {
	if (_clients.empty())
		return ;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		Client &client = _clients[i];
		if (detectedActivity(client.getFd()))
		{
			client.storeRawData(Client::receiveData(client));
			client.pushToCommandQueue();
			std::queue<std::string> &commandsQueue = client.getCommandsQueue();
			while (!commandsQueue.empty()) {
				std::string line = commandsQueue.front();
				commandsQueue.pop();
				RawMessage msg = RawMessage::parseMsg(line);
				std::pair<std::string, std::vector<Client> > response = RawMessage::processMessage(msg, client, _clients, _channels);
				client.sendReply(response);
			}
			if (client.getShouldEraseClient())
				disconnectClient(client, i);
		}
	}
}

void	Server::start()
{
	signal(SIGINT, &Server::sigHandler);
	_activeConnections.push_back((pollfd) {.fd = Server::_socketDescriptor, .events = POLLIN});
	LOG("Server is up and running!")
	while (true)
	{
		pollActiveConnections();
		acceptNewClients();
		processClientsActivity();
	}
};
