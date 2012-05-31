/*
 * Row.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include "sqlite3_wrapper.h"

namespace SQLite3 {

Row::Row() {
}

Row::~Row() {
	for (std::vector<Entry>::iterator entry(_row.begin()); entry != _row.end();entry++) {
		free(entry->data);
	}
}

void Row::push_back(const void* data, const int data_size, const DataType data_type) {
	_row.resize(_row.size() + 1);
	std::vector<Entry>::iterator entry(_row.end() - 1);
	entry->data_type = data_type;
	entry->data = malloc(data_size);
	memcpy(entry->data, data, data_size);
}

} /* namespace SQLite3 */
