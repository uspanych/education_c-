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
	virtual Type GetCurrent(BYTE* A) const = 0;
	ULONGLONG Pos = 0;
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

	Cluster GetCurrent(BYTE* A) const
	{
		EXT4 FS(Items[Pos].filename);
		FS.getClusterData(Items[Pos].cluster_number, A);
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