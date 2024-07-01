/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:18 by rinacio           #+#    #+#             */
/*   Updated: 2024/06/23 16:22:18 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include "ft_irc.hpp"

class Utils {
private:
	Utils();
	~Utils();

public:
	static std::vector<std::string> split(std::string &s, std::string delimiter);
	static bool containsUniqueModeCharacters(std::string str);
	static bool hasModeCommandsWithParams(std::string str, std::vector<std::string> args);
};

bool operator==(const pollfd &lhs, const pollfd &rhs);
#endif
