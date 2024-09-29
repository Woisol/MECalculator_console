#pragma once

#include <iostream>
#include<sstream>
#include <vector>
#include <algorithm>
#include<cmath>
#include"TUI.h"
// !TUI.cpp����������
using namespace std;
class Multinomial
{
	vector<pair<int, int>> multinomialIndicator;
public:
	static int initNum;
	void init(string input) {
		if (input.empty())
		{
			Dialog_Error("�������", "����Ϊ�գ�");
			return;
		}
		if ([input]() {
			int n, count = 0;
			int Iint;
			stringstream sstream(input);
			sstream >> n;
			while (sstream >> Iint)
			{
				count++;
			}
			return count != 2 * n;
			}())
			// !�������������ǵ����ˡ���
		{
			Dialog_Error("�������", "�������ݵ���������ȷ��");return;
		}
		if (!all_of(input.begin(), input.end(), [](char c) {return c == ' ' || isdigit(c); }))
		{
			Dialog_Error("�������", "�������ݰ����Ƿ��ַ���");return;
		}
		if (multinomialIndicator.size() > 0)multinomialIndicator.clear();
		int n;
		int a, b;
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
				// �������ˣ���������ʧЧ���⣡
			}
			else
				p++;
		}
		initNum++;
	}
	Multinomial operator+(const Multinomial& other) const {
		Multinomial res;
		res.multinomialIndicator = multinomialIndicator;
		// td��ʵ����Ļ��������Ż�һ�¡���
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
	int calculate(int x) const {
		int res = 0;
		for (auto p : multinomialIndicator)
		{
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
				res.multinomialIndicator.push_back(make_pair(p.first, 0));
			}
		}
		return res;
	}
	string print() const {
		string outputString = "";
		for (auto p : multinomialIndicator)
		{
			if (!outputString.empty() && p.first < 0)outputString.pop_back();
			// !ʲô�߼�ܳ
			if (p.first == 0)continue;
			if (p.second == 1)outputString += (p.first == 1 ? "" : p.first == -1 ? "-" : to_string(p.first)) + "x" + "+";
			else if (p.second == 0) outputString += to_string(p.first) + "+";
			else outputString += (p.first == 1 ? "" : p.first == -1 ? "-" : to_string(p.first)) + "x^" + to_string(p.second) + "+";
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