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
	struct VTInfo {
		void ** ptr;
		int size;
	} vtInfos[] = { { vtable1, 5 }, { vtable2 , 5 }, { vtable3, 6 } };
	for each (VTInfo info in vtInfos)
	{
		cout << "vtable " << info.ptr << " = {";
		for (int i = 0; i < info.size; i++)
		{
			if (i != 0) cout << ", ";
			cout << info.ptr[i];
		}
		cout << "}" << endl;
	}
	
	return EXIT_SUCCESS;
}