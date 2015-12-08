#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"
#include "externalAlgo.h"

template<class T>
class ExternalReverser : public ExternalAlgorithms<T> {
private:
	void preprocessing_(std::vector<T> &a)
	{
		std::reverse(a.begin(), a.end());
	}

	void merging_()
	{
		for (size_t j = 0, i; j < (int)numberOfBlocks_; ++j)
		{
			i = (int)numberOfBlocks_ - 1 - j;
			FileStorage<T> fromBlock(numberToName(i), sizeOfBlock_);
			vector<T> a;
			for (size_t j = 0; j < sizeOfBlock_ && fromBlock.canTakeData(); ++j)
				a.push_back(fromBlock.getData());
			for (size_t j = 0; j < a.size(); ++j)
				totalOut_->push(a[j]);
		}
	}
public:
	ExternalReverser(IDataSource<T> *in, IDataTransmitter<T> *out, unsigned int memoryInBlock) :
		ExternalAlgorithms(in, out, memoryInBlock) {}

};