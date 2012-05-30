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
		const bool is_temporary,
		Rows& retval
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
	log << "querying..." << std::endl;
#endif //ENABLE_LOG
	this->query(pStmt, retval);
}

void Db::query(sqlite3_stmt* pStmt, Rows& retval) {
	int error_code;
	int is_continue(true);
	int col_size(sqlite3_column_count(pStmt));
#ifdef ENABLE_LOG
	log << "Cols: " << col_size << std::endl;
#endif //ENABLE_LOG
	while(is_continue) {
		error_code = sqlite3_step(pStmt);
		switch(error_code) {
		case SQLITE_BUSY:
#ifdef ENABLE_LOG
			log << "sqlite3_step return: SQLITE_BUSY" << std::endl;
#endif
			break;
		case SQLITE_DONE:
#ifdef ENABLE_LOG
			log << "sqlite3_step return: SQLITE_DONE" << std::endl;
#endif
			is_continue = false;
			break;
		case SQLITE_ERROR:
#ifdef ENABLE_LOG
			log << "sqlite3_step return: SQLITE_ERROR" << std::endl;
#endif
			throw exception(db_handle);
			break;
		case SQLITE_MISUSE:
#ifdef ENABLE_LOG
			log << "sqlite3_step return: SQLITE_MISUSE" << std::endl;
#endif
			throw std::logic_error("Misuse sqlite3_step");
			break;
		case SQLITE_ROW:
#ifdef ENABLE_LOG
			log << "sqlite3_step return: SQLITE_ROW" << std::endl;
#endif
			this->getSQLResult(pStmt, col_size, retval);
			break;
		default:
			throw std::logic_error("Unknown return code of sqlite3_step");
			break;
		}
	}
#ifdef ENABLE_LOG
	log << "finalizing..." << std::endl;
#endif
	Db::check(sqlite3_finalize(pStmt));
}

void Db::getSQLResult(sqlite3_stmt* pStmt, int col_size, Rows& retval) {
#ifdef ENABLE_LOG
	log << "Retrieving |";
#endif //ENABLE_LOG
	Rows::size_type i;
	retval.resize(i + 1);
	Row& row(retval[i]);
	row.resize(col_size);
	for (int col(0);col < col_size;col++) {
		row[col].data_type = Db::int2datatype(sqlite3_column_type(pStmt, col));
		Data& data(row[col].data);
		const unsigned char* src_text;
		const void* src_blob;
		int src_size;
		switch (row[col].data_type) {
		case Integer:
			data._integer = sqlite3_column_int64(pStmt, col);
#ifdef ENABLE_LOG
			log << " " << data._integer;
#endif //ENABLE_LOG
			break;
		case Float:
			data._float = sqlite3_column_double(pStmt, col);
#ifdef ENABLE_LOG
			log << " " << data._float;
#endif //ENABLE_LOG
			break;
		case Text:
			src_text = sqlite3_column_text(pStmt, col);
			if (!src_text) {
				throw exception(db_handle);
			}
			src_size = sqlite3_column_bytes(pStmt, col);
			data._buff.assign(reinterpret_cast<const char*>(src_text), src_size);
#ifdef ENABLE_LOG
			log << " " << data._buff;
#endif //ENABLE_LOG
			break;
		case Blob:
			src_blob = sqlite3_column_blob(pStmt, col);
			if (!src_blob) {
				throw exception(db_handle);
			}
			src_size = sqlite3_column_bytes(pStmt, col);
			data._buff.assign(reinterpret_cast<const char*>(src_blob), src_size);
#ifdef ENABLE_LOG
			log << " " << Encoding::hex_encode(data._buff);
#endif //ENABLE_LOG
			break;
		case Null:
			break;
		default:
			throw std::logic_error("Unknown DataType");
		}
#ifdef ENABLE_LOG
		log << " (" << Db::getTypeName(row[col].data_type) << ") |";
#endif //ENABLE_LOG
	}
#ifdef ENABLE_LOG
	log << std::endl;
#endif //ENABLE_LOG
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
	}
}

const Db::DataType Db::int2datatype(const int src) {

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

} /* namespace SQLite3 */
