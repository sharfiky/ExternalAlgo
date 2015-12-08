#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"

template <class T>
class ExternalAlgorithms{
private:
	virtual void preprocessing_(std::vector<T> &a) = 0;
	void split_()
	{
		numberOfBlocks_ = 0;
		for (size_t i = 0; totalIn_->hasNext(); ++i, ++numberOfBlocks_)
		{
			vector<T> a;
			for (size_t j = 0; j < sizeOfBlock_ && totalIn_->hasNext(); ++j)
				a.push_back(totalIn_->get());
			preprocessing_(a);
			FileDataTransmitter<T> block(numberToName(i));
			for (size_t j = 0; j < a.size(); ++j)
				block.push(a[j]);
		}
	}
	void prepareBuffers_()
	{
		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			buffers_.push_back(new FileStorage<T>(numberToName(i), sizeOfBlock_ / numberOfBlocks_));
		}
	}
	virtual void merging_() = 0;
protected:
	IDataSource<T> *totalIn_;
	IDataTransmitter<T> *totalOut_;
	unsigned int sizeOfBlock_;
	unsigned int numberOfBlocks_;
	std::vector<FileStorage<T>*> buffers_;
public:
	ExternalAlgorithms(IDataSource<T> *in, IDataTransmitter<T> *out, int memoryInBlock){
		totalIn_ = in;
		totalOut_ = out;
		sizeOfBlock_ = memoryInBlock / sizeof(T);
	}

	void externalWork(){
		split_();
		prepareBuffers_();
		merging_();
	}
};

