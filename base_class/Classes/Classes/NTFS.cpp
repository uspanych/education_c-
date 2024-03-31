//Файл описывает реализации методов класса наследника NTFS-----------------------//
//-------------------------------------------------------------------------------//
#include "NTFS.h"
#include "Base.h"
#include <iostream>
//Реализации виртуальных методов, описанных в базовом классе---------------------//
//-------------------------------------------------------------------------------//
int NTFS::getClusterSize() {
	DWORD lowerCase = SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	bool k = ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
	unsigned __int64 cluster_multiplier = ReadBytes(read_buffer, 13, 1);
	cluster_size = sector_size * cluster_multiplier;
	delete [] read_buffer;
	return cluster_size;
}
void NTFS::getClusterData(
	unsigned int cluster_number,
	BYTE* read_buffer) 
{
	unsigned __int64 startOffset = static_cast<unsigned long long>(cluster_number) * cluster_size;
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
}
NTFS::~NTFS()
{

}
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//