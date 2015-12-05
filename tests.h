#pragma once

#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <set>
#include "sources.h"
#include "transforms.h"
#include "fileStorage.h"
#include "externalSort.h"
#include "externalReverser.h"
#include "randoms.h"
#include <Windows.h>


using std::queue;
using std::vector;
using std::string;


unsigned int maxSizeInRam = 30 * 1024 * 1024;
unsigned int maxInVector = 4000 * 1000 * 1000;

const string testDir = ".\\test\\_";

template<class T>
bool eq(T &a, T &b)
{
	return a != b;
}

template <class T>
bool checkVectorEq(vector<T> &a, vector<T>  &b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}
template <class T>
bool checkVectorEq(vector<vector<T> > &a, vector<vector<T> > &b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i)
	{
		if (a[i].size() != b[i].size())
			return false;
		for (size_t j = 0; j < a[i].size(); ++j)
			if (a[i][j] != b[i][j])
				return false;
	}
	return true;
}

template <class TestType>
bool checkSort(IDataSource<TestType> *a, IDataSource<TestType> *b)
{
	TestType l;
	bool was = false;
	while (a->hasNext() && b->hasNext())
	{
		TestType tmp = b->get();
		if (was && l > tmp)
			return false;
		else
			was = true;
		l = a->get();
		l = tmp;
	}
	if (a->hasNext() != b->hasNext())
		return false;
	return true;
}



template<class T> void generateToFile(const std::string &nameOfFile, unsigned int size, T(*make_rand)())
{
	IDataTransmitter<T> *testFile = new FileDataTransmitter<T>(nameOfFile);
	for (size_t i = 0; i < size; ++i)
	{
		T a = make_rand();
		testFile->push(a);
	}
	testFile->close();
}

template <class T> void sortFromFileToFile(const string &nameInFile, const string &nameOutFile, unsigned int &memoryInRam)
{
	IDataSource<T> *fromTestFile = new FileDataSource<T>(nameInFile);
	IDataTransmitter<T> *checkingFile = new FileDataTransmitter<T>(nameOutFile);

	ExternalSorter<T> sorter(fromTestFile, checkingFile, memoryInRam);
	sorter.externalWork();
	checkingFile->close();
}


template <class TestType>
void testSerialize(string name, TestType(*make_rand)()) {
	string nameInDir = testDir + name;
	IDataTransmitter<TestType> *out = new FileDataTransmitter<TestType>(nameInDir);
	unsigned int n = littleIntRand();
	vector<TestType> a(n), b(n);
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = make_rand();
		out->push(a[i]);
	}
	out->close();
	IDataSource<TestType> *in = new FileDataSource<TestType>(nameInDir);
	for (size_t i = 0; i < n; ++i)
		b[i] = in->get();
	std::cout << name << " " << (checkVectorEq<TestType>(a, b) ? "OK" : "NO") << "\n";
}

template <class TestType>
void makeSortTest(unsigned int size, string name, TestType(*make_rand)())
{
	unsigned memoryInRam = min(sizeof(TestType) * size, maxSizeInRam);
	memoryInRam = sizeof(TestType) * (min(memoryInRam / sizeof(TestType), maxInVector));
	string nameInFile = testDir + name + "In.txt";
	string nameOutFile = testDir + name + "Out.txt";

	generateToFile<TestType>(nameInFile, size, make_rand);
	sortFromFileToFile<TestType>(nameInFile, nameOutFile, memoryInRam);

	IDataSource<TestType> *one = new FileDataSource<TestType>(nameInFile);
	IDataSource<TestType> *two = new FileDataSource<TestType>(nameOutFile);
	std::cout << name << " " << (checkSort<TestType>(one, two) ? "OK" : "NO") << "\n";
}

template<class T>
bool checkFileEq(IDataSource<T> *a, IDataSource<T> *b)
{
	while (a->hasNext() && b->hasNext())
	{
		T l = a->get(), m = b->get();
		if (l != m)
			return false;
	}
	if (a->hasNext() != b->hasNext())
		return false;
	return true;
}



template <class T>
void reverseFromFileToFile(const string &nameInFile, const string &nameOutFile, unsigned int &memoryInRam)
{
	IDataSource<T> *fromTestFile = new FileDataSource<T>(nameInFile);
	IDataTransmitter<T> *checkingFile = new FileDataTransmitter<T>(nameOutFile);

	ExternalReverser<T> reverser(fromTestFile, checkingFile, memoryInRam);
	reverser.externalWork();
	checkingFile->close();
}

template <class TestType> void makeReverseTest(unsigned int size, string name, TestType(*make_rand)())
{
	unsigned memoryInRam = min(sizeof(TestType) * size, maxSizeInRam);
	memoryInRam = sizeof(TestType) * (min(memoryInRam / sizeof(TestType), maxInVector));

	string nameInFile = testDir + name + "In.txt";
	string nameOutFile = testDir + name + "Out.txt";
	string middle = testDir + "middle.txt";

	generateToFile<TestType>(nameInFile, size, make_rand);
	reverseFromFileToFile<TestType>(nameInFile, nameOutFile, memoryInRam);
	reverseFromFileToFile<TestType>(nameOutFile, middle, memoryInRam);

	IDataSource<TestType> *one = new FileDataSource<TestType>(nameInFile);
	IDataSource<TestType> *two = new FileDataSource<TestType>(middle);
	std::cout << name << " " << (checkFileEq<TestType>(one, two) ? "OK" : "NO") << "\n";
}


