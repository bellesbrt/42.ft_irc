/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandArgs.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:21:44 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:21:44 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ARGS_HPP
#define COMMAND_ARGS_HPP

#include "ft_irc.hpp"

struct CommandArgs
{
	Client &client;
	RawMessage msg;
	std::vector<Client> &clients;
	std::vector<Client> &broadcastList;
	std::vector<Channel> &channels;

	CommandArgs(Client &client, RawMessage &msg, std::vector<Client> &clients, std::vector<Channel> &channels,
				std::vector<Client> &broadcastList);
	~CommandArgs();
};

#endif
