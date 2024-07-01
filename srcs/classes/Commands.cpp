/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:21:15 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 11:13:41 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::map<std::string, Commands::funcPtr> Commands::_messageFunctions;

void Commands::populateMap() {
    _messageFunctions["USER"] = &user;
    _messageFunctions["NICK"] = &nick;
    _messageFunctions["PASS"] = &pass;
    _messageFunctions["CAP"] = &cap;
    _messageFunctions["QUIT"] = &quit;
    _messageFunctions["JOIN"] = &join;
    _messageFunctions["LISTC"] = &listc;
    _messageFunctions["PRIVMSG"] = &privmsg;
    _messageFunctions["KICK"] = &kick;
    _messageFunctions["PART"] = &part;
    _messageFunctions["WHO"] = &who;
    _messageFunctions["MODE"] = &mode;
    _messageFunctions["TOPIC"] = &topic;
    _messageFunctions["INVITE"] = &invite;
}

std::string Commands::callFunction(const std::string &cmdName, const CommandArgs &args)
{
	std::set<std::string> authorizedCommands;
	authorizedCommands.insert("USER");
	authorizedCommands.insert("CAP");
	authorizedCommands.insert("NICK");
	authorizedCommands.insert("PASS");
	authorizedCommands.insert("QUIT");

	if (!args.client.isAuthenticated() && authorizedCommands.find(args.msg.command) == authorizedCommands.end())
		return ("User is not authenticated\r\n");

    std::map<std::string, funcPtr>::iterator it = _messageFunctions.find(cmdName);
    if (it == _messageFunctions.end()) return cmdName + " :Invalid command\r\n";
    
	return it->second(args);
}
