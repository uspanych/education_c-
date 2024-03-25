#pragma once
#include "Base.h"

class Fat16 : public Base {
public:
	Fat16(WCHAR* file_path) : Base(file_path) {};

	void getClusterData(
		HANDLE file_handle,
		unsigned int cluster_number,
		BYTE* read_buffer);

	int getClusterSize(HANDLE file_handle);

	~Fat16() {};

};