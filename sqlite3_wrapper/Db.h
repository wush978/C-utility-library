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

#include "../encoding/hex.h"
#include <stdexcept>
#include <string>
#include <vector>
#include "sqlite3_wrapper.h"

namespace SQLite3 {

class Db {

	sqlite3* db_handle;

public:


	/**
	 * Open the file filename
	 */
	Db(const std::string& filename) throw(exception);
	/**
	 * Close the connection
	 */
	virtual ~Db();

	/**
	 * Only execute SQL without return value
	 */
	void exec(std::string& sql);

	/**
	 * execute SQL and put the result into retval
	 */
	void exec(std::string& sql, SQLite3::Table& retval);

	void createTable(
			const std::string& table_name,
			const TableDef& column_def,
			const bool is_temporary
			);

private:
	Db(const Db&);
	const Db& operator=(const Db&);

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
