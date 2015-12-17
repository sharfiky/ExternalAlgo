#pragma once

#include <vector>
#include <string>
#include "sources.h"

const size_t nameSize = 10;
const std::string buffersDir = ".\\buffers\\";

std::string intToString(size_t some, size_t size)
{
	int len = 0;
	std::string str;
	while (some > 0)
	{
		str += (char)(some % 10 + 48);
		some /= 10;
		++len;
	}
	for (size_t i = 0; i < size - len; ++i)
		str += '0';
	reverse(str.begin(), str.end());
	return str;
}

std::string numberToName(size_t number)
{
	std::string name = buffersDir + "file N" + intToString(number, nameSize) + ".txt";
	return name;
}
