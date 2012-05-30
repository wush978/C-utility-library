/*
 * exception.cpp
 *
 *  Created on: 2012/5/30
 *      Author: wush
 */

#include "exception.h"

namespace SQLite3 {

exception::exception(sqlite3* db) {
	message = sqlite3_errmsg(db);
}

exception::exception(const char* msg) : message(msg) { }

exception::exception(const int error_code) {
	switch(error_code) {
		case SQLITE_ERROR:
			message = "SQL error or missing database";
			break;
		case SQLITE_INTERNAL:
			message = "Internal logic error in SQLite";
			break;
		case SQLITE_PERM:
			message = "Access permission denied";
			break;
		case SQLITE_ABORT:
			message = "Callback routine requested an abort";
			break;
		case SQLITE_BUSY:
			message = "The database file is locked";
			break;
		case SQLITE_LOCKED:
			message = "A table in the database is locked";
			break;
		case SQLITE_NOMEM:
			message = "A malloc() failed";
			break;
		case SQLITE_READONLY:
			message = "Attempt to write a readonly database";
			break;
		case SQLITE_INTERRUPT:
			message = "Operation terminated by sqlite3_interrupt(";
			break;
		case SQLITE_IOERR:
			message = "Some kind of disk I/O error occurred";
			break;
		case SQLITE_CORRUPT:
			message = "The database disk image is malformed";
			break;
		case SQLITE_NOTFOUND:
			message = "Unknown opcode in sqlite3_file_control()";
			break;
		case SQLITE_FULL:
			message = "Insertion failed because database is full";
			break;
		case SQLITE_CANTOPEN:
			message = "Unable to open the database file";
			break;
		case SQLITE_PROTOCOL:
			message = "Database lock protocol error";
			break;
		case SQLITE_EMPTY:
			message = "Database is empty";
			break;
		case SQLITE_SCHEMA:
			message = "The database schema changed";
			break;
		case SQLITE_TOOBIG:
			message = "String or BLOB exceeds size limit";
			break;
		case SQLITE_CONSTRAINT:
			message = "Abort due to constraint violation";
			break;
		case SQLITE_MISMATCH:
			message = "Data type mismatch";
			break;
		case SQLITE_MISUSE:
			message = "Library used incorrectly";
			break;
		case SQLITE_NOLFS:
			message = "Uses OS features not supported on host";
			break;
		case SQLITE_AUTH:
			message = "Authorization denied";
			break;
		case SQLITE_FORMAT:
			message = "Auxiliary database format error";
			break;
		case SQLITE_RANGE:
			message = "2nd parameter to sqlite3_bind out of range";
			break;
		case SQLITE_NOTADB:
			message = "File opened that is not a database file";
			break;
		case SQLITE_ROW:
			message = "sqlite3_step() has another row ready";
			break;
	}
}

exception::~exception() throw() {
}

const char* exception::what() throw() {
	return message;
}

} /* namespace SQLite3 */
