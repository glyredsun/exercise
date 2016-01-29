#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
#include "Fraction.h"
int main(void)
{
	Fraction f(1, 5);
	cout << static_cast<double>(f) << endl;
	cout << f << endl;
	Fraction f2(3, 4);
	assert(f != f2);
	getchar();
	return EXIT_SUCCESS;
}