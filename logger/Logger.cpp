/*
 * Logger.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include "Logger.h"

namespace logger {

Logger::Logger(const std::string& filename) : _f(filename.c_str(), std::ofstream::out | std::ofstream::app) {
}

Logger::~Logger() {
	_f.close();
}

void Logger::log(const std::string& message) {
	_f << "[" << boost::posix_time::microsec_clock::local_time() << "] " << message << std::endl;
}

} /* namespace logger */
