
#include <iostream>
#include "../sqlite3_wrapper/exception.h"
#include "../sqlite3_wrapper/Db.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: sqlite3-console <filename>" << std::endl;
		return 1;
	}
	try {
		using namespace SQLite3;
		Db db(argv[1]);
		Table table("test_table");
		table << "id" << "test2" << "test3";
		table << SQLITE_INTEGER << SQLITE_TEXT << SQLITE_BLOB;
		db.createTable(table);
	}
	catch (SQLite3::exception &e) {
		std::cout << "An exception occurred:" << std::endl;
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (std::exception &e) {
		std::cout << "Unknown Error" << std::endl;
		return 1;
	}
	return 0;
}
