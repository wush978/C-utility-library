
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include "../random_related/shuffle.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (argc != 2) {
		cerr << "Usage: shuffle-console.exe <string to shuffle>" << endl;
		return 1;
	}
	std::string src(argv[1]);
	Random::shuffle(&src[0], src.size());
	cout << src << endl;
	return 0;
}
