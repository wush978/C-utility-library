/*
 * hex.h
 *
 * Modify php src
 *
 *  Created on: May 9, 2012
 *      Author: wush
 */

#ifndef HEX_H_
#define HEX_H_

#include <stdexcept>
#include <string>
#include "C-utility-library.config.h"

namespace PROJECT_NAMESPACE {

const std::string
hex_decode(const std::string& src);

/**
 * @param src input
 * @return base64 decoded output
 * @throws std::invalid_argument
 */
const std::string
hex_encode(const std::string& src);

}

#endif /* HEX_H_ */
