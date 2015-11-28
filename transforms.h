#pragma once

#include <vector>
#include <string>
#include "sources.h"

const int nameSize = 10;
//const std::string buffersDir = "D:\\visual studio 2015\\Projects\\external\\external\\buffers\\";
const std::string buffersDir = ".\\buffers\\";


template<class T>
void printVector(std::vector<T> &a, IDataTransmitter<T> *out)
{
	for (size_t i = 0; i < a.size(); ++i)
		out->push(a[i]);
	a.clear();
}

std::string intToString(int some, int size)
{
	int len = 0;
	std::string str;
	while (some > 0)
	{
		str += (char)(some % 10 + 48);
		some /= 10;
		++len;
	}
	for (int i = 0; i < size - len; ++i)
		str += '0';
	reverse(str.begin(), str.end());
	return str;
}

std::string numberToName(int number)
{
	std::string name = buffersDir + "file N" + intToString(number, nameSize) + ".txt";
	return name;
}
