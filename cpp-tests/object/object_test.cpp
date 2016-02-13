#include <string>
#include <vector>
#include <iostream>
#include <memory>

#define SHOW_CODE_POSITION	printf("in function %s, line %d\n", __FUNCTION__, __LINE__)

class A
{
	friend std::ostream & operator<<(std::ostream& out, const A& a);
public:
	A()
		: A(0, "abc")
	{
		SHOW_CODE_POSITION;
		std::cout << *this;
	}
	A(int num, std::string str)
		: num(num)
		, str(str)
	{
		SHOW_CODE_POSITION;
		std::cout << *this;
	}
	virtual ~A()
	{
		SHOW_CODE_POSITION;
		std::cout << *this;
	}

public:
	int getNum() const { return num; }
	std::string& getStr() { return str; }
	const std::string& getStr() const { return str; }
protected:
	int num;
	std::string str;
};
std::ostream & operator<<(std::ostream& out, const A& a)
{
	return out << "num " << a.num << ", str " << a.str << std::endl;
}

class DerivedA : public A
{
public:
	DerivedA()
	{
		SHOW_CODE_POSITION;
	}

	DerivedA(const A& a)
		: A(a.getNum(), a.getStr())
	{
		SHOW_CODE_POSITION;
	}

	~DerivedA()
	{
		SHOW_CODE_POSITION;
	}

	DerivedA & operator=(const A& a)
	{
		if (this != &a)
		{
			this->num = a.getNum();
			this->str = a.getStr();
		}
		return *this;
	}

};

class B
{
public:
	B() 
	{
		SHOW_CODE_POSITION;
	}
	~B()
	{
		SHOW_CODE_POSITION;
	}
};

class C
{
public:
	C()
	{
		SHOW_CODE_POSITION;
	}

	~C()
	{
		SHOW_CODE_POSITION;
	}
};

int main(void)
{
	{
		A a;
		B b;
	}
	
	{
		std::vector<A> v{ { 1, "abc" }, { 2, "def" }, { 3, "ghi" }, { 4, "jkl" } };
		std::cout << "begin loop1" << std::endl;
		for each (A a in v)
		{

		}
		std::cout << "end loop1" << std::endl;
		std::cout << "begin loop2" << std::endl;
		for each (const A& a in v)
		{

		}
		std::cout << "end loop2" << std::endl;
		std::cout << "begin loop3" << std::endl;
		for each (const A& a in v)
		{
			DerivedA da = a;
		}
		std::cout << "end loop3" << std::endl;

	}
	
	{
		std::unique_ptr<C> ptrC(new C);
	}

	system("pause");
	return 0;
}