/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:21:11 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:27:13 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel() : _i(false), _t(true), _k(false), _l(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::Channel(const std::string& name) : _name(name), _i(false), _t(true), _k(false), _l(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::~Channel() {}

Channel::Channel(Channel const &src) : _i(), _t(), _k(), _l(), _userLimit()
{
	*this = src;
}

Channel &Channel::operator=(Channel const &src)
{
	if (this != &src)
	{
		this->_topic = src._topic;
		this->_name = src._name;
		this->_key = src._key;
		this->_clients = src._clients;
		this->_operators = src._operators;
		this->_userLimit = src._userLimit;
		this->_i = src._i;
		this->_t = src._t;
		this->_k = src._k;
		this->_l = src._l;
	}
	return (*this);
}

bool Channel::operator==(const std::string &name)
{
	if (name == this->_name)
		return true;
	return false;
}

std::string Channel::getTopic() const
{
	return (this->_topic);
}

void Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

std::string Channel::getName() const
{
	return (this->_name);
}

void Channel::setName(const std::string &name)
{
	this->_name = name;
}

std::string Channel::getKey() const
{
	return (this->_key);
}

void Channel::setKey(const std::string &key)
{
	this->_k = true;
	this->_key = key;
}

bool Channel::getIsInviteOnly() const
{
	return (this->_i);
}

void Channel::setIsInviteOnly(bool action)
{
	this->_i = action;
}

void Channel::setTopicRestricted(bool action) {
	this->_t = action;
}
std::vector<Client> &Channel::getClients()
{
	return (this->_clients);
}

void Channel::removeKey() {
	this->_k = false;
	this->_key = "";
}
const std::vector<Client> &Channel::getClients() const
{
	return (this->_clients);
}

void Channel::setClients(const std::vector<Client> &clients)
{
	this->_clients = clients;
}

size_t Channel::getUserLimit() const
{
	return (this->_userLimit);
}

void Channel::setUserLimit(const size_t &userLimit)
{
	this->_l = true;
	this->_userLimit = userLimit;
}

void Channel::addClient(const Client &client)
{
	this->_clients.push_back(client);
}

std::string Channel::getChannelUsers() {
	std::string channelUsers;

	for (size_t i = 0; i < this->_clients.size(); i++) {
		if (std::find(this->_operators.begin(), this->_operators.end(), this->_clients[i]) != this->_operators.end())
			channelUsers += "@";
		channelUsers += this->_clients[i].getUser();
		channelUsers += " ";
	}
	return channelUsers;
}

void Channel::addOperator(const Client &client) {
	this->_operators.push_back(client);
}

void Channel::removeOperator(const Client &client) {
	this->_operators.erase(std::find(this->_operators.begin(), this->_operators.end(), client));
}

bool Channel::isClientOnChannel(const Client &client) {
	std::vector<Client>::iterator
	it = std::find(this->_clients.begin(), this->_clients.end(), client);
	if (it == this->_clients.end())
		return false;
	return true;
}

bool Channel::isClientOnChannel(const std::string &client) {
	std::vector<Client>::iterator
	it = std::find(this->_clients.begin(), this->_clients.end(), client);
	if (it == this->_clients.end())
		return false;
	return true;
}

void Channel::removeClient(const Client &client) {

	std::vector<Client>::iterator clientsIt = std::find(this->_clients.begin(), this->_clients.end(), client);

	std::vector<Client>::iterator operatorsIt = std::find(this->_operators.begin(), this->_operators.end(), client);

	if (clientsIt != this->_clients.end())
		this->_clients.erase(clientsIt);

	if (operatorsIt != this->_operators.end())
		this->_operators.erase(operatorsIt);
}

void Channel::removeClientLimit() {
	this->_l = false;
	this->_userLimit = -1;
}

bool Channel::isOperator(Client &client) {
	std::vector<Client>::iterator
	it = std::find(this->_operators.begin(), this->_operators.end(), client);
	if (it == this->_operators.end())
		return false;
	return true;
}

std::pair<std::string, std::string> Channel::getModes() const {
	std::string modes = "+";
	std::string modeParams = "";
	if (this->_i)
		modes += 'i';
	if (this->_t)
		modes += 't';
	if (this->_k) {
		modes += 'k';
		if (!this->_key.empty())
			modeParams += this->_key + " ";
	}
	if (this->_l) {
		modes += 'l';
		std::ostringstream oss;
		oss << this->_userLimit;
		modeParams += oss.str() + " ";
	}
	return std::make_pair(modes, modeParams);
}

bool Channel::isTopicOPOnly() {
    if (this->_t)
        return false;
    return true;
}
