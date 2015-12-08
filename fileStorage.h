#pragma once

#include<queue>
#include "sources.h"

template<class T>
class FileStorage{
private:
	FileDataSource<T> fileFrom_;
	FileDataTransmitter<T> fileTo_;
	bool fileFomeOpen_;
	std::queue<T> cash_;
	int objectInCash_;
	
	T getCash()
	{
		T some = cash_.front();
		cash_.pop();
		return some;
	}

	bool emptyCash() const
	{
		return cash_.empty();
	}
public:
	FileStorage(const std::string &nameOfBuffer, int cashingSize) :
		fileFrom_(nameOfBuffer), objectInCash_(cashingSize), fileTo_(nameOfBuffer), fileFomeOpen_(false) {
	}

	~FileStorage() {
		close();
		DeleteFile(fileFrom_.getName().c_str());
	}

	void close() {
		fileFrom_.close();
		fileTo_.close();
	}
	void closeToOpenFrom() {
		fileTo_.close();
		fileFrom_.open();
		fileFomeOpen_ = true;
	}

	void checkFileFromOpen()
	{
		if (!fileFomeOpen_)
			closeToOpenFrom();
	}

	bool canTakeData() 
	{
		checkFileFromOpen();
		return fileFrom_.hasNext() || !emptyCash();
	}

	T getData()
	{
		checkFileFromOpen();
		if (emptyCash())
		{
			for (int i = 0; i < objectInCash_ && fileFrom_.hasNext(); ++i)
				cash_.push(fileFrom_.get());
		}
		return getCash();
	}
	void push(T data)
	{
		fileTo_.push(data);
	}
};
