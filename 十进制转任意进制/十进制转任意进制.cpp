#include <iostream>
#include <stack>
#include <string>
using namespace std;



string stard = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//void convert10below(int& num, int base) {
//	stack<int> ans;
//	int temp;
//	while (num > 0) {
//		temp = num % base;
//		ans.push(temp);
//		num /= base;
//	}
//	while (!ans.empty()) {
//		cout << ans.top();
//		ans.pop();
//	}
//}

void convert10high(int& num, int base) {
	stack<char>ans;
	int temp;
	while (num > 0) {
		temp = num % base;
		ans.push(stard[temp]);
		num /= base;
	}
	while (!ans.empty()) {
		cout << ans.top();
		ans.pop();
	}
}

int main() {
	int n;
	int q;
	cin >> n;
	cin >> q;
	//convert10below(n, q);
	convert10high(n, q);
}