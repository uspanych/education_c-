#pragma once
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"
#include "FSCreator.h"
#include "iostream"

using namespace std;


int main()
{
	WCHAR disk[] = L"\\\\.\\F:";
	WCHAR* path = disk;
	Fabric* FsCreator = new Fabric;

	FileSystemType1 FsType = FsCreator->DetectFileSystem(path);
	
	Base* FileSystem = FsCreator->CreateFileSystem(FsType, path);

	BYTE* buffer = new BYTE[FileSystem->cluster_size]{0};
	
#pragma pack(push,1)
	struct Cluster
	{
		UINT32 JPEG_s;
	};
#pragma pack(pop)

	Cluster* JPEG_find = new Cluster;

	for(ULONGLONG i=0; i<FileSystem->cluster_count; i++)
	{
		FileSystem->getClusterData(i, buffer);
		JPEG_find = (Cluster*)buffer;
		if (JPEG_find->JPEG_s == 0xe0ffd8ff)
		{
			std::cout << i << "\n";
		}
	}
	delete JPEG_find;
	delete[] buffer;
}