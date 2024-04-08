#pragma once
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"
#include "FSCreator.h"
#include "iostream"

using namespace std;


/* int main()
{
	WCHAR disk[] = L"\\\\.\\E:";
	WCHAR* path = disk;
	FSCreator* fabric = new FSCreator;
	Base* fs = fabric->CreateFS(path);
	
	BYTE* buffer = new BYTE[fs->cluster_size]{0};
}
*/