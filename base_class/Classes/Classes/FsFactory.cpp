#include "FsFactory.h"


#include <iostream>


void FsFactory::writeBufferData(BYTE* buffer) {
	DWORD dwPtr = SetFilePointer(
		this->file_handle,
		0,
		0,
		FILE_BEGIN
	);

	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		// Obtain the error code. 
		DWORD dwError = GetLastError();
	};

	bool is_read = ReadFile(
		this->file_handle,
		buffer,
		2048,
		NULL,
		NULL
	);

	if (!is_read) {
		std::cout << "Can't read cluster data";
	};


}

FileSystems FsFactory::detectFileSystem() {
	FileSystems filesystem;
	BYTE* buffer = new BYTE[2048];
	this->writeBufferData(buffer);
	#pragma pack(push, 1) // это команда на запись структуры в памяти подряд
	struct Signature
	{
		BYTE jump[3];
		UINT32 NTFS_s;
		BYTE jump2[16];
		UINT16 fat_changer;
		BYTE jump3[485];
		UINT16 fat_s;
		BYTE jump4[568];
		UINT16 ext4_s;
	};
	#pragma pack(pop)

	Signature* parse = new Signature;
	parse = (Signature*)buffer;

	if (parse->NTFS_s == 1397118030) {
		filesystem = FileSystems::NTFS;
	}
	else if (parse->fat_s == 43605) {
		if (parse->fat_changer == 0) {
			filesystem = FileSystems::FAT32;
		}
		else filesystem = FileSystems::FAT16;
	}
	else if (parse->ext4_s == 21487)
	{
		filesystem = FileSystems::EXT4;
	}
	else filesystem = FileSystems::None;
	delete parse;
	return filesystem;
}

Base* FsFactory::getFileSystem() {
	FileSystems Fs = this->detectFileSystem();
	switch (Fs) {
	case FileSystems::NTFS:  
		return new NTFS(this->file_path);
	case FileSystems::FAT16:  return new Fat16(this->file_path);
	case FileSystems::FAT32:  return new FAT32(this->file_path);
	case FileSystems::EXT4:  return new EXT4(this->file_path);
	case FileSystems::None:  std::cout << "Couldn't detect filesystem\n";
		return NULL;
	}
}



FsFactory::FsFactory(WCHAR* file_path)
{
	this->file_path = file_path;
	this->file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	// Обработчик ошибок при открытии логического диска //
	if (this->file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		file_handle = NULL;
	}

}

FsFactory::~FsFactory()
{
	CloseHandle(file_handle);
}



/*
int main() {

	WCHAR file_path[] = L"\\\\.\\E:";
	WCHAR* file = file_path;
	FsFactory fs(file);
	Base* file_system = fs.getFileSystem();
	file_system->getClusterInfo();
	BYTE* buffer = new BYTE[32768];
	file_system->getClusterData(5, buffer);
	//for (int i; i <= file_system->cluster_count; i++) {
		// тут читаем все кластеры по порядку
	//}
	return 0;
}
*/