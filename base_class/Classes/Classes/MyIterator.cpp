#include "iostream"
#include "FsFactory.h"
#include "MyIterator.h"

Cluster::Cluster(WCHAR* file_path, ULONGLONG cluster_number) {
	this->cluster_number = cluster_number;
	this->file_path = file_path;
}

ClusterContainer::ClusterContainer() {
	this->cluster_count = 0;
	this->Items = new Cluster[1000];
}

void ClusterContainer::Add(Cluster& newItem) {
	this->Items[this->cluster_count++] = newItem;
}

ULONGLONG ClusterContainer::GetCount() const {
	return this->cluster_count;
}

Cluster ClusterContainer::GetByIndex(ULONGLONG index) {
	return this->Items[index];
}


ClusterIterator::ClusterIterator(Cluster* containerItems, ULONGLONG obj_count) {
	this->Pos = 0;
	this->Count = obj_count;
	this->itItems = containerItems;
}

void ClusterIterator::First() {
	this->Pos = 0;
}

void ClusterIterator::Next() {
	this->Pos++;
}

bool ClusterIterator::IsDone() const {
	return this->Pos >= this->Count;
}


BYTE* ClusterIterator::GetCurrent() const {
	
	Cluster example = itItems[Pos];
	FsFactory fs(example.file_path);
	Base* file_system = fs.getFileSystem();
	file_system->getClusterInfo();
	BYTE* buffer = new BYTE[file_system->cluster_size];
	file_system->getClusterData(example.cluster_number, buffer);
	return buffer;
}


Iterator<Cluster>* ClusterContainer::GetIterator() {
	return new ClusterIterator(Items, cluster_count);
}
