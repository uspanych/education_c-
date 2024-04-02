#include "FSCreator.h"

#include <iostream>
#include <Windows.h>

FStype FSCreator::DetectFS(BYTE* buffer)
{
	FStype filesystem;

	#pragma pack(push, 1) // это команда на запись структуры в памяти подряд
	struct Signature
	{
		BYTE jump[3];
		UINT32 NTFS_s;
		BYTE jump2[15];
		UINT16 fat_changer;
		BYTE jump3[486];
		UINT16 fat_s;
		BYTE jump4[568];
		UINT16 ext4_s;
	};
	#pragma pack(pop)
	Signature* parse = new Signature;
	parse = (Signature*)buffer;
	if (parse->NTFS_s == 1397118030)
	{
		filesystem = FStype::NTFS;
	}
	else if (parse->fat_s == 43605)
	{
		if (parse->fat_changer == 0)
		{
			filesystem = FStype::FAT32;
		}
		else
			filesystem = FStype::FAT16;
	}
	else if (parse->ext4_s == 21487)
	{
		filesystem = FStype::EXT4;
	}
	else
		filesystem = FStype::None;
	delete parse;
	return filesystem;
}


Base* FSCreator::CreateFS(WCHAR* FSpath)
{
	HANDLE handle = CreateFile(
		FSpath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	BYTE* buffer = new BYTE[2048];
	DWORD pointerstatus = SetFilePointer(handle, 0, 0, FILE_BEGIN);
	BOOL readstatus = ReadFile(handle, buffer, 2048, NULL, NULL);
	
	FStype filesystem = DetectFS(buffer);

	CloseHandle(handle);
	
	switch (filesystem)
	{
	case FStype::NTFS:
		return new NTFS(FSpath);
	case FStype::FAT32:
		return new FAT32(FSpath);
	/*case FStype::FAT16:
		return new Fat16(FSpath);
	
	case FStype::EXT4:
		return new EXT4(FSpath);
	case FStype::None:
		std::cout << "Couldn't detect filesystem\n";
		return NULL;*/
	}


	

}
