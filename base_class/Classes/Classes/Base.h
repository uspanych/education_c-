#pragma once
#include <windows.h>

class Base {
public:
	Base(WCHAR* file_path);

	// ���� �� �����
	WCHAR* file;

	// ������� ������� � ������ ���������� ��������
	virtual void setClusterData(WCHAR* cluster_data) const = 0;

	// ������� ������ ��������� ���������, ���������� ������ �������� 
	virtual int getClusterSize() const = 0;


	HANDLE getFileHandle();


protected:
	// ���� ������ �������� ������ ��������, ����������� � �������� ������
	int cluster_size;
	HANDLE file_handle;
};
