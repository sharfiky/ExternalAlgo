#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"

template <class T>
class ExternalAlgorithms{
private:
	IDataSource<T> *totalIn_;
protected:
	IDataTransmitter<T> *totalOut_;
	unsigned int sizeOfBlock_;
	unsigned int numberOfBlocks_;
public:
	ExternalAlgorithms(IDataSource<T> *in, IDataTransmitter<T> *out, int memoryInBlock){
		totalIn_ = in;
		totalOut_ = out;
		sizeOfBlock_ = memoryInBlock / sizeof(T);
	}

	virtual void preprocessing(std::vector<T> &a) = 0;

	void split()
	{
		numberOfBlocks_ = 0;
		for (size_t i = 0; totalIn_->hasNext(); ++i, ++numberOfBlocks_)
		{
			vector<T> a;
			for (size_t j = 0; j < sizeOfBlock_ && totalIn_->hasNext(); ++j)
				a.push_back(totalIn_->get());
			preprocessing(a);
			FileDataTransmitter<T> block(numberToName(i));
			for (size_t j = 0; j < a.size(); ++j)
				block.push(a[j]);
		}
	}

	virtual void merging() = 0;

	void externalWork(){
		split();
		merging();
	}
};

