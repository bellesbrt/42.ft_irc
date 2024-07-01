/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:24:51 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:24:51 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string part(CommandArgs cArgs) {
    if (cArgs.msg.args.empty())
        return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No channel specified");

    std::string message;
    if (cArgs.msg.args.size() == 2)
        message = cArgs.msg.args[1];

    std::string nick = cArgs.client.getNick();
    std::string user = cArgs.client.getUser();
    std::string returnMessage;
    std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], COMMA);

    std::vector<std::string>::iterator it_channel;
    for (it_channel = channels.begin(); it_channel != channels.end(); ++it_channel) {
        std::string channelName = *it_channel;
        std::vector<Channel>::iterator it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
        if (it == cArgs.channels.end())
            return ERR_CHANNELNOTFOUND(channelName);
        if (!it->isClientOnChannel(cArgs.client))
            return ERR_NOTONCHANNEL(channelName);

        std::vector<Client> broadcastList = it->getClients();
        it->removeClient(cArgs.client);
        if (it->getClients().empty())
            cArgs.channels.erase(it);

        std::string reply;
        if (!message.empty())
            reply = RPL_PARTMSG(user, nick, channelName, message);
        else
            reply = RPL_PARTNOMSG(user, nick, channelName);

        std::pair<std::string, std::vector<Client> > broadcastPair = std::make_pair(reply, broadcastList);
        Client::sendToBroadcastOnly(broadcastPair);
        returnMessage.append(reply);
    }

    return returnMessage;
}

