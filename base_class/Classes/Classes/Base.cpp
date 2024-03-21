#include <iostream>
#include "Base.h"
#include <windows.h>


Base::Base(WCHAR* file_path) {
		// Указываем путь до файла, при инициализации класса
		file = file_path;
}

HANDLE Base::getFileHandle() {
	// Функция возвращает файловый дескриптор по указанному пути
	HANDLE file_hadle = CreateFileW(
		file,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	return file_hadle;
};


int main() {
	return 0;
}
