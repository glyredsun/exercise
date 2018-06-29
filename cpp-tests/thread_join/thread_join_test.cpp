#include <thread>
#include <chrono>

static void thread_entry()
{
	printf("in function %s\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(void) {

	std::thread t1(thread_entry);
	std::this_thread::sleep_for(std::chrono::seconds(5));
    assert(t1.joinable());
    t1.join();
	return 0;
}
