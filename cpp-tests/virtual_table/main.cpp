#include <iostream>
#include <cstdlib>
#define SHOW_FUNC {cout << __FUNCTION__;}
using namespace std;
class C1
{
public:
	virtual ~C1() {}
	virtual void func1() {}
	virtual void func2() {}
	virtual void func3() {}
	virtual void func4() {}
};

class C2 : public C1
{
public:
	virtual void func2() {}
};

class C3 : public C2
{
public:
	virtual void func3() {}
	virtual void func5() {}
};


int main(void)
{
	C1 c1;
	C2 c2;
	C3 c3;
	void ** vtable1 = *((void ***)&c1);
	void ** vtable2 = *((void ***)&c2);
	void ** vtable3 = *((void ***)&c3);
	void ** vtables[] = {vtable1, vtable2, vtable3};
	for each (void** vtable in vtables)
	{
		cout << "vtable " << vtable << " = {";
		for (int i = 0; ; i++)
		{
			if (vtable[i] == nullptr) break;
			if (i != 0) cout << ", ";
			cout << vtable[i];
		}
		cout << "}" << endl;
	}
	
	return EXIT_SUCCESS;
}