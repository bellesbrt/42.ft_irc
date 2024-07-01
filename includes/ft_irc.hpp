/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:27 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 18:11:33 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#define LOG(log) std::cout << "<INFO> " << log << std::endl;
#define ERROR(error) std::cerr << "<ERROR> IRC Internal error: " << error << std::endl;
#define DEBUG(debugMessage) std::cout << "<DEBUG> " << debugMessage << std::endl;
#define CLIENT_LIMIT 1024
#define TIMEOUT_MS 1000
#define BUFFER_SIZE 512
#define MAX_PORT_NUMBER 65535
#define SERVER 0

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include <csignal>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <set>

class Channel;
struct CommandArgs;
class Client;
class Server;

#include "classes/Client.hpp"
#include "classes/RawMessage.hpp"
#include "classes/Commands.hpp"
#include "classes/Channel.hpp"
#include "classes/CommandArgs.hpp"
#include "classes/Server.hpp"
#include "classes/Utils.hpp"

#include "replies.hpp"

typedef struct sockaddr_in sockAddrIn;

typedef struct sockaddr sockAddr;

typedef struct pollfd pollfd;

#endif
