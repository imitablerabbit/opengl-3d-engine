#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

class StringUtils
{
	public:
		StringUtils();
		~StringUtils();
		static std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);
		static std::vector<std::string> split(const std::string&, char);
};

#endif