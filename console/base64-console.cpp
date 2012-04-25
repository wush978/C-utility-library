/*
 * base64-test.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: wush
 */
#include <string>
#include <iostream>
#include <cstdio>
#include "../encoding/base64.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "Usage: base64-console.exe encode|decode <encoded file path>" << endl;
		return 0;
	}

	const int argv_option(1), argv_path(2);

	FILE* infile = fopen(argv[argv_path], "rb");
	if (!infile) {
		cerr << "Invalid file path!" << endl;
		return 1;
	}

	std::string src, option(argv[argv_option]);
	unsigned char temp;
	int c = fgetc(infile);
	while( c != EOF )
	{
		temp = (unsigned char) c;
		src.push_back((char) temp);
		c = fgetc(infile);
	}
	fclose(infile);

	if (!option.compare("encode")) {
		string retval(PROJECT_NAMESPACE::base64_encode(src));
		cout << retval << endl;
	}
	else {
		if (!option.compare("decode")) {
			try {
				cout << PROJECT_NAMESPACE::base64_decode(src) << endl;
			}
			catch (std::invalid_argument &e) {
				cerr << e.what() << endl;
				return 1;
			}
		}
		else {
			cerr << "Second arguments should be \"encode\" or \"decode\"" << endl;
			return 1;
		}
	}
	return 0;
}


