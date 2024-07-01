/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:25:44 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:25:44 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string kick(CommandArgs cArgs) {
	if (cArgs.msg.args.size() < 2)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "You must send at least one channel and one user to kick");

	std::vector<std::string> specifiedChannels = Utils::split(cArgs.msg.args[0], COMMA);
	std::vector<std::string> usersToKick = Utils::split(cArgs.msg.args[1], COMMA);
	std::string reason;
	if (cArgs.msg.args.size() > 2)
		reason = cArgs.msg.args[2];

	if (specifiedChannels.size() == 0)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No channels informed");
	if (usersToKick.size() == 0)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No users informed");
	if (specifiedChannels.size() != usersToKick.size())
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "The number of channels and users to kick should be equal");

	size_t nbOperations = specifiedChannels.size();
	std::string reply;

	for (size_t i = 0; i < nbOperations; i++) {
		std::vector<Channel>::iterator channelToKickFrom = std::find(cArgs.channels.begin(), cArgs.channels.end(), specifiedChannels[i]);
		if (channelToKickFrom == cArgs.channels.end()) {
			reply.append(ERR_CHANNELNOTFOUND(specifiedChannels[i]));
			continue ;
		}
		if (!channelToKickFrom->isOperator(cArgs.client)) {
			reply.append(ERR_NOTCHANNELOPERATOR(cArgs.client.getUser(), channelToKickFrom->getName()));
			continue ;
		}
		std::vector<Client>::iterator clientToBeKicked = std::find(cArgs.clients.begin(), cArgs.clients.end(), usersToKick[i]);
		if (clientToBeKicked == cArgs.clients.end() || !channelToKickFrom->isClientOnChannel(usersToKick[i])) {
			reply.append(ERR_NOTINCHANNEL(cArgs.client.getUser(), usersToKick[i], specifiedChannels[i]));
			continue ;
		}
		if (*clientToBeKicked == cArgs.client) {
			reply.append(ERR_NEEDMOREPARAMS(cArgs.msg.command, "You can't KICK yourself... use PART instead!"));
			continue ;
		}
		std::vector<Client> broadcastList = channelToKickFrom->getClients();
		broadcastList.erase(std::find(broadcastList.begin(), broadcastList.end(), cArgs.client));
		std::string messageToBroadcast;

		if (reason.empty())
			messageToBroadcast.append(RPL_KICKNOREASON(cArgs.client.getNick(), cArgs.client.getUser(), specifiedChannels[i], usersToKick[i]));
		else
			messageToBroadcast.append(RPL_KICKREASON(cArgs.client.getNick(), cArgs.client.getUser(), specifiedChannels[i], usersToKick[i], reason));

		std::pair<std::string, std::vector<Client> > broadcastPair = std::make_pair(messageToBroadcast, broadcastList);
		Client::sendToBroadcastOnly(broadcastPair);

		channelToKickFrom->removeClient(*clientToBeKicked);
		reply.append(messageToBroadcast);
	}

	return reply;
}
