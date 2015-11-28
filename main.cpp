#define _CRT_SECURE_NO_WARNINGS

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
#include "tests.h"
#include <stdio.h>


void allTestSerialize()
{
	testSerialize("testInt.txt", goodIntRand);
	testSerialize("testDouble.txt", doubleRand);
	testSerialize("testString.txt", littleStringRand);
	testSerialize("testVector.txt", vectorTRand);
}

void shortIntTester()
{
	makeSortTest(1000, "ShortIntSortTest", rand);
	makeReverseTest(1000, "ShortIntReverseTest", rand);
}
void shortDoubleTester() {
	makeSortTest(1000, "ShortDoubleSortTest", doubleRand);
	makeReverseTest(1000, "ShortDoubleReverseTest", doubleRand);
}

void shortTester()
{
	shortIntTester();
	shortDoubleTester();
}

void mediumTester()
{
	makeReverseTest(1000 * 1000, "MediumIntReverseTest", rand);
	makeSortTest(1000 * 1000, "MediumIntTest", rand);
}
void bigTesterNotRand() {
	makeReverseTest(10 * 1000 * 1000, "MaximumIntReverseTest", randNot);
}

void makeDirectories()
{
	system("md .\\buffers\\");
	system("md .\\test\\");
}

void testItAll()
{
	makeDirectories();
	allTestSerialize();
	shortTester();
	mediumTester();
	bigTesterNotRand();
	system("rd .\\buffers\\");
}

int main()
{
	
	
	_setmaxstdio(2048);
	testItAll();
	system("pause");
	return 0;
}
