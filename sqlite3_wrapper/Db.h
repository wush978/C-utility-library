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
#include <stdexcept>
#include <string>
#include <vector>

namespace SQLite3 {

class Db {

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

	static const char* getTypeName(const DataType data_type);
};


} /* namespace SQLite3 */
#endif /* DB_H_ */
