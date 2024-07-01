/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:11 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:22:11 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	private:

		static int					_serverPort;
		static int					_socketDescriptor;
		static pollfd				*_pollfd;
		static sockaddr_in			_serverAddr;
		static std::string			_password;
		static std::vector<pollfd>	_activeConnections;
		static std::vector<Client>	_clients;
		static std::vector<Channel>	_channels;

		Server();
		~Server();
		Server(const Server&);

		static void bindSocketToAddress();
		static void createSocket();
		static void configureAddress();
		static void listenForClients();
		static void sigHandler(int);

		static void pollActiveConnections(void);
		static void processClientsActivity(void);
		static void acceptNewClients(void);
		static bool detectedActivity(const int &clientFd);
		static void disconnectClient(const Client &client, const int &clientPosition);

	public:

		static Server& getInstance();

		static void setUpTCP();
		static void start();

		void setPort(char *input);
		static std::string getPassword();
		static void setPassword(char *password);
};

#endif
