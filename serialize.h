#pragma once

#include <vector>
#include <string>
#include <fstream>


template <class T>
void serialize(T &some, std::fstream &streamTo)
{
	streamTo.write(reinterpret_cast <char *> (&some), sizeof(some));
}

template <class T>
void serialize(std::vector<T> &some, std::fstream &streamTo)
{
	size_t n = some.size();
	serialize(n, streamTo);
	for (size_t i = 0; i < n; ++i)
		serialize(some[i], streamTo);
}

template <>
void serialize<std::string>(std::string &some, std::fstream &streamTo)
{
	size_t n = some.size();
	serialize(n, streamTo);
	for (size_t i = 0; i < n; ++i)
		serialize(some[i], streamTo);
}


template <class T>
void deserialize(T &some, std::fstream &streamFrom)
{
	streamFrom.read(reinterpret_cast <char *> (&some), sizeof(T));
}

template <class T>
void deserialize(std::vector <T> &some, std::fstream &streamFrom)
{
	size_t n;
	deserialize(n, streamFrom);
	some.resize(n);
	for (size_t i = 0; i < n; ++i)
		deserialize(some[i], streamFrom);
}

template <>
void deserialize<std::string>(std::string &some, std::fstream &streamFrom)
{
	size_t n;
	deserialize(n, streamFrom);
	some.resize(n);
	for (size_t i = 0; i < n; ++i)
		deserialize<char>(some[i], streamFrom);
}