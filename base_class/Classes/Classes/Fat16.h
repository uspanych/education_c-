#pragma once
#include "Base.h"

class Fat16 : public Base {
public:
	Fat16(WCHAR* file_path) : Base(file_path) {};

	void getClusterData(
		unsigned int cluster_number,
		BYTE* read_buffer);

	int getClusterSize();

	~Fat16() {};

};