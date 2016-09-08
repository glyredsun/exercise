#include <cstdio>
#include <cstdlib>

#include <new.h>

#define SHOW_FUNC	printf("%s\n", __FUNCTION__);
#define SHOW_LINE	printf("line %d\n", __LINE__);

class MyClass 
{
public:
	MyClass() 
	{
		SHOW_FUNC;
	}

	~MyClass()
	{
		SHOW_FUNC;
	}

	void* operator new(size_t size)
	{
		SHOW_FUNC;
		return ::operator new(size);
	}

	void func()
	{
		SHOW_FUNC;
		printf("n is %d\n", n);
	}

private:
	int n{0};
};

int main(void)
{
	SHOW_LINE;
	MyClass *p1 = ::new MyClass;
	p1->func();
	delete p1;
	SHOW_LINE;

	void *p2 = malloc(sizeof(MyClass));
	printf("before placement new\n");
	static_cast<MyClass*>(p2)->func();
	::new(p2) MyClass;
	printf("after placement new\n");
	static_cast<MyClass*>(p2)->func();
	static_cast<MyClass*>(p2)->~MyClass();
	free(p2);

	system("pause");
	return 0;
}