#include <iostream>
#include "fat32.h"
#include "Iterator.h"

using namespace std;

Cluster::Cluster(WCHAR* file_path, UINT64 cluster_number) {
	this->cluster_number = cluster_number;
	this->file_path = file_path;
}

ClusterContainer::ClusterContainer() {
	this->cluster_count = 0;
	this->Items = new Cluster[1000];
}

Iterator<Cluster>* ClusterContainer::GetIterator() {
	return new ClusterContainerIterator(this->Items, this->cluster_count);
}

void ClusterContainer::AddItem(const Cluster& newItem) {
	this->Items[this->cluster_count++] = newItem;
}

UINT64 ClusterContainer::GetCount() const {
	return this->cluster_count;
}


BYTE* ClusterContainerIterator::GetCurrent() const {
	Cluster myCluster = Items[Pos];
	FAT32 fs(myCluster.file_path);
	fs.getClusterInfo();
	BYTE* buffer = new BYTE[fs.cluster_size];
	fs.getClusterData(myCluster.cluster_number, buffer);
	return buffer;
}


int main() {
	WCHAR path[] = L"\\\\.\\E:";
	WCHAR* p_path = path;
	Cluster cluster_num(p_path, 6);

	ClusterContainer myContainer;
	myContainer.AddItem(cluster_num);

	Iterator <Cluster>* it = myContainer.GetIterator();

	for (it->First(); !it->IsDone(); it->Next()) {
		BYTE* buffer = it->GetCurrent();
		cout << buffer;
	}
	return 0;
}