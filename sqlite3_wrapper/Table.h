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
#include "sqlite3_wrapper.h"

namespace SQLite3 {

class Table {
	bool temporary;
	std::string name;
	size_t pk_index;
	std::vector<std::string> column_name;
	std::vector<DataType> column_type;
public:
	Table(const std::string& table_name);
	Table(const std::string& table_name, const bool is_temporary);
	virtual ~Table();

	// function for user
	void setPK(const size_t src) { pk_index = src; }
	/**
	 * Check if Table definition is valid or not
	 */
	bool check() const;

	// function to create SQL
	const bool isTemporary() const { return temporary; };
	const std::vector<std::string>& getColumnName() const { return column_name; }
	const std::vector<DataType>& getColumnType() const { return column_type; }
	const size_t getPK() const { return pk_index; }

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
