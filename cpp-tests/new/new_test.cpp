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
		SHOW_FUNC
	}

	~MyClass()
	{
		SHOW_FUNC
	}

	void* operator new(size_t size)
	{
		SHOW_FUNC
		return ::operator new(size);
	}

	int n{0};
};

int main(void)
{
	SHOW_LINE;
	MyClass *p1 = ::new MyClass;
	printf("p1->n is %d\n", p1->n);
	delete p1;
	SHOW_LINE;

	void *p2 = malloc(sizeof(MyClass));
	printf("p2->n before placement new %d\n", static_cast<MyClass*>(p2)->n);
	::new(p2) MyClass;
	printf("p2->n after placement new %d\n", static_cast<MyClass*>(p2)->n);
	static_cast<MyClass*>(p2)->~MyClass();
	free(p2);

	system("pause");
	return 0;
}