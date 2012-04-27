/*
 * RAIIPtr.hpp
 *
 *  Created on: Apr 27, 2012
 *      Author: wush
 */

#ifndef RAIIPTR_HPP_
#define RAIIPTR_HPP_

namespace PROJECT_NAMESPACE {

#ifndef NULL
#define NULL 0
#endif

template<class _T>
class RAIIPtr
{
	_T* ptr;
public:
	RAIIPtr() : ptr(NULL) { }
	RAIIPtr(_T* src) : ptr(src) { }
	~RAIIPtr() {
		if (ptr) {
			delete ptr;
		}
	}

	_T* getPtr() { return ptr; }
};

}


#endif /* RAIIPTR_HPP_ */
