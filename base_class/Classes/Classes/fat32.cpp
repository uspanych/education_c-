#include "fat32.h"
#include <iostream>

FAT32::FAT32(WCHAR* file_path)
{
	// ”казываем путь до файла, при инициализации класса //
	path = file_path;
	cluster_size = NULL;
	file_handle = NULL;
};

FAT32::FAT32()
{
	path = NULL;
	cluster_size = NULL;
	file_handle = NULL;
};

FAT32::~FAT32()
{

};

int FAT32::getClusterSize(HANDLE file_handle)
{
	BYTE* read_buffer = new BYTE[sector_size];
	SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
	int sectors_count = read_buffer[13];
	cluster_size = sectors_count * sector_size;
	delete[] read_buffer;
	return cluster_size;
}

void FAT32::getClusterData(
	HANDLE file_handle,
	unsigned int cluster_number,
	BYTE* read_buffer)
{
	int size_reserve_section;
	int count_fat;
	int size_fat;

	BYTE* buffer = new BYTE[sector_size];
	SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	ReadFile(file_handle, buffer, sector_size, NULL, NULL);

// рамзер зарезервированной области
	size_reserve_section = int((buffer[15]) << 8 | (buffer[14])) * sector_size;
// кол-во таблиц фат
	count_fat = buffer[16];
// размер таблицы FAT
	size_fat = int((buffer[39]) << 24 | (buffer[38]) << 16 | (buffer[37]) << 8 | (buffer[36])) * sector_size;
// начало первого кластера
	int cluster_begin = size_reserve_section + (count_fat * size_fat);
// номер необходимого кластера
	unsigned __int64 startOffset = cluster_begin + cluster_size * (static_cast<unsigned long long>(cluster_number) - 2);
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;
	delete[] buffer;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
};

int main()
{
	WCHAR path_file[] = L"\\\\.\\E:";
	WCHAR* pt_path_file = path_file;
	FAT32 GM(pt_path_file);

	int cluster_size = GM.getClusterSize(GM.getFileHandle());

	std::cout << "Cluster size: " << cluster_size << "\n";

	BYTE* buffer = new BYTE[cluster_size];

	GM.getClusterData(GM.getFileHandle(), 6, buffer);

	std::cout << buffer;

	delete[] buffer;
};

