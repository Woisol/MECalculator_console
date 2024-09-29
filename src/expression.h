#pragma once

#include <iostream>
#include<string>
#include<sstream>
#include<map>
#include<cmath>
#include<stack>
using namespace std;
map<char, bool>priority_addminus = \
{ {'+', true}, { '-',true }, { '*',false }, { '/',false }, { '^',false }}, priority_muldiv = \
{ {'+', true}, { '-',true }, { '*',true }, { '/',true }, { '^',false }}, priority_pow = \
{ {'+', true}, { '-',true }, { '*',true }, { '/',true }, { '^',true }};
// , priority_leftquotient = \
// { {'+', false}, { '-',false }, { '*',false }, { '/',false }, { '^',false } }, priority_rightquotient = \
// { {'+', true}, { '-',true }, { '*',true }, { '/',true }, { '^',true }};
map<char, map<char, bool>> priority_map{ {'+',priority_addminus},{'-',priority_addminus},{'*',priority_muldiv},{'/',priority_muldiv},{'^',priority_pow} };
// ,{'(',priority_leftquotient},{')',priority_rightquotient}
// td后面记得改成double……
int calSwitch(double num1, char op, double num2)
{
	switch (op)
	{
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	case '^': return pow(num1, num2);
	default: return 0;
	}
}
// dtd 已知会导致崩溃的输入：-1、不匹配的括号
class Expression
{
	string expression;
	stack<int> operations;
	stack<int> opnums;
public:
	string getExpression()const { return expression; }
	bool empty() { return expression.empty(); }
	void init(string input) { expression = input; }
	bool calc() {
		// try
		// {
		if (opnums.size() < 2)
		{
			Dialog_Error("表达式错误！", "表达式中操作数的数量不匹配！");
			expression = "";
			return false;
		}
		int b = opnums.top();
		// !啊catch不住？？？
		opnums.pop();
		int a = opnums.top();
		opnums.pop();
		char c = operations.top();
		operations.pop();
		opnums.push(calSwitch(a, c, b));
		// }
		// catch (exception e)
		// {
		// 	Dialog_Error("表达式错误！", "表达式中可能存在连续的运算符！");
		// 	cerr << "Error: " << e.what() << endl;
		// }
		return true;
	}

	int calculate() {
		char input;
		stringstream sstream(expression);
		while (!operations.empty())operations.pop();
		while (!opnums.empty())opnums.pop();

		while (sstream.get(input))
		{
			if (isdigit(input))
			{
				// sstream.putback(c);
				// // ！原来有这个函数……
				// int num;
				// sstream >> num;
				// opnums.push(num);
				// !麻了这样始终push的0……搞不懂……
				int num = input - '0';
				while (isdigit(input = sstream.get()))
				{
					num = num * 10 + (input - '0');
				}
				sstream.putback(input);
				if (opnums.size() == 0 && operations.size() == 1)
				{
					if (operations.top() == '-')
					{
						operations.pop();
						opnums.push(num * -1);
					}
					else if (operations.top() == '+') opnums.push(num);
					// dtd 错误处理
					else
					{
						Dialog_Error("表达式错误！", "表达式中出现多余的符号");
						return -1;
					}
					continue;
				}
				// !然后意外发现这样以后 -1 + 2 * 2也处理好了……
				opnums.push(num);
			}
			// !FT补全几次都补全不对……
			// ~~下面参考了https://blog.csdn.net/qq_41404557/article/details/115207653
			// !woq https://blog.csdn.net/PengHao666999/article/details/135899403的有图例代码也更简单！
			else if (input == '(')
			{
				// if (operations.empty())operations.push(c);continue;
				// while (!operations.empty() && priority_map[operations.top()][c] && priority_map[operations.top()][c] <= priority_map[operations.top()][c])
				// {
				// 	int num2 = opnums.top();
				// 	opnums.pop();
				// 	int num1 = opnums.top();
				// 	opnums.pop();
				// 	char op = operations.top();
				// 	operations.pop();
				// 	opnums.push(calSwitch(num1, op, num2));
				// }
				// operations.push(c);

				operations.push(input);
			}
			else if (input == ')')
			{
				while (operations.top() != '(')calc();
				operations.pop();
			}
			else
			{
				while (!operations.empty() && operations.top() != '(' && priority_map[operations.top()][input])
					// !注意这里就是比较栈顶元素是否比当前的大……
					if (!calc())return -1;
				operations.push(input);
			}
			// lastOp = c;
		}
		while (!operations.empty())
		{
			if (operations.top() == '(' || operations.top() == ')')
			{
				// dtd分.h后弹出错误Dialog
				Dialog_Error("表达式错误！", "表达式中存在不匹配的括号");
				return -1;
			}
			// if (opnums.size() != operations.size() + 1)
			// {
			// 	return -1;
			// }
			// !中途就要计算的……不能在这里检查……
			// if (opnums.size() < 2)
			// {
			// 	if (operations.top() == '+')
			// 		return opnums.top();
			// 	else if (operations.top() == '-')
			// 		return opnums.top() * -1;
			// 	else
			// 		return -1;
			// }
			int num2 = opnums.top();
			opnums.pop();
			int num1 = opnums.top();
			opnums.pop();
			char op = operations.top();
			operations.pop();
			opnums.push(calSwitch(num1, op, num2));
		}
		return opnums.top();
	}

}expression;
