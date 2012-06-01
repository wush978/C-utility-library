/*
 * Row.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include "sqlite3_wrapper.h"

namespace SQLite3 {

Row::Row(const Table& src)
: table(src), data_type(src.getColumnType()), assign_index(0) {
	DataType type;
	for (size_t i(0);i < data_type.size();i++) {
		type = data_type[i];
		switch(type) {
		case Integer:
			data_int.push_back(0);
			hash.push_back(data_int.size() - 1);
			break;
		case Float:
			data_float.push_back(0);
			hash.push_back(data_float.size() - 1);
			break;
		case Null:
			hash.push_back(0);
			break;
		default:
			data_string.push_back("");
			hash.push_back(data_string.size() - 1);
			break;
		}
	}
}

Row::~Row() {
}

Row& operator<<(Row& dst, const std::string& src) {
	DataType type(dst.data_type[dst.assign_index]);
	if (type == Null && !src.compare("")) {
		dst.assign_index++;
		return dst;
	}
	if (type != Text && type != Blob) {
		throw std::invalid_argument("Assign an invalid type to a Row");
	}
	size_t index(dst.hash[dst.assign_index++]);
	dst.data_string[index].assign(src);
	return dst;
}

Row& operator<<(Row& dst, const sqlite3_int64 src) {
	DataType type(dst.data_type[dst.assign_index]);
	if (type == Null && !src) {
		dst.assign_index++;
		return dst;
	}
	size_t index(dst.hash[dst.assign_index++]);
	dst.data_int[index] = src;
	return dst;
}

Row& operator<<(Row& dst, const double src) {
	DataType type(dst.data_type[dst.assign_index]);
	if (type == Null && !src) {
		dst.assign_index++;
		return dst;
	}
	size_t index(dst.hash[dst.assign_index++]);
	dst.data_float[index] = src;
	return dst;
}


} /* namespace SQLite3 */
