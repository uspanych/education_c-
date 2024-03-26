//Файл описывает реализации методов класса наследника EXT4-----------------------//
//-------------------------------------------------------------------------------//
#include "EXT4.h"
#include "Base.h"
#include <iostream>
#include <cmath>
//Реализации виртуальных методов, описанных в базовом классе---------------------//
//-------------------------------------------------------------------------------//
int EXT4::getClusterSize(HANDLE file_handle) {
	SetFilePointer(file_handle, 1024, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);

	int LB_power = int((unsigned char)(read_buffer[27]) << 24 |
		(unsigned char)(read_buffer[26]) << 16 |
		(unsigned char)(read_buffer[25]) << 8 |
		(unsigned char)(read_buffer[24]));

	cluster_size = pow(2, (10 + LB_power));

	delete[] read_buffer;
	return cluster_size;
}
void EXT4::getClusterData(
	HANDLE file_handle,
	unsigned int cluster_number,
	BYTE* read_buffer)
{
	unsigned __int64 startOffset = static_cast<unsigned long long>(cluster_number) * cluster_size;
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
//Реализация конструктора и деструктора класса-----------------------------------//
//-------------------------------------------------------------------------------//
EXT4::EXT4(WCHAR* file_path = NULL)
{
	path = file_path;
	cluster_size = NULL;
	file_handle = NULL;
}
EXT4::~EXT4()
{

}
//-------------------------------------------------------------------------------//
//----------