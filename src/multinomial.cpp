#include <iostream>
#include<sstream>
#include <vector>
#include <algorithm>
// #include"TUI.cpp"
// !TUI.cpp包含自身……
using namespace std;
class Multinomial
{
	vector<pair<int, int>> multinomialIndicator;
public:
	static int initNum;
	void init(stringstream input) {
		if (input.str().empty())return;
		if (multinomialIndicator.size() > 0)multinomialIndicator.clear();
		int n;
		int a, b;
		input >> n;
		while (n--)
			// for (int i = 0;i < n;i++)
		{
			input >> a >> b;
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
	string print() const {
		string outputString = "";
		for (auto p : multinomialIndicator)
		{
			if (!outputString.empty() && p.first < 0)outputString.pop_back();
			// !什么逻辑艹
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