/*
 * exe.cpp
 *
 *  Created on: May 3, 2012
 *      Author: wush
 */

//#define UNICODE
//#define _UNICODE

#include "windows.h"
#include "winbase.h"
#include "TChar.h"
#include <iostream>
#include <string>
#include <stdexcept>

typedef std::basic_string<TCHAR> TSTRING;

struct HMODULE_CONTAINER
{
	HMODULE hmodule;
	HMODULE_CONTAINER(HMODULE src) : hmodule(src) { }
	~HMODULE_CONTAINER() { FreeLibrary(hmodule); }
};

int main()
{
	try {
		HMODULE_CONTAINER dll(GetModuleHandle(_TEXT("dll_1")));
		if (!dll.hmodule) {
			std::cout << _TEXT("Loading library dll_1.dll") << std::endl;
			dll.hmodule = LoadLibrary(_TEXT("dll_1"));
		}
		TSTRING file_name(100, 0);
		GetModuleFileName(dll.hmodule, &file_name[0], file_name.size());
		std::cout << _TEXT("Loaded DLL Name: ") << file_name.c_str() << std::endl;

		const PTCHAR message = reinterpret_cast<PTCHAR>(GetProcAddress(dll.hmodule, "?message@@3QBDB"));
		if (!message) {
			std::cerr << _TEXT("Failed to load message: ");
			throw std::exception("");
		}

		const size_t *message_size = reinterpret_cast<size_t*>(GetProcAddress(dll.hmodule, "?message_size@@3IB"));
		if (!message_size) {
			std::cerr << _TEXT("Failed to load message_size: ");
			throw std::exception("");
		}

		TSTRING message_str(message, *message_size);
		std::cout << message_str << std::endl;
		return 0;
	}
	catch (std::exception &e) {
		HLOCAL hlocal = NULL;
		BOOL f0k = FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
				NULL, GetLastError(), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				(LPTSTR) &hlocal, 0, NULL);
		std::cerr << (PCTSTR) LocalLock(hlocal) << std::cout;
		return 1;
	}
}




