#include <memory>
#include <iostream>
#include <string>

class A
{
public:
	A(const char *name) : name_(name) {
		std::cout << __FUNCTION__ << " " << name_ << std::endl;
	}

	virtual ~A() {
		std::cout << __FUNCTION__ << " " << name_ << std::endl;
	}
protected:
	std::string name_;
};

class B : public A
{
public:
	B(const char *name) : A(name)
	{
		std::cout << __FUNCTION__ << " " << name_ << std::endl;
	}
};

int main(void)
{
	{
		std::cout << "weak ptr test begin" << std::endl;
		std::unique_ptr<A> up;

		std::cout << "before first reset" << std::endl;
		up.reset(new A("first"));
		std::cout << "before second reset" << std::endl;
		up.reset(new A("second"));
		std::cout << "before third reset" << std::endl;
		up.reset(new B("third"));

		std::unique_ptr<A> up1 = std::move(up);
		std::cout << "weak ptr test end" << std::endl;
	}

	{
		std::cout << "shared ptr test begin" << std::endl;
		std::shared_ptr<A> sp;

		sp.reset(new A("first"));

		std::shared_ptr<A> sp1 = sp;
		{
			std::shared_ptr<A> sp2 = sp1;
		}

		std::cout << "shared ptr test end" << std::endl;
	}

	std::cout << "main is going to return" << std::endl;
	return 0;
}