#include <thread>
#include <chrono>

static void thread_entry()
{
	printf("in function %s\n", __FUNCTION__);
	std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
}

class ClassA
{
public:
	void operator()()
	{
		printf("in function %s\n", __FUNCTION__);
		std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
	}
};

class ClassB
{
public:
	ClassB(int id) : id(id) {}
	void func()
	{
		printf("in function %s, id %d\n", __FUNCTION__, id);
		std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
	}
private:
	int id;
};

int main(void) {

	std::thread t1(thread_entry);
	std::thread t2(ClassA{});
	std::thread t3([]{
		printf("in function %s\n", __FUNCTION__);
		std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
	});
	ClassB b(1);
	std::thread t4(&ClassB::func, &b);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	system("pause");

	return 0;
}