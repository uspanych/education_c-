#pragma once
#include <windows.h>
#include <string.h>
#include "EXT4.h"
using namespace std;

class Cluster
{
public:
	Cluster() = default;
	Cluster(
		ULONGLONG cluster_num,
		WCHAR* file_path);
	ULONGLONG cluster_number;
		WCHAR* filename;
		
};

template<class Type> class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Type GetCurrent() const = 0;
	ULONGLONG Pos = 0;
	BYTE* buffer = new BYTE[4096];
};

class ContainerIterator : public Iterator<Cluster>
{
private:
	const Cluster* Items;
	int Count;
public:

	ContainerIterator(const Cluster* containerItems, int objectsCount)
	{
		Items = containerItems;
		Count = objectsCount;
	}

	void First() 
	{
		Pos = 0;
	}

	void Next()
	{
		Pos++;
	}
	
	bool IsDone() const
	{
		return (Pos >= Count);
	}

	Cluster GetCurrent() const
	{
		EXT4 FS(Items[Pos].filename);
		FS.getClusterData(Items[Pos].cluster_number, this->buffer);
		return Items[Pos];
	}
};

class Container
{
private:
	Cluster* Items;
	ULONGLONG Count;

public:
	Container();
	void AddItem(const Cluster& newItem);
	int GetCount() const;
	Iterator<Cluster>* GetIterator();
};

template<class Type>
class IteratorDecorator : public Iterator<Type>
{
protected:
	Iterator<Type> *It;

public:
	IteratorDecorator(Iterator<Type> *it)
	{
		It = it;
	}



	virtual ~IteratorDecorator() { delete It; };
	virtual void First() { It->First(); };
	virtual bool IsDone() const { return It->IsDone(); };
	virtual Type GetCurrent() const { return It->GetCurrent(); };


	void Next()
	{
		ULONGLONG TargetBytes = 0x0A1A0A0D474E5089;

#pragma pack(push, 1)
		struct Bytes {
			ULONGLONG MagicBytes;
		};
#pragma pack(pop)

		Bytes* A = (Bytes*)(It->buffer);
		do
		{	
			It->GetCurrent();
			A = (Bytes*)(It->buffer);


			It->Next();
		} while (!It->IsDone() && 
			A->MagicBytes != TargetBytes);
	}

	IteratorDecorator() = default;
};