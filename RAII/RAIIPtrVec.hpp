/*
 * RAIIPtrVec.hpp
 *
 *  Created on: Apr 27, 2012
 *      Author: wush
 */

#ifndef RAIIPTRVEC_HPP_
#define RAIIPTRVEC_HPP_

#include <stdexcept>
#include <vector>

namespace PROJECT_NAMESPACE {

template<class _T>
class RAIIPtrVec
{
	std::vector< _T* > vec;
public:
	RAIIPtrVec() : vec() { }
	~RAIIPtrVec() {
		for (size_t i = 0;i < vec.size();i++)
		{
			delete vec[i];
		}
	}

	_T* operator[](size_t i) {
		if (i < vec.size()) {
			return vec[i];
		}
		throw std::runtime_error("Index out of bound");
	}

	void push_back(_T* ptr) {
		vec.push_back(ptr);
	}

	size_t size() const {
		return vec.size();
	}
};

}

#endif /* RAIIPTRVEC_HPP_ */
