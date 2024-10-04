#pragma once

#include <iostream>
#include<sstream>
#include <vector>
#include <algorithm>
#include<cmath>
#include"TUI.h"
#include"process.h"
// !TUI.cpp包含自身……
using namespace std;
class Multinomial
{
	vector<pair<double, double>> multinomialIndicator;
public:
	static int initNum;
	void init(string input) {
		if (input.empty())
		{
			Dialog_Error("输入错误！", "输入为空！");
			return;
		}
		// **检查输入合法性
		if ([&]() {
			int n, count = 0;
			double Idouble;
			if (!isdigit(input[0]) || input[0] == '0')
			{
				Dialog_Error("输入错误！", "输入的n非正整数");
				return true;
			}
			stringstream sstream(input);
				sstream >> n;
				while (sstream >> Idouble)
				{
					count++;
				}
			if (count != 2 * n)
			{
				Dialog_Error("输入错误！", "输入数据的数量不正确或含有非法字符！！");return true;
			}
			return false;

			}())return;
		// !额匿名函数忘记调用了……
	// {
	// 	Dialog_Error("输入错误！", "输入数据的数量不正确！");return;
	// }
	// if (!all_of(input.begin(), input.end(), [](char c) {return c == ' ' || isdigit(c); }))
	// {
	// 	Dialog_Error("输入错误！", "输入数据包含非法字符！");return;
	// }
		if (multinomialIndicator.size() > 0)multinomialIndicator.clear();
		// if (input[0] == '0')
		// {
		// 	multinomialIndicator.push_back(make_pair(0, 0));
		// 	return;
		// }
		int n;
		double a, b;
		stringstream sstream(input);
		sstream >> n;
		while (n--)
			// for (int i = 0;i < n;i++)
		{
			sstream >> a >> b;
			multinomialIndicator.push_back(make_pair(a, b));
			// multinomialIndicator.push_back(make_pair(indicators[i * 2], indicators[i * 2 + 1]));
		}
		sort(multinomialIndicator.begin(), multinomialIndicator.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
			return p.second > q.second;
			});
		for (auto p = multinomialIndicator.begin(); (p + 1) != multinomialIndicator.end(); )
		{
			if (p->second == (p + 1)->second)
			{
				p->first += (p + 1)->first;
				multinomialIndicator.erase(p + 1);
				// ！忘记了！！迭代器失效问题！
			}
			else
				p++;
		}
		initNum++;
	}
	Multinomial operator+(const Multinomial& other) const {
		Multinomial res;
		res.multinomialIndicator = multinomialIndicator;
		// td其实降序的话可以再优化一下……
		for (auto p : other.multinomialIndicator)
		{
			auto it = find_if(res.multinomialIndicator.begin(), res.multinomialIndicator.end(), [p](const pair<int, int>& q) {
				return q.second == p.second;
				});
			if (it == res.multinomialIndicator.end())
			{
				res.multinomialIndicator.push_back(p);
			}
			else
			{
				it->first += p.first;
			}
		}
		sort(res.multinomialIndicator.begin(), res.multinomialIndicator.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
			return p.second > q.second;
			});
		return res;
	}
	Multinomial operator-(const Multinomial& other) const {
		Multinomial res;
		res.multinomialIndicator = multinomialIndicator;
		for (auto p : other.multinomialIndicator)
		{
			auto it = find_if(res.multinomialIndicator.begin(), res.multinomialIndicator.end(), [p](const pair<int, int>& q) {
				return q.second == p.second;
				});
			if (it == res.multinomialIndicator.end())
			{
				res.multinomialIndicator.push_back(make_pair(-p.first, p.second));
			}
			else
			{
				it->first -= p.first;
				if (it->first == 0)
				{
					res.multinomialIndicator.erase(it);
				}
			}
		}
		sort(res.multinomialIndicator.begin(), res.multinomialIndicator.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
			return p.second > q.second;
			});
		return res;
	}
	Multinomial operator*(const Multinomial& other) const {
		Multinomial res;
		for (auto p : multinomialIndicator)
		{
			for (auto q : other.multinomialIndicator)
			{
				res.multinomialIndicator.push_back(make_pair(p.first * q.first, p.second + q.second));
			}
		}
		sort(res.multinomialIndicator.begin(), res.multinomialIndicator.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
			return p.second > q.second;
			});
		for (auto p = res.multinomialIndicator.begin(); (p + 1) != res.multinomialIndicator.end(); )
		{
			if (p->second == (p + 1)->second)
			{
				p->first += (p + 1)->first;
				res.multinomialIndicator.erase(p + 1);
			}
			else
				p++;
		}

		return res;
	}
	double calculate(double x) const {
		double res = 0;
		for (auto p : multinomialIndicator)
		{
			if (p.second < 1 && p.second > -1 && x < 0 || p.second < 0 && x == 0)
			{
				Dialog_Error("数学错误！", "输入的x不在定义域内！");res = -1;return res;
			}
			res += p.first * pow(x, p.second);
		}
		return res;
	}
	Multinomial derivative() {
		Multinomial res;
		for (auto p : multinomialIndicator)
		{
			if (p.second > -1)
			{
				res.multinomialIndicator.push_back(make_pair(p.first * p.second, p.second - 1));
			}
			else if (p.second == -1)
			{
				Dialog_Error("输入错误", "输入了特殊求导的x^-1，暂不支持该多项式求导！");
				res.multinomialIndicator.clear();
				return res;
			}
		}
		return res;
	}
	string print() const {
		string outputString = "";
		for (auto p : multinomialIndicator)
		{
			if (!outputString.empty() && p.first < 0)outputString.pop_back();
			// !什么逻辑艹
			if (p.first == 0)continue;
			if (p.second == 1)outputString += (p.first == 1 ? "" : p.first == -1 ? "-" : better_double_to_string(p.first)) + "x" + "+";
			else if (p.second == 0) outputString += better_double_to_string(p.first) + "+";
			else outputString += (p.first == 1 ? "" : p.first == -1 ? "-" : better_double_to_string(p.first)) + "x^" + better_double_to_string(p.second) + "+";
		}
		if (outputString.empty())return "0";
		outputString.pop_back();
		return outputString;
	}
	void clear() {
		multinomialIndicator.clear();
	}
};
// Multinomial::initNum = 0;
Multinomial multinomials[2] = { Multinomial(), Multinomial() };
Multinomial res;
// void mutinomial() {
// }