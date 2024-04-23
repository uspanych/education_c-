#include "MyIterator.h"

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


class SampleDecoratorPDF : public IteratorDecorator<Cluster> {

protected:
	BYTE* buffer_bytes;

public:
	SampleDecoratorPDF(Iterator<Cluster>* it) : IteratorDecorator(it) {}

	void First() {
		It->First();
	}

	void Next() {
		#pragma pack(push, 1)
		struct pdfCheck {
			UINT32 pdf_bytes;
			UINT8 pdf_bytes_2; 
		};
		#pragma pack(pop)

		pdfCheck* check = new pdfCheck;

		do {
			buffer_bytes = It->GetCurrent();
			check = (pdfCheck*)buffer_bytes;
			It->Next();
		} while (!It->IsDone() && check->pdf_bytes != 0x25504446 && check->pdf_bytes_2 != 0x2d);

		delete check;
		
	}
	
	bool IsDone() const {
		return It->IsDone();
	}

	BYTE* GetCurrent() const {
		return It->GetCurrent();
	}

};
