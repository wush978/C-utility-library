/*
 * dll.h
 *
 *  Created on: May 3, 2012
 *      Author: wush
 */

#ifndef DLL_H_
#define DLL_H_

#include "TChar.h"
#include <string>

#ifdef dll_1_EXPORTS
	#define MYLIB_EXPORT __declspec(dllexport)
#else
	#define MYLIB_EXPORT __declspec(dllimport)
#endif

extern const MYLIB_EXPORT TCHAR message[];
extern const MYLIB_EXPORT size_t message_size;


#endif /* DLL_H_ */
