#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include "sources.h"
#include "fileStorage.h"
#include "externalAlgo.h"

template<class T>
class ExternalSorter : public ExternalAlgorithms<T> {
public:
	ExternalSorter(IDataSource<T> *in, IDataTransmitter<T> *out, int memoryInBlock) :
		ExternalAlgorithms(in, out, memoryInBlock) {}
	void preprocessing(std::vector<T> &a)
	{
		std::sort(a.begin(), a.end());
	}
	void merging() {
		vector<FileStorage<T>*> buffers;
		std::set<std::pair<T, int> > mySet;
		vector<T> blockToOut;
		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			buffers.push_back(new FileStorage<T>(numberToName(i), sizeOfBlock_ / numberOfBlocks_));
		}
		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			mySet.insert(std::make_pair(buffers[i]->getData(), i));
		}
		while (!mySet.empty())
		{
			std::pair <T, int> tmp = *mySet.begin();
			mySet.erase(mySet.begin());
			int ind = tmp.second;
			blockToOut.push_back(tmp.first);
			if (buffers[ind]->canTakeData())
				mySet.insert(std::make_pair(buffers[ind]->getData(), ind));
			if (blockToOut.size() > sizeOfBlock_ / numberOfBlocks_)
				printVector(blockToOut, totalOut_);
		}
		printVector(blockToOut, totalOut_);

		for (size_t i = 0; i < numberOfBlocks_; ++i)
		{
			buffers[i]->close();
			delete buffers[i];
		}
	}
};
