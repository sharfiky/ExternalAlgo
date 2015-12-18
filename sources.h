#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <queue>
#include <string>
#include "fileStorage.h"

const size_t cashSize = 100;



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
	FileStorage<T> fileFrom_;
public:
	FileDataSource(const std::string &nameFile, int cashSize = 1): fileFrom_(nameFile, false, cashSize){}

	T get()
	{
		return fileFrom_.getData();
	}

	void close()
	{
		fileFrom_.close();
	}

	bool hasNext()
	{
		return fileFrom_.canTakeData();
	}

	std::string getName() const
	{
		return fileFrom_.getName();
	}
	void removeFile()
	{
		fileFrom_.removeFile();
	}
};



template <class T>
class IDataTransmitter{
public:
	virtual void push(T &some) = 0;
	virtual void close() = 0;
	virtual ~IDataTransmitter(){
	}
};

template <class T>
class FileDataTransmitter : public IDataTransmitter <T>{
private:
	FileStorage<T> fileTo_;
public:
	FileDataTransmitter(const std::string &nameFile):
		fileTo_ (nameFile, true) {}

	void push(T &some)
	{
		fileTo_.pushData(some);
	}
	
	void close()
	{
		fileTo_.close();
	}
	void removeTFile()
	{
		fileTo_.removeFile();
	}
};