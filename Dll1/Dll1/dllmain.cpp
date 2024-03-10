#include "Header.h"
#include "iostream"

void __stdcall user_name(const char* my_data) {
	std::cout << my_data << "\n";
}

void __stdcall group_number(int group_number) {
	std::cout << "RI-" << group_number;
}


