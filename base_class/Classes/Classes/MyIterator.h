#pragma once
#include <windows.h>


class Cluster {
public:
	Cluster() {};
	Cluster(WCHAR* file_path, ULONGLONG cluster_number);
	WCHAR* file_path;
	ULONGLONG cluster_number;
};

template<class Type>
class Iterator {	
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual BYTE* GetCurrent() const = 0;
};

class ClusterIterator: public Iterator<Cluster> {
protected:
	ULONGLONG Pos;
	ULONGLONG Count;
	Cluster* itItems;
public:
	ClusterIterator(Cluster* containerItems, ULONGLONG obj_count);
	void First();
	void Next();
	bool IsDone() const;
	BYTE* GetCurrent() const;
};

class ClusterContainer {
protected:
	ULONGLONG cluster_count;
	Cluster* Items;
public:
	ClusterContainer();
	Iterator<Cluster>* GetIterator();
	void Add(Cluster& newItem);
	ULONGLONG GetCount() const;
	Cluster GetByIndex(ULONGLONG index);
};