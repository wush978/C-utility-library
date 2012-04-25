/*
 * shuffle.h
 *
 *  Created on: Apr 25, 2012
 *      Author: wush
 */

#ifndef SHUFFLE_H_
#define SHUFFLE_H_
#ifdef __cplusplus


#include <cstring>
#include <cstdlib>

#ifndef PROJECT_NAMESPACE
#define PROJECT_NAMESPACE wush_utility
#endif // PROJECT_NAMESPACE

namespace PROJECT_NAMESPACE {

void shuffle(void* begin, size_t length, size_t size = 1);

}

#endif /* __cplusplus */
#endif /* SHUFFLE_H_ */
