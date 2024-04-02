//Файл описывает реализации методов класса наследника EXT4-----------------------//
//-------------------------------------------------------------------------------//
#include "EXT4.h"
#include "Base.h"
#include <iostream>
#include <cmath>
//Реализации виртуальных методов, описанных в базовом классе---------------------//
//-------------------------------------------------------------------------------//
int EXT4::getClusterInfo() {
	SetFilePointer(file_handle, 1024, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);

	unsigned __int64 LB_power = ReadBytes(read_buffer, 24, 4);

	cluster_size = (int)pow(2, (10 + LB_power));

	delete[] read_buffer;
	return cluster_size;
}
void EXT4::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer)
{
	unsigned __int64 startOffset = static_cast<unsigned long long>(cluster_number) * cluster_size;
	LARGE_INTEGER sectorOffset{};
	sectorOffset.QuadPart = startOffset;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
//Реализация конструктора и деструктора класса-----------------------------------//
//-------------------------------------------------------------------------------//
EXT4::EXT4(WCHAR* file_path)
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
EXT4::~EXT4()
{

}
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//