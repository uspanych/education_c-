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
	WCHAR disk[] = L"\\\\.\\C:";
	WCHAR* path = disk;
	FSCreator* fabric = new FSCreator;
	Base* fs = fabric->CreateFS(path);
	std::cout << fs->getClusterSize();
	
}
