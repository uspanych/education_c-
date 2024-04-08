#pragma once
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"
#include "FSCreator.h"
#include "iostream"
#include "MyIterator.h"

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

	ClusterContainer cs_container;
	cs_container.Add(cluster_5);

	Iterator <Cluster>* iterator = cs_container.GetIterator();

	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		BYTE* buffer = iterator->GetCurrent();
		std::cout << buffer;
	}

	return 0;
}
