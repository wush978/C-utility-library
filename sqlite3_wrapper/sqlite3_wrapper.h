/*
 * sqlite3_wrapper.h
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#ifndef SQLITE3_WRAPPER_H_
#define SQLITE3_WRAPPER_H_

#include "sqlite3.h"

#include "exception.h"
#ifdef ENABLE_LOG
#include "../logger/Logger.h"
#endif //ENABLE_LOG


namespace SQLite3 {
#ifdef ENABLE_LOG
	extern logger::Logger logger;
#endif // ENABLE_LOG

	typedef enum{
		Integer = SQLITE_INTEGER,
		Float = SQLITE_FLOAT,
		Text = SQLITE_TEXT,
		Blob = SQLITE_BLOB,
		Null = SQLITE_NULL,
	} DataType;

	DataType getDataType(const int src);

	const char* getDataTypeName(const DataType data_type);

	inline void log(const std::string& message) {
#ifdef ENABLE_LOG
		logger.log(message);
#endif
	}

}

#include "Row.h"
#include "Table.h"
#include "Db.h"

#endif /* SQLITE3_WRAPPER_H_ */
