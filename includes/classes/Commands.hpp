/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:21:54 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 18:56:21 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"
#include <map>

struct CommandArgs;

class Commands
{

	public:
		typedef std::string (*funcPtr)(CommandArgs);
		static void 			populateMap(void);
		static std::string 		callFunction(const std::string& cmdName, const CommandArgs& args);

	private:
		static std::map<std::string, funcPtr> _messageFunctions;
};

std::string cap(CommandArgs cArgs);
std::string invite(CommandArgs cArgs);
std::string join(CommandArgs cArgs);
std::string kick(CommandArgs cArgs);
std::string listc(CommandArgs cArgs);
std::string mode(CommandArgs cArgs);
std::string nick(CommandArgs cArgs);
std::string part(CommandArgs cArgs);
std::string pass(CommandArgs cArgs);
std::string privmsg(CommandArgs cArgs);
std::string quit(CommandArgs cArgs);
std::string topic(CommandArgs cArgs);
std::string user(CommandArgs cArgs);
std::string who(CommandArgs cArgs);

#endif
