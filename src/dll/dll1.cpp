/*
 * dll.cpp
 *
 *  Created on: May 3, 2012
 *      Author: wush
 */

#include "dll.h"
#include "windows.h"
#include "winbase.h"
#include <iostream>

const TCHAR message[] = "This is from dll 2222";
const size_t message_size = 21;

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, PVOID fImpLoad) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			std::cout << "dll1: attached by process" << std::endl;
			break;
		case DLL_THREAD_ATTACH:
			std::cout << "dll1: attached by thread" << std::endl;
			break;
		case DLL_THREAD_DETACH:
			std::cout << "dll1: detached by thread" << std::endl;
			break;
		case DLL_PROCESS_DETACH:
			std::cout << "dll1: detached by process" << std::endl;
			break;
	}
	return(TRUE);  // Used only for DLL_PROCESS_ATTACH
}
