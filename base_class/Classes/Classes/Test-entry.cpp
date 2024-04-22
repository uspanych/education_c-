#pragma once
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"
#include "FSCreator.h"
#include "iostream"
#include "MyDecorator.h"

using namespace std;


/*
int main()
{
	WCHAR disk[] = L"\\\\.\\C:";
	WCHAR* path = disk;
	FSCreator* fabric = new FSCreator;
	Base* fs = fabric->CreateFS(path);
	
	BYTE* buffer = new BYTE[fs->cluster_size]{0};
	
#pragma pack(push,1)
	struct Cluster
	{
		UINT32 JPEG_s;
	};
#pragma pack(pop)
	Cluster* jpeg_finder = new Cluster;

	for(ULONGLONG i=0; i<1000; i++)
	{
		fs->getClusterData(i, buffer);
		jpeg_finder = (Cluster*)buffer;
		if (jpeg_finder->JPEG_s == 0xe0ffd8ff)
		{
			std::cout << i << "\n";
		}
	}
	delete jpeg_finder;
	delete[] buffer;
}
*/


int main() {
	WCHAR disk[] = L"\\\\.\\E:";
	WCHAR* path = disk;
	Cluster cluster_5(path, 5);
	Cluster cluster_7(path, 7);
	Cluster cluster_25(path, 25);

	ClusterContainer cs_container;
	cs_container.Add(cluster_5);
	cs_container.Add(cluster_7);
	cs_container.Add(cluster_25);

	Iterator <Cluster>* iterator = cs_container.GetIterator();

	IteratorDecorator<Cluster>* sample_decorator = new SampleDecoratorPDF(iterator);

	for (sample_decorator->First(); !sample_decorator->IsDone(); sample_decorator->Next()) {
		std::cout << iterator->Pos;
	}

	return 0;
}
