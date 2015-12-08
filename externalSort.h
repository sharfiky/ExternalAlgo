#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"
#include "externalAlgo.h"

template<class T>
class ExternalSorter : public ExternalAlgorithms<T> {
private:
	void preprocessing_(std::vector<T> &a)
	{
		std::sort(a.begin(), a.end());
	}
	void merging_() {
		std::set<std::pair<T, int> > mySet;
		
		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			mySet.insert(std::make_pair(buffers_[i]->getData(), i));
		}
		while (!mySet.empty())
		{
			std::pair <T, int> tmp = *mySet.begin();
			mySet.erase(mySet.begin());
			int ind = tmp.second;
			totalOut_->push(tmp.first);
			if (buffers_[ind]->canTakeData())
				mySet.insert(std::make_pair(buffers_[ind]->getData(), ind));
		}

		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			buffers_[i]->close();
			delete buffers_[i];
		}
	}
public:
	ExternalSorter(IDataSource<T> *in, IDataTransmitter<T> *out, int memoryInBlock) :
		ExternalAlgorithms(in, out, memoryInBlock) {}
	
};
