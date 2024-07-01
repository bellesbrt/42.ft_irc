/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:25:59 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 19:21:21 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Utils.hpp"
#include "replies.hpp"

std::string join(CommandArgs cArgs) {
    std::string nick = cArgs.client.getNick();
    std::string user = cArgs.client.getUser();
    std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], COMMA);
    std::vector<std::string> keys;
    if (cArgs.msg.args.size() > 1) {
        keys = Utils::split(cArgs.msg.args[1], COMMA);
    }

    if (channels.size() != keys.size() && !keys.empty()) {
        return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Mismatched keys and channels");
    }

    std::string reply;

    if (channels.size() == 1 && channels[0] == "0") {
        for (size_t i = 0; i < cArgs.channels.size(); ++i) {
			RawMessage rawMessage("", "PART", std::vector<std::string>(1, cArgs.channels[i].getName()));
			std::vector<Client> tempBroadcastList;
			reply += part(CommandArgs(cArgs.client, rawMessage, cArgs.clients, cArgs.channels, tempBroadcastList));
        }
        return reply;
    }

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string channelName = channels[i];
        std::string channelKey = keys.size() > i ? keys[i] : "";

        if (channelName[0] != '#' && channelName[0] != '&') {
            reply += ERR_CHANNELNOTFOUND(channelName);
            continue;
        }

        std::vector<Channel>::iterator it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
        if (it == cArgs.channels.end()) {
            Channel newChannel(channelName);
            newChannel.addClient(cArgs.client);
            if (!channelKey.empty()) newChannel.setKey(channelKey);
            cArgs.channels.push_back(newChannel);
            reply += JOIN(user, channelName) + RPL_NAMREPLY(nick, channelName, newChannel.getChannelUsers()) + RPL_ENDOFNAMES(nick, channelName);
        } else {
            if (it->isClientOnChannel(cArgs.client)) {
                continue;
            }
            if (it->getIsInviteOnly() && !cArgs.client.channelOnInviteList(channelName)) {
                reply += ERR_INVITEONLY(channelName);
                continue;
            }
            if (!it->getKey().empty() && it->getKey() != channelKey) {
                reply += ERR_BADCHANNELKEY(user, channelName);
                continue;
            }
            if (it->getClients().size() == it->getUserLimit()) {
                reply += ERR_CHANNELFULL(channelName);
                continue;
            }
            it->addClient(cArgs.client);
            reply += JOIN(user, channelName) + RPL_NAMREPLY(nick, channelName, it->getChannelUsers()) + RPL_ENDOFNAMES(nick, channelName);
        }
    }
    return reply;
}

