#include <stack>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <tuple>
#include <cmath>
#include <sstream>

using namespace std;

//定义栈数据结构体
struct stackData {
    char Operator;
    double Number;
};

inline bool isOperator(char ch) {
    return ch == '+'
        or ch == '-'
        or ch == '*'
        or ch == '/'
        or ch == '^'
        /*or ch == '!'*/;
}


inline bool isNumber(char ch) {
    return '0' <= ch and ch <= '9' or ch == '.';
}


//优先级判定
inline int priority(char operatorChar) {
    int level = 0;  // level越大，优先级越高
    if (operatorChar == '^'/* or operatorChar == '!'*/) {
        level = 2;
    }
    else if (operatorChar == '*' or operatorChar == '/') {
        level = 1;
    }
    else if (operatorChar == '+' or operatorChar == '-') {
        level = 0;
    }
    return level;
}

//获取数字栈顶双数
template<typename T>
tuple<T, T> getTwoNums(stack<T>& nums) {
    auto second = nums.top();
    nums.pop();
    auto first = nums.top();
    nums.pop();
    return { first, second };
}   // return {first, second}
//template<typename T>
//tuple<T> getOneNums(stack<T>& nums) {
//    auto first = nums.top();
//    nums.pop();
//    return { first };
//}

//计算后缀表达式
double postfixCalculate(vector<stackData>& postfix) {
    double first, second;
    stack<double> nums;
    for (const auto& p : postfix) {
        switch (p.Operator) {
        case '*':
            tie(first, second) = getTwoNums(nums);
            nums.push(first * second);
            break;
        case '/':
            tie(first, second) = getTwoNums(nums);
            nums.push(first / second);
            break;
        case '+':
            tie(first, second) = getTwoNums(nums);
            nums.push(first + second);
            break;
        case '-':
            tie(first, second) = getTwoNums(nums);
            nums.push(first - second);
            break;
        case '^':
            tie(first, second) = getTwoNums(nums);
            nums.push(pow(first, second));
            break;
            //case '!':
            //    tie(first) = getOneNums(nums);
            //    for (int i = 1; i < first; i++)
            //        first = i * first;
            //    nums.push(first);
            //    break;
        default:
            nums.push(p.Number);
            break;
        }
    }
    double result = nums.top();
    nums.pop();
    return result;
}

//做分割
vector<stackData> getSeparate(string& infix) {
    vector<stackData> postfix;
    string numStr;  // 单个连续字符的数字
    for (const auto& p : infix) {
        if (isNumber(p)) {
            numStr += p;
        }
        else if (isOperator(p) or p == '(' or p == ')') {
            if (not numStr.empty()) {
                postfix.emplace_back(stackData{ ' ', stod(numStr) });
            }
            numStr = "";
            postfix.emplace_back(stackData{ p, 0 });
        }
    }
    if (not numStr.empty()) {
        postfix.emplace_back(stackData{ ' ', stod(numStr) });
    }

    //前导缺损+-符号补0
    vector<stackData> newPostfix;
    char preChar = '(';
    for (const auto& p : postfix) {
        if (p.Operator != ' ') {
            if (preChar == '(' and (p.Operator == '-' or p.Operator == '+'))
                newPostfix.emplace_back(stackData{ ' ', 0 });
            preChar = p.Operator;
        }
        else {
            preChar = ' ';
        }
        newPostfix.emplace_back(p);
    }
    return newPostfix;
}

//表达式输出
string printExpression(vector<stackData>& temp) {
    stringstream ss;
    for (const auto& t : temp) {
        if (t.Operator != ' ') {
            ss << t.Operator;
        }
        else {
            ss << t.Number;
        }
        ss << ' ';
    }
    return ss.str();
}

//后缀表达式转换
vector<stackData> getPostfixExp(vector<stackData>& infix) {
    stack<char> operator_stack;
    vector<stackData> postfix;
    for (const auto& p : infix) {
        if (isOperator(p.Operator)) {
            while (not operator_stack.empty()
                and isOperator(operator_stack.top())
                and priority(operator_stack.top()) >= priority(p.Operator)) {
                postfix.emplace_back(stackData{ operator_stack.top(), 0 });
                operator_stack.pop();
            }
            operator_stack.push(p.Operator);
        }
        else if (p.Operator == '(') {
            operator_stack.push(p.Operator);
        }
        else if (p.Operator == ')') {
            while (operator_stack.top() != '(') {
                postfix.push_back(stackData{ operator_stack.top() });
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else {
            postfix.push_back(p);
        }

    }
    while (not operator_stack.empty()) {
        postfix.push_back(stackData{ operator_stack.top(), 0 });
        operator_stack.pop();
    }
    return postfix;
}


int main() {
    cout << "please input string expression: " << endl
        << "example: " << "( 15 / 3 - 1)^2 -(8 + (0.7 - 0.2)*5.41 + 6.8)+1^0.5" << endl;
    string infix;
    // 读取非空行
    while (getline(cin, infix)) {
        infix.erase(infix.find_last_not_of(" \n\r\t") + 1);
        if (not infix.empty()) {
            break;
        }
    }

    vector<stackData> expression = getSeparate(infix);
    cout << "Standard expression: " << printExpression(expression) << endl;
    vector<stackData> postfixExp = getPostfixExp(expression);
    cout << "Postfix expression: " << printExpression(postfixExp) << endl;
    double result = postfixCalculate(postfixExp);
    cout << "Answer: " << setprecision(10) << result;
    return 0;
}