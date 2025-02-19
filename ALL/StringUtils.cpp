#include "StringUtils.h"

StringUtils::StringUtils()
{
}

StringUtils::~StringUtils()
{
}

//Split a string
std::vector<std::string>& StringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//Split a string
std::vector<std::string> StringUtils::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}