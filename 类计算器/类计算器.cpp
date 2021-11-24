#include<iostream>
#include<string>
using namespace std;

class abstractcalculator
{
public:



	virtual float getresult()
	{
		return 0;
	}
	float num1 = 0, num2 = 0;

};

class addcalculator :public abstractcalculator//加法
{
public:
	float getresult()
	{
		return num1 + num2;
	}
};

class subcalculator :public abstractcalculator//减法
{
public:
	float getresult()
	{
		return num1 - num2;
	}
};

class muticalculator :public abstractcalculator
{
public:
	float getresult()
	{
		return num1 * num2;
	}

};


class devicalculator :public abstractcalculator
{
public:
	float getresult()
	{
		return num1 / num2;
	}

};


int main()
{
	cout << "请输入算式,，每输入一个请空格一下" << endl;
	float num;

	while (cin >> num)
	{

		string ch;
		cin >> ch;
		if (ch == "+")
		{
			abstractcalculator* abs = new addcalculator;
			abs->num1 = num;
			cin >> abs->num2;
			cout << "结果为" << abs->getresult() << endl;
			delete abs;

		}
		else if (ch == "-")
		{
			abstractcalculator* abs = new subcalculator;
			abs->num1 = num;
			cin >> abs->num2;
			cout << "结果为" << abs->getresult() << endl;
			delete abs;

		}
		else if (ch == "*")
		{
			abstractcalculator* abs = new muticalculator;
			abs->num1 = num;
			cin >> abs->num2;
			cout << "结果为" << abs->getresult() << endl;
			delete abs;

		}
		else if (ch == "/")
		{
			abstractcalculator* abs = new devicalculator;
			abs->num1 = num;
			cin >> abs->num2;
			cout << "结果为" << abs->getresult() << endl;
			delete abs;

		}
	}

	return 0;
}