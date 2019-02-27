#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::vector<std::string> chilisplit(const std::string& s, const std::string& delimiters)
{
	std::vector<std::string> split;
	const auto FindNext = [&](const auto i)
	{
		return std::find_first_of(i, s.end(), delimiters.begin(), delimiters.end());
	};
	for (std::string::const_iterator i, i_prev = s.begin(); ; i_prev = i + 1)
	{
		i = FindNext(i_prev);
		split.emplace_back(i_prev, i);
		if (i == s.end()) {
			break;
		}
	}
	return split;
};
