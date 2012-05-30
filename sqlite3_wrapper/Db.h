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
#include "../encoding/hex.h"
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

	typedef struct {
		sqlite3_int64 _integer;
		double _float;
		std::string _buff;
	} Data;

	typedef struct {
		DataType data_type;
		Data data;
	} Entry;

	typedef std::vector<Entry> Row;

	typedef std::vector<Row> Rows;

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
			const bool is_temporary,
			Rows& retval
			);


private:
	Db(const Db&);
	const Db& operator=(const Db&);

	/**
	 * Perform sqlite3_step and sqlite3_finalize for a query
	 */
	void query(sqlite3_stmt*, Rows& retval);

	/**
	 * Retrieve the result after receive SQLITE_ROW from sqlite3_step()
	 */
	void getSQLResult(sqlite3_stmt*, int col_size, Rows& retval);

	/**
	 * Convert data_type to string
	 */
	static const char* getTypeName(const DataType data_type);

	const DataType int2datatype(const int src);
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
