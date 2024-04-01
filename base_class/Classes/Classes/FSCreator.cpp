#include <iostream>
#include <Windows.h>
#include "FSCreator.h"
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"


Base* Fabric::CreateFileSystem(
	FileSystemType1 FsType,
	WCHAR* filename)
{
	switch (FsType)
	{
	case FileSystemType1::EXT4: return new EXT4(filename);
	case FileSystemType1::NTFS: return new NTFS(filename);
		//case FileSystemType1::FAT16: return new Fat16(filename);
		//case FileSystemType1::FAT32: return new FAT32(filename);

	default: return NULL;
	}

};

FileSystemType1 Fabric::DetectFileSystem(WCHAR* filename) {
	HANDLE file_handle = CreateFileW(
		filename,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	BYTE* read_buffer = new BYTE[1536];
	ReadFile(file_handle, read_buffer, 1536, NULL, NULL);

#pragma pack(push, 1)
	struct FS_DETECTOR {
		BYTE jump1[3];
		UINT32 NTFS;
		BYTE jump2[15];
		UINT16 FAT_detect;
		BYTE jump3[486];
		UINT16 FAT;
		BYTE jump4[568];
		UINT16 EXT4;
	};
#pragma pack(pop)

	FS_DETECTOR* A = new FS_DETECTOR;
	A = (FS_DETECTOR*)read_buffer;

	if (A->NTFS == 0x5346544E)
	{
		return FileSystemType1::NTFS;
	}
	else if (A->FAT == 0xAA55)
	{
		if (A->FAT_detect == 0x0)
		{
			return FileSystemType1::FAT32;
		}
		else
			return FileSystemType1::FAT16;
	}
	else if (A->EXT4 == 0xEF53)
	{
		return FileSystemType1::EXT4;
	}


};

