#pragma once

#include<queue>
#include <string>
#include <fstream>
#include "sources.h"


template<class T>
class FileStorage {
private:
	std::fstream file_;
	std::queue<T> cash_;
	bool isWritting_;
	int objectInCash_;
	std::string nameOfFile;

	T preGetT_;
	T nowT_;
	bool haveInMemory_;

	T preGet_()
	{
		T some;
		deserialize(some, file_);
		return some;
	}

	T getCash_()
	{
		T some = cash_.front();
		cash_.pop();
		return some;
	}

	bool emptyCash_() const
	{
		return cash_.empty();
	}

	T getFromFile_()
	{
		if (!haveInMemory_)
			preGetT_ = preGet_();
		else
			preGetT_ = nowT_;
		haveInMemory_ = false;
		return preGetT_;
	}


	bool hasNextInFile_()
	{
		if (isWritting_)
			changeMode_();
		if (!haveInMemory_) //haveInMemory нужен, т.к. сначала мы пресчитываем элемент
		{
			nowT_ = preGet_();
			haveInMemory_ = true;
		}
		return !file_.eof();
	}

	void setFileMode_(bool modeOfFile) {
		isWritting_ = modeOfFile;
		file_.close();
		file_.open(nameOfFile.c_str(), (modeOfFile ? std::ios_base::out : std::ios_base::in) | std::ios_base::binary);
	}

	void changeMode_() {
		if (isWritting_ == false)
			setFileMode_(true); //to write
		else
			setFileMode_(false); //to read
	}

public:
	FileStorage(const std::string &nameOfBuffer, bool modeOfFile = true, int cashingSize = 1) : objectInCash_(cashingSize),
		isWritting_(modeOfFile), nameOfFile(nameOfBuffer), haveInMemory_(false) {
		setFileMode_(modeOfFile);
	}



	void changeCashSize(int n) {
		objectInCash_ = n;
	}

	std::string getName() {
		return this->nameOfFile;
	}	

	bool canTakeData()
	{

		return hasNextInFile_() || !emptyCash_();
	}


	T getData()
	{
		if (emptyCash_())
		{
			for (size_t i = 0; i < objectInCash_ && hasNextInFile_(); ++i)
				cash_.push(getFromFile_());
		}
		return getCash_();
	}
	
	void pushData(T &some)
	{
		if (!isWritting_)
			changeMode_();
		serialize(some, file_);
	}

	void close()
	{
		file_.close();
	}
	void removeFile()
	{
		remove (nameOfFile.c_str());
	}
	~FileStorage()
	{
		close();
		removeFile();
	}
};