/*
 * Db.h
 *
 * I only wrap the UTF-8 encoding part
 *
 *  Created on: 2012/5/30
 *      Author: wush
 */

#ifndef DB_H_
#define DB_H_

#include "sqlite3.h"
#include "exception.h"
#ifdef ENABLE_LOG
#include <fstream>
#endif
#include <stdexcept>
#include <string>
#include <vector>

namespace SQLite3 {

class Db {

#ifdef ENABLE_LOG
	std::fstream log;
#endif
	sqlite3* db_handle;


public:

	typedef enum{
		Integer = SQLITE_INTEGER,
		Float = SQLITE_FLOAT,
		Text = SQLITE_TEXT,
		Blob = SQLITE_BLOB,
		Null = SQLITE_NULL,
	} DataType;


	typedef struct {
		DataType column_type;
		std::string column_label;
	} ColumnDef;

	/**
	 * Open the file filename
	 */
	Db(const std::string& filename) throw(exception);
	/**
	 * Close the connection
	 */
	virtual ~Db();

	void createTable(
			const std::string& table_name,
			const std::vector<ColumnDef>& column_def,
			const bool is_temporary = false
			);


private:
	Db(const Db&);
	const Db& operator=(const Db&);

	/**
	 * Perform sqlite3_step and sqlite3_finalize for a query
	 */
	void query(const sqlite3_stmt*);

	/**
	 * Convert data_type to string
	 */
	static const char* getTypeName(const DataType data_type);

	/**
	 * Check error
	 */
	inline void check(int src) {
		int error_code(src);
		if (error_code != SQLITE_OK) {
			throw exception(db_handle);
		}
	}
};


} /* namespace SQLite3 */
#endif /* DB_H_ */
