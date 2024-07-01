/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:09:35 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 15:59:43 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include <algorithm>
#include <cstdlib>

std::vector<std::string> Utils::split(std::string &s, std::string delimiter)
{
	std::vector<std::string> tokens;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		tokens.push_back(s.substr(pos_start, pos_end - pos_start));
		pos_start = pos_end + delim_len;
	}
	tokens.push_back(s.substr(pos_start));
	tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());
	return tokens;
}

bool Utils::containsUniqueModeCharacters(std::string str) {
	std::string modeCharacters = "+-oitkl";
	if (str.size() > modeCharacters.size())
		return false;
	for (size_t i = 0; i < str.length(); ++i) {
		if (modeCharacters.find(str[i]) == std::string::npos
			|| (str[i] == '+' && i != 0)
			|| (str[i] == '-' && i != 0)) {
			return false;
		}
	}
	std::sort(str.begin(), str.end());
	return std::unique(str.begin(), str.end()) == str.end();
}

bool hasModeCommandsWithParams(const std::string &modes, const std::vector<std::string> &modeParams) {
    std::string charactersWithParams = modes.find('-') != std::string::npos ? "o" : "okl";
    size_t paramsCount = 0;
    for (std::string::const_iterator it = modes.begin(); it != modes.end(); ++it) {
        if (charactersWithParams.find(*it) != std::string::npos) {
            paramsCount++;
        }
    }
    return paramsCount == modeParams.size();
}

bool operator==(const pollfd &lhs, const pollfd &rhs) {
	return (lhs.events == rhs.events && lhs.fd == rhs.fd && lhs.revents == rhs.revents);
};

Utils::Utils() {}
Utils::~Utils() {}
