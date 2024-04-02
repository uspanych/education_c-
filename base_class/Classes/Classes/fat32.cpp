#include "fat32.h"
#include <iostream>

FAT32::FAT32(WCHAR* file_path)
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
};

FAT32::~FAT32()
{

};

int FAT32::getClusterInfo()
{
	BYTE* read_buffer = new BYTE[sector_size];
	SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
	unsigned __int64 sectors_count = ReadBytes(read_buffer, 13, 1);
	cluster_size = sectors_count * sector_size;
	delete[] read_buffer;
	return cluster_size;
}

void FAT32::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer)
{
	unsigned __int64 size_reserve_section;
	unsigned __int64 count_fat;
	unsigned __int64 size_fat;

	BYTE* buffer = new BYTE[sector_size];
	SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	ReadFile(file_handle, buffer, sector_size, NULL, NULL);

// рамзер зарезервированной области
	size_reserve_section = ReadBytes(buffer, 14, 2) * sector_size;
// кол-во таблиц фат
	count_fat = ReadBytes(buffer, 16, 1);
// размер таблицы FAT
	size_fat = ReadBytes(buffer, 36, 4) * sector_size;
// начало первого кластера
	int cluster_begin = size_reserve_section + (count_fat * size_fat);
// номер необходимого кластера
	unsigned __int64 startOffset = cluster_begin + cluster_size * (static_cast<unsigned long long>(cluster_number) - 2);
	LARGE_INTEGER sectorOffset{};
	sectorOffset.QuadPart = startOffset;
	delete[] buffer;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
};

