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
#include "sqlite3_wrapper.h"

namespace SQLite3 {


typedef struct {
	DataType data_type;
	void* data;
} Entry;

class Row {
	std::vector<Entry> _row;
public:
	Row();
	virtual ~Row();
	void push_back(const void* data, const int data_size, const DataType data_type);
};

typedef std::vector<Row> Rows;

} /* namespace SQLite3 */
#endif /* ROW_H_ */
