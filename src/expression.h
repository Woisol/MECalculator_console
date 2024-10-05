#pragma once
// td (-2*3)�޷�����

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
map<char, map<char, bool>> priority_map{ {'+',priority_addminus},{'-',priority_addminus},{'*',priority_muldiv},{'/',priority_muldiv},{'^',priority_pow} };
// dtd����ǵøĳ�double����
double calSwitch(double num1, char op, double num2)
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
// dtd ��֪�ᵼ�±��������룺-1����ƥ�������
class Expression
{
	string expression;
	stack<char> operations;
	stack<double> opnums;
public:
	string getExpression()const { return expression; }
	bool empty() { return expression.empty(); }
	void init(string input) { expression = input; }
	bool calc() {
		if (opnums.size() < 2)
		{
			Dialog_Error("���ʽ����", "���ʽ�в�������������ƥ�䣡");
			expression = "";
			return false;
		}
		double b = opnums.top();
		opnums.pop();
		double a = opnums.top();
		opnums.pop();
		char c = operations.top();
		operations.pop();
		opnums.push(calSwitch(a, c, b));
		return true;
	}

	int calculate() {
		char input;
		if (expression.find('.') != string::npos)
		{
			Dialog_Error("���ʽ����", "���ʽ�����ݲ�֧��С����");
			return -1;
		}
		stringstream sstream(expression);
		while (!operations.empty())operations.pop();
		while (!opnums.empty())opnums.pop();

		while (sstream.get(input))
		{
			if (isdigit(input))
			{
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
					// dtd ������
					else
					{
						Dialog_Error("���ʽ����", "���ʽ�г��ֶ���ķ���");
						return -1;
					}
					continue;
				}
				opnums.push(num);
			}
			else if (input == '(')
				operations.push(input);
			else if (input == ')')
			{
				if (operations.empty())
				{
					Dialog_Error("���ʽ����", "���ʽ�д��ڲ�ƥ�������");
					return -1;
				}
				while (!operations.empty() && operations.top() != '(')
				{
					if (operations.size() == 1 && operations.top() != '(')
					{
						Dialog_Error("���ʽ����", "���ʽ�д��ڲ�ƥ�������");
						return -1;
					}
					calc();
				}
				if (!operations.empty())
					operations.pop();
			}
			else
			{
				while (!operations.empty() && operations.top() != '(' && priority_map[operations.top()][input])
					if (!calc())return -1;
				operations.push(input);
			}
		}
		while (!operations.empty())
		{
			if (operations.top() == '(' || operations.top() == ')')
			{
				// dtd��.h�󵯳�����Dialog
				Dialog_Error("���ʽ����", "���ʽ�д��ڲ�ƥ�������");
				return -1;
			}
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
