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
		for (int i = numberOfBlocks_ - 1; i >= 0; --i)
		{
			vector<T> a;
			for (size_t j = 0; j < sizeOfBlock_ && buffers_[i]->canTakeData(); ++j)
				a.push_back(buffers_[i]->getData());
			for (size_t j = 0; j < a.size(); ++j)
				totalOut_->push(a[j]);
		}
	}
public:
	ExternalReverser(IDataSource<T> *in, IDataTransmitter<T> *out, unsigned int memoryInBlock) :
		ExternalAlgorithms(in, out, memoryInBlock) {}

};