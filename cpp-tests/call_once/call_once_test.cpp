#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

std::once_flag flag;

void initializeSharedResources(int id)
{
	std::cout << "initializeSharedResources" << ", id " << id << std::endl;
}

void processingFunction(int id)
{
	std::call_once(flag, initializeSharedResources, id);
	std::cout << "Processing, id " << id << std::endl;
}

int main(void)
{
	int id = 0;
	std::vector<std::thread> threads(3);

	for (auto &t : threads)
	{
		t = std::thread{processingFunction, ++id};
	}
	processingFunction(0);
	for (auto &t : threads)
	{
		t.join();
	}
	
	system("pause");
	return 0;
}