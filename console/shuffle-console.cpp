
#include <string>
#include <iostream>
#include <cstdio>
#include "../random_related/shuffle.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: shuffle-console.exe <string to shuffle>" << endl;
		return 1;
	}
	std::string src(argv[1]);
	PROJECT_NAMESPACE::shuffle(&src[0], src.size());
	cout << src << endl;
	return 0;
}
