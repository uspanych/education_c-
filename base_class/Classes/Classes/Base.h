#pragma once
#include <windows.h>

class Base {
public:
	Base(WCHAR* file_path);

	// Путь до файла
	WCHAR* file;

	// Функция положит в память содержимое кластера
	virtual void setClusterData(WCHAR* cluster_data) const = 0;

	// Функция вернет приватную перменную, содержащую размер кластера 
	virtual int getClusterSize() const = 0;


	HANDLE getFileHandle();


protected:
	// Сюда нужано положить размер кластера, вычисленный в дочернем классе
	int cluster_size;
	HANDLE file_handle;
};
