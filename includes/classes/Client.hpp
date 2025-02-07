/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:21:32 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:21:32 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ft_irc.hpp"

class Client
{
	private:
	
		bool _shouldEraseClient;
		int _retries;
		static int _idCounter;
		int _fd;
		int _id;
		std::string _realName;
		std::string _nick;
		std::string _user;
		std::string _rawData;
		std::string _pass;

		std::queue<std::string> _commandsQueue;
		std::string _buffer;
		std::vector<std::string> _channelsInvited;
	public:

		explicit Client(int socketDescriptor);
		Client(const Client &rhs);
		Client &operator=( const Client &rhs);
		~Client();
	
		int getId() const;
		void setId(const int &id);
		int getFd() const;
		void setFd(const int &fd);
		std::string getRealName() const;
		void setRealName(const std::string &name);
		std::string getUser() const;
		void setUser(const std::string &user);
		std::string getNick() const;
		void setNick(const std::string &nick);
		std::string getPass() const;
		void setPass(const std::string &clientpass);
		bool getShouldEraseClient() const;
		void setShouldEraseClient(bool state);
		int getRetries() const;
		void setRetries(int value);
		static int getIdCounter();
		void storeRawData(const std::string &cmd);
		void flushBuffer();
		std::string getRawData() const;
		std::queue<std::string> &getCommandsQueue();

		void addChannelToInvited(const std::string &channelName);
		std::vector<std::string> &getChannelInvited();
		bool channelOnInviteList(const std::string &channelName);
		void removeChannelFromInviteList(const std::string &channelName);

		static void decrementIdCounter();
		void sendReply(std::pair<std::string, std::vector<Client> > &msg) const;
		static void sendToBroadcastOnly(std::pair<std::string, std::vector<Client> > &msg);
		void incrementRetries();
		void pushToCommandQueue();

		bool operator==(const Client &rhs);
		bool operator==(const std::string &rhs);

		static std::string receiveData(Client &client);
		
		bool isAuthenticated(void) const;
};

#endif
