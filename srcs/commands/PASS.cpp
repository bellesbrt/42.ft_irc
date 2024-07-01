/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:24:42 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:24:42 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string pass(CommandArgs cArgs)
{
	if (cArgs.msg.args.size() != 1)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of arguments");

	if (!cArgs.client.getPass().empty())
		return ERR_ALREADYREGISTERED(cArgs.client.getUser());

	cArgs.client.setPass(cArgs.msg.args[0]);

	if (cArgs.client.getPass() != Server::getPassword())
	{
		cArgs.client.setShouldEraseClient(true);
		return (ERR_INCORRECTPASSWORD());
	}

	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));

	return ("");
}
