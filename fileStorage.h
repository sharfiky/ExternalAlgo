#pragma once

#include<queue>
#include "sources.h"

template<class T>
class FileStorage{
private:
	FileDataSource<T> fileFrom_;
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
		fileFrom_(nameOfBuffer), objectInCash_(cashingSize) {
	}

	~FileStorage() {
		close();
	}

	void close() {
		fileFrom_.close();
	}

	

	bool canTakeData()
	{
		return fileFrom_.hasNext() || !emptyCash();
	}

	T getData()
	{
		if (emptyCash())
		{
			for (int i = 0; i < objectInCash_ && fileFrom_.hasNext(); ++i)
				cash_.push(fileFrom_.get());
		}
		return getCash();
	}
};
