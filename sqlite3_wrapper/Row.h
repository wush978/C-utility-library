/*
 * Row.h
 *
 *  Created on: 2012/5/31
 *      Author: wush
 */

#ifndef ROW_H_
#define ROW_H_

#include <cstring>
#include <vector>
#include "Table.h"
#include "sqlite3_wrapper.h"

namespace SQLite3 {

class Table;

class Row {
	const Table& table;
	const std::vector<DataType>& data_type;
	std::vector<size_t> hash;
	std::vector<sqlite3_int64> data_int;
	std::vector<double> data_float;
	std::vector<std::string> data_string;
	size_t assign_index;
public:
	virtual ~Row();


private:
	friend class Table;
	Row(const Table& src);

	Row(const Row&);
	const Row& operator=(const Row& src);



friend Row& operator<<(Row& dst, const std::string& src);
friend Row& operator<<(Row& dst, const sqlite3_int64 src);
friend Row& operator<<(Row& dst, const double src);
};

typedef std::vector<Row> Rows;

} /* namespace SQLite3 */
#endif /* ROW_H_ */
