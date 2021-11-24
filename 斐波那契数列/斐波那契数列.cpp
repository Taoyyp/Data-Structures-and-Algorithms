#include <iostream>
#include <vector>

using namespace std;

int fib1(int n) {
	if (n < 2)
		return n;
	return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {

	vector<int> res(n);
	int a = 0;
	int b = 1;
	while (0 < n--)
	{
		a = a + b;
		b = a - b;
	}
	return a;
}

int main() {
	int n, res = 0;
	cin >> n;
	res = fib2(n);
	cout << res;
	return 0;


}