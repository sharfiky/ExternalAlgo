#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"
#include "externalAlgo.h"
#include "serialize.h"

template<class T>
class ExternalSorter : public ExternalAlgorithms<T> {
private:
	void preprocessing_(std::vector<T> &a)
	{
		std::sort(a.begin(), a.end());
	}
	void merging_() {
		std::priority_queue<std::pair<T, int> > mySet;
		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			mySet.push(std::make_pair(buffers_[i]->getData(), i));
		}
		while (!mySet.empty())
		{
			std::pair <T, int> tmp = mySet.top();
			mySet.pop();
			int ind = tmp.second;
			totalOut_->push(tmp.first);
			if (buffers_[ind]->canTakeData())
				mySet.push(std::make_pair(buffers_[ind]->getData(), ind));
		}
	}
public:
	ExternalSorter(IDataSource<T> *in, IDataTransmitter<T> *out, int memoryInBlock) :
		ExternalAlgorithms(in, out, memoryInBlock) {}
	
};
