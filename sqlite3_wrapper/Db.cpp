/*
 * Db.cpp
 *
 *  Created on: 2012/5/30
 *      Author: wush
 */

#include "sqlite3_wrapper.h"

namespace SQLite3 {
Db::Db(const std::string& filename) throw(exception) : db_handle(NULL) {
	int error_code = sqlite3_open(filename.c_str(), &db_handle);
	if (!db_handle) {
		throw exception("Failed to allocate memory to open the connection!");
	}
	if (error_code != SQLITE_OK) {
		throw exception(error_code);
	}
}

Db::~Db() {
	sqlite3_close(db_handle);
}

void Db::exec(std::string& sql) {
	log(sql);
	this->check(sqlite3_exec(db_handle, sql.c_str(), NULL, NULL, NULL));
}

void Db::createTable(const Table& table) {
	table.assertNonMutable();
	std::string sql;
	if (!table.check()) {
		throw std::invalid_argument("The Table definition is invalid");
	}
	sql.append("CREATE ");
	if(table.isTemporary()) {
		sql.append("TEMPORARY ");
	}
	sql.append(" TABLE ").append(table.getName()).append("( ");
	if (table.isAutoPK()) {
		sql.append("id INTEGER PRIMARY KEY ASC, ");
	}
	const std::vector<std::string>& column_name(table.getColumnName());
	const std::vector<DataType>& column_type(table.getColumnType());
	for(size_t i; i < column_name.size();i++) {
		sql.append(column_name[i]). append(" ").append(getDataTypeName(column_type[i])).append(" ");
		if (i == table.getPK() & !table.isAutoPK()) {
			sql.append("PRIMARY KEY, ");
		}
		else {
			sql.append(", ");
		}
	}
	sql.resize(sql.size() - 2);
	sql.append(");");
	this->exec(sql);
}
//void Db::createTable(
//		const std::string& table_name,
//		const TableDef& column_def,
//		const bool is_temporary
//		) {
//	std::string sql_statement("CREATE ");
//	if (is_temporary) {
//		sql_statement.append("TEMPORARY ");
//	}
//	sql_statement.append("TABLE ").append(table_name).append("( id INTEGER PRIMARY KEY ASC, ");
//	for(std::vector<ColumnDef>::const_iterator i(column_def.begin()); i != column_def.end();i++) {
//		sql_statement.append(i->column_label).append(" ").append(getDataTypeName(i->column_type)).append(", ");
//	}
//	sql_statement.resize(sql_statement.size() - 2);
//	sql_statement.append(");");
//	this->exec(sql_statement);
//}

} /* namespace SQLite3 */
