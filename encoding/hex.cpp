/*
 * hex.cpp
 *
 *  Created on: May 9, 2012
 *      Author: wush
 */

#include "hex.h"

namespace Encoding {

const static char bin2hextab[] = "0123456789abcdef";
const static int hex2bintab[] = {
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,
		-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};
const std::string
hex_decode(const std::string& src) {
	if (src.size() % 2) {
		throw std::invalid_argument("hex_decode: the input is not a valid hex code");
	}
	std::string retval;
	retval.resize(src.size()/2);
	unsigned char *pretval( reinterpret_cast<unsigned char*>(&retval[0]) );
	const unsigned char *psrc( reinterpret_cast<const unsigned char*>(&src[0]) );
	int first, second;
	for (size_t i = 0; i < src.size()/2; i++) {
		first = hex2bintab[*psrc++];
		if (first == -1) {
			throw std::invalid_argument("hex_decode: the input is not a valid hex code");
		}
		second = hex2bintab[*psrc++];
		if (second == -1) {
			throw std::invalid_argument("hex_decode: the input is not a valid hex code");
		}
		first = first << 4;
		*pretval++ = first + second;
	}
	return retval;
}

const std::string
hex_encode(const std::string& src) {
	std::string retval(0, src.size() * 2);
	for (size_t i(0), j(0); i < src.size();i++) {
		retval[j++] = bin2hextab[src[i] >> 4];
		retval[j++] = bin2hextab[src[i] & 15];
	}
	return retval;
}


}

