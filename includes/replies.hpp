/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:34 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 20:21:49 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#define FTIRC std::string(":ft.irc")
#define CRLF std::string("\r\n")
#define COMMA std::string(",")
#define COLON std::string(":")
#define SPACE std::string(" ")

#define RPL_WELCOME(nick, user) (FTIRC + " 001 " + user + " :Welcome, " + nick + "!" + user + "@*" + CRLF)
#define RPL_ENDOFWHO(channel) (FTIRC + " 315 " + channel + " :End of WHO list." + CRLF)
#define RPL_CHANNELMODE(channel, mode, modeParams) (FTIRC + " 324 * " + channel + " " + mode + " " + modeParams + CRLF)
#define RPL_NOTOPIC(nick, channel) (FTIRC + " 331 " + nick + " " + channel + " :No topic set." + CRLF)
#define RPL_TOPIC(nick, channel, topic) (FTIRC + " 332 " + nick + " " + channel + " :" + topic + CRLF)
#define RPL_INVITING(nick, recipient, channel) (FTIRC + " 341 " + nick + " " + recipient + " :" + channel + CRLF)
#define RPL_WHOREPLY(channel, user, nick, flags, realname) (FTIRC + " 352 " + channel + " " + user + " ft.irc " + nick + " " + flags + ":0 " + realname + CRLF)
#define RPL_NAMREPLY(nick, channel, names) (FTIRC + " 353 " + nick + " = " + channel + " : " + names + CRLF)
#define RPL_ENDOFNAMES(nick, channel) (FTIRC + " 366 " + nick + " " + channel + " :End of NAMES list." + CRLF)

#define ERR_CHANNELNOTFOUND(channel) (FTIRC + " 403 * " + channel + " :Channel does not exist." + CRLF)
#define ERR_UNKNOWNNICK(nick) (FTIRC + " 406 " + nick + " :Nickname does not exist." + CRLF)
#define ERR_NORECIPIENT(user) (FTIRC + " 411 " + user + " :Message recipient missing." + CRLF)
#define ERR_NOTEXTTOSEND(user) (FTIRC + " 412 " + user + " :No text to send." + CRLF)
#define ERR_NICKNAMENOTGIVEN() (FTIRC + " 431 :Nickname not specified." + CRLF)
#define ERR_INVALIDNICKNAME(nick) (FTIRC + " 432 * " + nick + " :Invalid nickname." + CRLF)
#define ERR_NICKNAMEINUSE(nick) (FTIRC + " 433 * " + nick + " :Nickname is in use." + CRLF)
#define ERR_NOTINCHANNEL(operator, client, channel) (FTIRC + " 441 " + operator + SPACE + client + SPACE + channel + " :Not in channel." + CRLF)
#define ERR_NOTONCHANNEL(channel) (FTIRC + " 442 * " + channel + " :Not on channel." + CRLF)
#define ERR_ALREADYONCHANNEL(nick, channel) (FTIRC + " 443 * " + nick + " " + channel + " :Already on channel." + CRLF)
#define ERR_NEEDMOREPARAMS(command, reason) (FTIRC + " 461 * " + command + " :Missing parameters. " + reason + CRLF)
#define ERR_ALREADYREGISTERED(user) (FTIRC + " 462 " + user + " :Already registered." + CRLF)
#define ERR_INCORRECTPASSWORD() (FTIRC + " 464 * :Incorrect password." + CRLF)
#define ERR_CHANNELFULL(channel) (FTIRC + " 471 * " + channel + " :Channel full." + CRLF)
#define ERR_INVITEONLY(channel) (FTIRC + " 473 * " + channel + " :Channel is invite-only." + CRLF)
#define ERR_BADCHANNELKEY(user, channel) (FTIRC + " 475 " + user + " " + channel + " :Incorrect channel key." + CRLF)
#define ERR_NOTCHANNELOPERATOR(user, channel) (FTIRC + " 482 " + user + " " + channel + " :Not a channel operator." + CRLF)

#define JOIN(user, channel) (COLON + user + " JOIN " + channel + CRLF)
#define PRIVMSG_BROADCAST(nick, user, channel, topic) (COLON + nick + "!~" + user + "@ft.irc TOPIC " + channel + " " + topic + CRLF)
#define RPL_PRIVMSG(user, dest, message) (COLON + user + " PRIVMSG " + dest + " :" + message + CRLF)
#define RPL_PARTMSG(nick, user, dest, message) (COLON + nick + "!~" + user + "@* PART " + dest + " :" + message + CRLF)
#define RPL_PARTNOMSG(nick, user, dest) (COLON + nick + "!~" + user + "@* PART " + dest + CRLF)
#define RPL_KICKREASON(op_nick, op_user, channel, client, reason) (COLON + op_nick + "!~" + op_user + "@ft.irc KICK " + channel + " " + client + " " + COLON + reason + CRLF)
#define RPL_KICKNOREASON(op_nick, op_user, channel, client) (COLON + op_nick + "!~" + op_user + "@ft.irc KICK " + channel + " " + client + CRLF)
#define RPL_KICKFEEDBACK(op_nick, op_user, channel, client) (COLON + op_nick + "!~" + op_user + "@ft.irc KICK " + channel + " " + client + CRLF)
#define RPL_MODEBASE(nick, user, channel) (COLON + nick + "!~" + user + "@ft.irc MODE " + channel + " ")
#define RPL_INVITEMSG(nick, user, recipient, channel) (COLON + nick + "!~" + user + "@ft.irc INVITE " + recipient + " :" + channel + CRLF)

#endif
