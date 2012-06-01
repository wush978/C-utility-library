/*
 * Table.cpp
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#include <boost/regex.hpp>
#include "sqlite3_wrapper.h"

namespace SQLite3 {

static const boost::regex check_column_name("^(\\w{1})[[:alnum:]]*$");

Table::Table(const std::string& table_name)
: temporary(false), name(table_name), pk_index(0), is_auto_pk(true), is_mutable(true) {
}

Table::Table(const std::string& table_name, const bool is_temporary)
: temporary(is_temporary), name(table_name), pk_index(0), is_auto_pk(true), is_mutable(true) {
}

Table::~Table() {
	for(size_t i(0);i < rows.size();i++) {
		delete rows[i];
	}
}

void Table::assertMutable() const {
	if (!is_mutable) {
		throw std::logic_error("The table is locked");
	}
}

void Table::assertNonMutable() const {
	if (is_mutable) {
		throw std::logic_error("The table is not locked");
	}
}

Table& operator<<(Table& dst, const DataType data_type) {
	dst.assertMutable();
	dst.column_type.push_back(data_type);
	return dst;
}

Table& operator<<(Table& dst, const std::string& name) {
	dst.assertMutable();
	if (!boost::regex_match(name, check_column_name)) {
		throw std::invalid_argument("Invalid column name");
	}
	dst.column_name.push_back(name);
	return dst;
}

bool Table::check() const {
	if (column_name.size() != column_type.size()) {
		return false;
	}
	if (pk_index > column_name.size()) {
		return false;
	}
	return true;
}


} /* namespace SQLite3 */
