/*
 * Logger.h
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include "boost/date_time/posix_time/posix_time.hpp"

namespace logger {

class Logger {
	std::ofstream _f;
public:
	Logger(const std::string& filename);
	virtual ~Logger();
	void log(const std::string& message);
};

} /* namespace logger */
#endif /* LOGGER_H_ */
