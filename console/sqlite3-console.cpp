
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
		std::vector<Db::ColumnDef> column_def;
		column_def.resize(3);
		column_def[0].column_label.assign("test0");
		column_def[0].column_type = Db::Integer;
		column_def[1].column_label.assign("test1");
		column_def[1].column_type = Db::Text;
		column_def[2].column_label.assign("test2");
		column_def[2].column_type = Db::Blob;
		db.createTable("test_table", column_def, false);
	}
	catch (SQLite3::exception &e) {
		std::cout << "An exception occurred:" << std::endl;
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (std::exception &e) {
		std::cout << "Unknown Error" << std::endl;
		return 1;
	}
	return 0;
}
