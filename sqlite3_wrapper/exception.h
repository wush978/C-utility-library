/*
 * exception.h
 *
 *  Created on: 2012/5/30
 *      Author: wush
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "sqlite3.h"
#include <exception>

namespace SQLite3 {

class exception: public std::exception {
	const char* message;
public:
	exception(sqlite3* db);
	explicit exception(const int error_code);
	explicit exception(const char* msg);
	virtual ~exception() throw();
	virtual const char* what() throw();
};

} /* namespace SQLite3 */
#endif /* EXCEPTION_H_ */
