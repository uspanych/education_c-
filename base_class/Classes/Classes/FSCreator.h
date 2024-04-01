#pragma once
#include <Windows.h>
#include <iostream>
#include "Base.h"

enum class FileSystemType1 {
	EXT4, FAT16, FAT32, NTFS
};

class Fabric {

protected:
	
public:
	Base* CreateFileSystem(
		FileSystemType1 FsType,
		WCHAR* filename
	);
	FileSystemType1 DetectFileSystem(
		WCHAR* filename
	);
};