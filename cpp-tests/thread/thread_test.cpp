#include <thread>
#include <chrono>

static void thread_entry()
{
	printf("in function %s\n", __FUNCTION__);
	std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
}

class MyClass
{
public:
	void operator()()
	{
		printf("in function %s\n", __FUNCTION__);
		std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
	}
};

int main(void) {

	std::thread t1(thread_entry);
	std::thread t2(MyClass{});
	std::thread t3([]{
		printf("in function %s\n", __FUNCTION__);
		std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
	});
	
	t1.join();
	t2.join();
	t3.join();
	return 0;
}