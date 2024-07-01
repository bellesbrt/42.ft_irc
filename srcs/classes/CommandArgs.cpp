/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:21:15 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 19:03:41 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

CommandArgs::CommandArgs(Client &client, RawMessage &msg, std::vector<Client> &clients, std::vector<Channel> &channels,
						 std::vector<Client> &broadcastList)
: client(client), msg(msg), clients(clients), broadcastList(broadcastList), channels(channels) {}

CommandArgs::~CommandArgs() {}
