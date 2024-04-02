#pragma once
#include <windows.h>
#include "Base.h"
#include "Fat16.h"
#include "Fat32.h"
#include "NTFS.h"
#include "Ext4.h"

enum class FileSystems {
	FAT16, NTFS, EXT4, FAT32, None
};


class FsFactory {
protected:
	BYTE* buffer;
	HANDLE file_handle;
	WCHAR* file_path;

	void writeBufferData(BYTE* buffer);
	FileSystems detectFileSystem();

public:
	
	Base* getFileSystem();

	FsFactory(WCHAR* file_path);
	~FsFactory();

};

