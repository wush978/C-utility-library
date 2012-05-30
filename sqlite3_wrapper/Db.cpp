/*
 * Db.cpp
 *
 *  Created on: 2012/5/30
 *      Author: wush
 */

#include "Db.h"

namespace SQLite3 {
Db::Db(const std::string& filename) throw(exception) : db_handle(NULL) {
#ifdef ENABLE_LOG
	log.open("db.log", std::fstream::in | std::fstream::out | std::fstream::app);
#endif //ENABLE_LOG
	int error_code = sqlite3_open(filename.c_str(), &db_handle);
	if (!db_handle) {
		throw exception("Failed to allocate memory to open the connection!");
	}
	if (error_code != SQLITE_OK) {
		throw exception(error_code);
	}
}

Db::~Db() {
#ifdef ENABLE_LOG
	log.close();
#endif //ENABLE_LOG
	sqlite3_close(db_handle);
}

void Db::createTable(
		const std::string& table_name,
		const std::vector<ColumnDef>& column_def,
		const bool is_temporary
		) {
	std::string sql_statement("CREATE ");
	if (is_temporary) {
		sql_statement.append("TEMPORARY ");
	}
	sql_statement.append("TABLE ").append(table_name).append("( id INTEGER PRIMARY KEY ASC, ");
	for(std::vector<ColumnDef>::const_iterator i(column_def.begin()); i != column_def.end();i++) {
		sql_statement.append(i->column_label).append(" ").append(Db::getTypeName(i->column_type)).append(", ");
	}
	sql_statement.resize(sql_statement.size() - 2);
	sql_statement.append(");");
#ifdef ENABLE_LOG
	log << "SQL: " << sql_statement << std::endl;
#endif //ENABLE_LOG
	sqlite3_stmt* pStmt;
#ifdef ENABLE_LOG
	log << "preparing..." << std::endl;
#endif //ENABLE_LOG
	this->check(sqlite3_prepare_v2(db_handle, sql_statement.c_str(), sql_statement.size() + 1, &pStmt, NULL));
#ifdef ENABLE_LOG
	log << "creating database..." << std::endl;
#endif //ENABLE_LOG
	this->query(pStmt);
#ifdef ENABLE_LOG
	log << "finalizing..." << std::endl;
#endif //ENABLE_LOG
	this->check(sqlite3_finalize(pStmt));
}

const char* Db::getTypeName(const DataType data_type) {
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
		return "";
	}
}

} /* namespace SQLite3 */
