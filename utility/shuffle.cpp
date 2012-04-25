/*
 * shuffle.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: wush
 */

#include "shuffle.h"

namespace PROJECT_NAMESPACE {

void shuffle(void* begin, size_t length, size_t size = 1)
{
    size_t switch_index;
    void* temp = malloc(size);
    while( --length )
    {
    	switch_index = rand() % (length + 1);
    	if (length == switch_index)
    		continue;
//    	temp = temp_keyboard[switch_index];
    	memcpy(temp, begin + switch_index * size, size);
//    	temp_keyboard[switch_index] = temp_keyboard[n_left];
    	memcpy( begin + switch_index * size, begin + length * size, size );
//    	temp_keyboard[n_left] = temp;
    	memcpy( begin + length * size, temp, size );
    }
    free(temp);
}

}

