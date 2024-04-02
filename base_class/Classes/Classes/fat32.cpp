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
	this->getClusterInfo();
};

FAT32::~FAT32()
{
	CloseHandle(file_handle);
};

int FAT32::getClusterInfo()
{
	BYTE* read_buffer = new BYTE[sector_size];
	SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);

#pragma pack(push, 1) // это команда на запись структуры в памяти подряд
	struct BootRecordStruct
	{
		BYTE pass1[13];
		UINT8 sectors_count_cluster; // кол-во секторов в кластере
		UINT16 size_reserve; // 0x0E размер 2 байта
		UINT8 count_fattable; // 0x10 размер 1 байт
		BYTE pass3[15];
		UINT32 sectors_count;
		UINT32 size_fattable_sectors; // 0x24 размер 4 байта
	};
#pragma pack(pop)

	BootRecordStruct* struct_b;
	struct_b = (BootRecordStruct*)read_buffer;

	// размер зарезервированной области
	int size_reserve_section = int(struct_b->size_reserve) * sector_size;
	// кол-во таблиц фат
	int count_fat = int(struct_b->count_fattable);
	// размер таблицы FAT
	int size_fat = int(struct_b->size_fattable_sectors) * sector_size;
	// начало первого кластера
	cluster_begin = size_reserve_section + (count_fat * size_fat);
	cluster_size = struct_b->sectors_count_cluster * sector_size;
	this->cluster_count = (static_cast<unsigned long long>(struct_b->sectors_count) * sector_size - cluster_begin) / cluster_size;
	delete[] read_buffer;
	return 0;
}

void FAT32::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer)
{

	
	
// номер необходимого кластера
	unsigned __int64 startOffset = cluster_begin + cluster_size * (static_cast<unsigned long long>(cluster_number) - 2);
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
};


