/*
	+----------------------------------------------------------------------+
	| PHP Version 6                                                        |
	+----------------------------------------------------------------------+
	| Copyright (c) 1997-2009 The PHP Group                                |
	+----------------------------------------------------------------------+
	| This source file is subject to version 3.01 of the PHP license,      |
	| that is bundled with this package in the file LICENSE, and is        |
	| available through the world-wide-web at the following url:           |
	| http://www.php.net/license/3_01.txt                                  |
	| If you did not receive a copy of the PHP license and are unable to   |
	| obtain it through the world-wide-web, please send a note to          |
	| license@php.net so we can mail you a copy immediately.               |
	+----------------------------------------------------------------------+
	| Author: Jim Winstead <jimw@php.net>                                  |
	+----------------------------------------------------------------------+
 */
/* $Id: base64.h,v 1.19 2008/12/31 11:12:36 sebastian Exp $ */

//#include <stdio.h>
//#include <stdlib.h>
//#ifdef __linux__
//#include <unistd.h>
//#endif
//#include <string.h>

//extern char *base64_decode(const char*,char **);
//extern char *base64_encode(const char*,char **);
#ifdef __cplusplus
extern "C" {
#endif
extern char *php_base64_decode(const unsigned char*,int,int*);
extern char *php_base64_encode(const unsigned char*,int,int*);
#ifdef __cplusplus
}
#endif
