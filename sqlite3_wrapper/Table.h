/*
 * Table.h
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <string>
#include <vector>
#include "Row.h"
#include "sqlite3_wrapper.h"

namespace SQLite3 {

class Row;

class Table {
	bool temporary;
	std::string name;
	size_t pk_index;
	bool is_auto_pk;
	std::vector<std::string> column_name;
	std::vector<DataType> column_type;
	std::vector<Row*> rows;
	bool is_mutable;
public:
	Table(const std::string& table_name);
	Table(const std::string& table_name, const bool is_temporary);
	virtual ~Table();

	// function for user
	void setPK(const size_t src) {
		is_auto_pk = false;
		pk_index = src;
	}
	/**
	 * Check if Table definition is valid or not
	 */
	bool check() const;
	void lock() { is_mutable = false; }
	void assertMutable() const;
	void assertNonMutable() const;

	// function to create SQL
	const bool isTemporary() const { return temporary; };
	const std::string& getName() const { return name; }
	const size_t getPK() const { return pk_index; }
	const bool isAutoPK() const { return is_auto_pk; }
	const std::vector<std::string>& getColumnName() const { return column_name; }
	const std::vector<DataType>& getColumnType() const { return column_type; }

private:
	Table(const Table&);
	const Table& operator=(const Table&);

	// function for user
	friend Table& operator<<(Table& dst, const DataType data_type);
	inline friend Table& operator<<(Table& dst, const int src) {
		return dst << getDataType(src);
	}
	friend Table& operator<<(Table& dst, const std::string& name);
};

} /* namespace SQLite3 */
#endif /* TABLE_H_ */
