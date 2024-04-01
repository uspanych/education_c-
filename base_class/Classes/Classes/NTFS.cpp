//Файл описывает реализации методов класса наследника NTFS-----------------------//
//-------------------------------------------------------------------------------//
#include "NTFS.h"
#include "Base.h"
#include <iostream>
//Реализации виртуальных методов, описанных в базовом классе---------------------//
//-------------------------------------------------------------------------------//
int NTFS::getClusterInfo() {
	DWORD lowerCase = SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	bool k = ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
#pragma pack(push,1)
	struct BootRecord
	{
		BYTE jump[13];
		UINT8 cluster_multiplier;
		BYTE jump2[26];
		UINT64 total_sectors;
	};
#pragma pack(pop)
	BootRecord* parse = new BootRecord;
	parse = (BootRecord*)read_buffer;
	cluster_size = sector_size * parse->cluster_multiplier;
	cluster_count = parse->total_sectors/parse->cluster_multiplier;
	return 0;
}
void NTFS::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer) 
{
	ULONGLONG startOffset = cluster_number * cluster_size;
	LARGE_INTEGER sectorOffset{0};
	sectorOffset.QuadPart = startOffset;

	DWORD lowerCase = SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	bool k = ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
//Реализация конструктора и деструктора класса-----------------------------------//
//-------------------------------------------------------------------------------//
NTFS::NTFS(WCHAR* file_path)
{
	cluster_size = NULL;
	file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	// Обработчик ошибок при открытии логического диска //
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		file_handle = NULL;
	}
	this->getClusterInfo();
}
NTFS::~NTFS()
{

}
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//