/*
 * base64.h
 *
 *  Created on: Apr 25, 2012
 *      Author: wush
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <string>
#include "C-utility-library.config.h"

namespace PROJECT_NAMESPACE {

const std::string
base64_decode(const std::string& src);
const std::string
base64_encode(const std::string& src);

}

#endif /* BASE64_H_ */
