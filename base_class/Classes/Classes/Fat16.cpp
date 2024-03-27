#include "Fat16.h"
#include <iostream>
#include <typeinfo>

void Fat16::getClusterData(
	unsigned int cluster_number,
	BYTE* read_buffer
)
{
	DWORD dwPtr  = SetFilePointer(
		file_handle,
		0,
		0,
		FILE_BEGIN
	);

	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		// Obtain the error code. 
		DWORD dwError = GetLastError();
	}

	BYTE* buffer = new BYTE[sector_size];
	bool is_read = ReadFile(
		file_handle,
		buffer,
		sector_size,
		NULL,
		NULL
	);

	if (!is_read) {
		std::cout << "Can't read cluster data";
	}

	// Размер загрузочного сектора
	int load_sector_size = buffer[14] * this->sector_size;

	// Размер таблицы фат
	int fat_table_size = buffer[22] * this->sector_size;

	// Кол-во таблиц фат
	int fat_table_count = buffer[16];

	// Таблицы фат
	int fat_all_size = fat_table_size * fat_table_count;

	// Количество записей в корневом каталоге
	uint16_t count_root_record = uint16_t((buffer[18] << 8)) + uint16_t(buffer[17]);
	
	// Размер корневого каталога
	int size_root_directory = count_root_record * 32;

	// Смещение первого кластера
	int cluster_offset_start = load_sector_size + fat_all_size + size_root_directory;
	
	// Смещение нужного кластера
	cluster_offset_start += this->cluster_size * (cluster_number - 2);

	DWORD dwPtr1 = SetFilePointer(
		file_handle,
		cluster_offset_start,
		0,
		FILE_BEGIN
	);

	if (dwPtr1 == INVALID_SET_FILE_POINTER)
	{
		// Obtain the error code. 
		DWORD dwError = GetLastError();
	}

	bool is_read1 = ReadFile(
		file_handle,
		read_buffer,
		this->cluster_size,
		NULL,
		NULL
	);
	
	if (!is_read1) {
		std::cout << "Can't read cluster data";
	}
	

}

int Fat16::getClusterSize()
{	
	SetFilePointer(
		file_handle,
		0,
		0,
		FILE_BEGIN
	);
	BYTE* buffer = new BYTE[sector_size];

	bool is_read = ReadFile(
		file_handle,
		buffer,
		sector_size,
		NULL,
		NULL
		);
	
	if (is_read) {
		unsigned __int64 sec_count = ReadBytes(buffer, 13, 1);

		delete[] buffer;

		this->cluster_size = sec_count * sector_size;
		return cluster_size;
	}
	else {
		std::cout << "Can't read file";
		return 1;
	}	
}

