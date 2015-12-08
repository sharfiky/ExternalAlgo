#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <queue>
#include "serialize.h"
#include <string>
#include <Windows.h>

const int cashSize = 100;

BOOL WINAPI DeleteFile(
	_In_ LPCTSTR lpFileName
	);

template <class T>
class IDataSource{
public:
	virtual T get() = 0;
	virtual bool hasNext() = 0;
	virtual ~IDataSource(){}
};

template <class T>
class FileDataSource : public IDataSource<T>{
private:
	std::fstream fileFrom_;
	std::string nameFile_;
	T preGetT_;
	T nowT_;
	bool haveInMemory_;
public:
	FileDataSource(const std::string &nameFile):nameFile_(nameFile), haveInMemory_ (false),
		fileFrom_(std::fstream(nameFile, std::fstream::in | std::fstream::binary)) {}

	T preGet()
	{
		T some;
		deserialize(some, fileFrom_);
		return some;
	}

	T get()
	{
		if (!haveInMemory_)
			preGetT_ = preGet();
		else
			preGetT_ = nowT_;
		haveInMemory_ = false;
		return preGetT_;
	}

	void close()
	{
		fileFrom_.flush();
		fileFrom_.close();
	}

	bool hasNext()
	{
		if (!haveInMemory_) //haveInMemory нужен, т.к. сначала мы пресчитываем элемент
		{
			nowT_ = preGet();
			haveInMemory_ = true;
		}
		return !fileFrom_.eof();
	}

	std::string getName() const
	{
		return nameFile_;
	}
};



template <class T>
class IDataTransmitter{
public:
	virtual void push(T &some) = 0;
	virtual void oflush() = 0;
	virtual void close() { }
	virtual ~IDataTransmitter(){
		close();
	}
};

template <class T>
class FileDataTransmitter : public IDataTransmitter <T>{
private:
	std::fstream fileTo_;
public:
	FileDataTransmitter(const std::string &nameFile):
		fileTo_ (std::fstream(nameFile, std::fstream::out | std::fstream::binary)) {}

	void push(T &some)
	{
		serialize(some, fileTo_);
	}
	
	void close()
	{
		fileTo_.flush();
		fileTo_.close();
	}

	void oflush() {
		fileTo_.flush();
	}
};