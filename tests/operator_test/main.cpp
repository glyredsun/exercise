#include <iostream>
#include <cstdlib>
using namespace std;
#include "Fraction.h"
int main(void)
{
	Fraction f(1, 5);
	cout << static_cast<double>(f) << endl;
	cout << f << endl;
	return EXIT_SUCCESS;
}