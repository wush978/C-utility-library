/*
 * base64.h
 *
 *  Created on: Apr 25, 2012
 *      Author: wush
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <stdexcept>
#include <string>
#include "C-utility-library.config.h"

namespace PROJECT_NAMESPACE {

const std::string
base64_decode(const std::string& src);

/**
 * @param src input
 * @return base64 decoded output
 * @throws std::invalid_argument
 */
const std::string
base64_encode(const std::string& src);

}

#endif /* BASE64_H_ */
