//Файл описывает реализации методов класса наследника NTFS-----------------------//
//-------------------------------------------------------------------------------//
#include "NTFS.h"
#include "Base.h"
#include <iostream>
//Реализации виртуальных методов, описанных в базовом классе---------------------//
//-------------------------------------------------------------------------------//
int NTFS::getClusterSize(HANDLE file_handle) {
	DWORD lowerCase = SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	bool k = ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
	int cluster_X = read_buffer[13];
	cluster_size = sector_size * cluster_X;
	delete [] read_buffer;
	return cluster_size;
}
void NTFS::getClusterData(
	HANDLE file_handle,
	unsigned int cluster_number,
	BYTE* read_buffer) 
{
	unsigned __int64 startOffset = static_cast<unsigned long long>(cluster_number) * cluster_size;
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	DWORD lowerCase = SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	bool k = ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
//Реализация конструктора и деструктора класса-----------------------------------//
//-------------------------------------------------------------------------------//
NTFS::NTFS(WCHAR* file_path = NULL)
{
	path = file_path;
	cluster_size = NULL;
	file_handle = NULL;
}
NTFS::~NTFS()
{

}
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//