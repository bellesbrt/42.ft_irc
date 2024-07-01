/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:57:10 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 15:57:10 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Invalid arguments. Expected: ./ircserv <port> <password>");

		Commands::populateMap();

		Server& server = Server::getInstance();

		server.setPort(argv[1]);
		server.setPassword(argv[2]);
		server.setUpTCP();
		server.start();
	}
	catch(const std::exception& e)
	{
		ERROR(e.what())
	}

	return (0);
}
