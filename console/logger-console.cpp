/*
 * logger-console.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include <iostream>
#include "../logger/Logger.h"

int main(int argc, char* argv[]) {
	logger::Logger l("logger.log");
	l.log("test");
	return 0;
}


