#include <functional>
#include <iostream>

int main()
{
	using FunType1 = std::function<void (int n)>;
	using FunType2 = std::function<int(int n)>;

	int num = 10;

	FunType1 f1 = [=](int n) {
		std::cout << "num + n = " << num + n << std::endl;
	};

	f1(2);

	FunType2 f2 = [&](int n) {
		num = 1;
		return num - n;
	};
	int result = f2(100);
	std::cout << "result = " << result << ", num = " << num << std::endl;

	FunType1 f3 = std::bind([=](int n, int m) {
			std::cout << "n + m + num = " << n + m + num << std::endl;
		}, std::placeholders::_1, 2);
	f3(11);
	getchar();
	return 0;
}