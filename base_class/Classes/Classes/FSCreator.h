#pragma once
#include "Base.h"

enum class FSType {NTFS, FAT16, FAT32, EXT4};

class FSCreator
{
private:

	FSType DetectFS(BYTE* buffer);

public:

	Base* CreateFS(WCHAR* FSpath);

};

