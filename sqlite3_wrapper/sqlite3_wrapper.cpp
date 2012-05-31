/*
 * sqlite3_wrapper.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include "sqlite3_wrapper.h"

namespace SQLite3 {

	logger::Logger logger("sqlite3_wrapper.log");

	DataType getDataType(const int src) {
		switch(src) {
		case SQLITE_INTEGER:
			return Integer;
		case SQLITE_FLOAT:
			return Float;
		case SQLITE_TEXT:
			return Text;
		case SQLITE_BLOB:
			return Blob;
		case SQLITE_NULL:
			return Null;
		default:
			throw std::invalid_argument("Invalid input of Db::int2DataType");
		}
	}

	const char* getDataTypeName(const DataType data_type) {
		switch(data_type) {
		case Null:
			return "NULL";
		case Integer:
			return "INTEGER";
		case Float:
			return "REAL";
		case Text:
			return "TEXT";
		case Blob:
			return "BLOB";
		default:
			throw std::logic_error("Unknown DataType");
		}
	}
}


