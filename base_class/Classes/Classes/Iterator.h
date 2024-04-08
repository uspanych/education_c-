#pragma once
#include <windows.h>


class Cluster {
public:
	Cluster() {};
	Cluster(WCHAR* file_path, UINT64 cluster_number);
	WCHAR* file_path;
	UINT64 cluster_number;
};

template<class Type>
class Iterator {
protected:
	Iterator() {};

public:
	virtual ~Iterator() {};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual BYTE* GetCurrent() const = 0;
};

class ClusterContainerIterator : public Iterator<Cluster> {
protected:
	UINT64 Pos;
	UINT64 Count;
	const Cluster* Items;

public:
	ClusterContainerIterator(const Cluster* containerItems, UINT64 clustersCount) {
		Items = containerItems;
		Count = clustersCount;
		Pos = 0;
	}
	void First() { Pos = 0;}
	void Next() { Pos++;}
	bool IsDone() const { return Pos >= Count; }
	BYTE* GetCurrent() const;
};

class ClusterContainer {
protected:
	UINT64 cluster_count;
	Cluster* Items;
public:
	ClusterContainer();
	Iterator<Cluster>* GetIterator();
	void AddItem(const Cluster& newItem);
	UINT64 GetCount() const;
};