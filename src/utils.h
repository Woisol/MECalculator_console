#pragma once
#include<string>
#include<algorithm>
using namespace std;
string better_double_to_string(double num) {
	string str = to_string(num);
	str.erase(str.find_last_not_of('0') + 1, string::npos);
	if (str.back() == '.')
	{
		str.pop_back();
	}
	return str;
}