#pragma once
#include "Base.h"

class Fat16 : public Base {
public:
	Fat16(WCHAR* file_path) : Base(file_path) {};

	int cluster_offset;

	void getClusterData(
		ULONGLONG cluster_number,
		BYTE* read_buffer);

	int getClusterInfo();

	~Fat16() {};

};