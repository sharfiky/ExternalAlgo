#pragma once

#include<vector>
#include<string>
#include<cstdlib>

int goodIntRand()
{
	return rand() * 65536 + rand();
}

int littleIntRand()
{
	return rand() % 64 + 16;
}

std::string littleStringRand()
{
	unsigned int n = rand() % 256 + 16;
	std::string s;
	for (size_t i = 0; i < n; ++i)
		s += (char)(rand() % 26 + 65);
	return s;
}

double doubleRand()
{
	return goodIntRand() * 1.0 / rand();
}

std::vector<int> vectorTRand()
{
	unsigned int n = rand();
	std::vector <int> a(n);
	for (size_t i = 0; i < n; ++i)
		a[i] = goodIntRand();
	return a;
}
std::string stringTestRand()
{
	return "AB";
}
int randNot()
{
	return 4;
}