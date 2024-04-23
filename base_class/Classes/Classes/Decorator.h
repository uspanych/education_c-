#pragma once
#include "Iterator.h"  

template<class Type>
class IteratorDecorator : public Iterator<Type> {
protected:
	Iterator<Type>* It;

public:
	IteratorDecorator(Iterator<Type>* it) {
		It = it;
	}

	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual BYTE* GetCurrent() const = 0;
};


class JpegIteratorDecorator : public IteratorDecorator<Cluster> {

protected:
	BYTE* buffer_bytes;

public:
	JpegIteratorDecorator(Iterator<Cluster>* it) : IteratorDecorator(it) {}

	void First() {
		It->First();
	}

	void Next() {

		ULONGLONG signature = 0xEEFFD8FF;

#pragma pack(push, 1)
		struct jpegStruct {
			UINT32 _bytes;
		};
#pragma pack(pop)

		jpegStruct* check = new jpegStruct;

		do {
			buffer_bytes = It->GetCurrent();
			check = (jpegStruct*)buffer_bytes;
			It->Next();
		} while (!It->IsDone() && check->_bytes == signature);

		delete check;

	}

	bool IsDone() const {
		return It->IsDone();
	}

	BYTE* GetCurrent() const {
		return It->GetCurrent();
	}

};
