/*
 * dll.h
 *
 *  Created on: May 3, 2012
 *      Author: wush
 */

#ifndef DLL_H_
#define DLL_H_

#include <string>

#ifdef dll_dll_EXPORT
	#define MYLIB_EXPORT __declspec(dllexport)
#else
	#define MYLIB_EXPORT __declspec(dllimport)
#endif

extern const MYLIB_EXPORT std::string message;


#endif /* DLL_H_ */
