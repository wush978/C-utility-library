
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

	}
	catch (SQLite3::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (std::exception &e) {
		std::cout << "Unknown Error" << std::endl;
		return 1;
	}
	return 0;
}
