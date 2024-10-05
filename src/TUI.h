#pragma once

#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include "../lib/include/curses.h"
#include "./Components/TUI_Win.h"
#include "multinomial.h"
#include"expression.h"
using namespace std;

int Multinomial::initNum = 0;
int Page_Welcome() {
	return Win_Select("欢迎使用本软件!", "按↑↓或对应的数字键选择模式:", { "一元稀疏多项式 ", "算法表达式求值","在GitHub上查看本软件","退出" });
}

int Page_Multinomial() {
	while (true)
	{
		switch (Multinomial::initNum)
		{
		case 0:
			switch (Win_Select(" 一元稀疏多项式 ", "现在还没有输入多项式，请选择输入", { "输入多项式","返回上一级","退出" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("请输入多项式项数n与其系数指数: "));
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			default:
				break;
			}
			break;
		case 1:
			switch (Win_Select(" 一元稀疏多项式 ", "当前输入了1个多项式，请选择", { "输入第二个多项式","查看第一个多项式","求值","求导","重新输入第一个多项式","返回上一级","退出" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: "));
				break;
			case 1:
				Dialog_Info("第一个多项式如下：", { multinomials[0].print() });
				break;
			case 2:
				double x;
				x = atof(Dialog_Input("请输入x = ：").c_str());
				Dialog_Info(" x = " + better_double_to_string(x) + "时，" + multinomials[0].print() + " =", { better_double_to_string(multinomials[0].calculate(x)) });
				break;
			case 3:
				Dialog_Info(multinomials[0].print() + "的导数为：", { multinomials[0].derivative().print() });
				break;
			case 4:
				Multinomial::initNum = 0;
				multinomials[0].init(Dialog_Input("请重新输入第一个多项式项数n与其系数指数: "));
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
			break;
		case 2:
			switch (Win_Select(" 一元稀疏多项式 ", "当前输入了2个多项式，请选择", { "查看多项式a,b","计算多项式a+b", "计算多项式a-b","计算多项式a*b","重新输入","返回上一级","退出" }))
			{
			case 0:
				Dialog_Info("a,b多项式如下：", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
				break;
			case 1:
				res = multinomials[0] + multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " + (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 2:
				res = multinomials[0] - multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " - (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 3:
				res = multinomials[0] * multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " * (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 4:
				switch (Win_Select("重新输入", "需要重新输入哪些多项式？", { "第一个多项式", "第二个多项式","小孩子才做选择()","算了算了，我不想了" }))
				{
				case 0:
					Multinomial::initNum = 1;
					multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: "));
					break;
				case 1:
					Multinomial::initNum = 1;
					multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: "));
					break;
				case 2:
					Multinomial::initNum = 0;
					multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: "));
					multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: "));
					break;
				default:
					break;
				}
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
		}
	}
}

int Page_Expression() {
	while (true)
	{
		if (expression.empty())
		{
			int calRes;
			switch (Win_Select("算法表达式求值计算器", "当前未输入表达式，请选择输入：", { "输入表达式并计算", "返回上一级", "退出" }))
			{
			case 0:
				expression.init(Dialog_Input("请输入算法表达式，注意数字和符号之间不能有空格："));
				calRes = expression.calculate();
				if (expression.getExpression().empty())continue;
				Dialog_Info(expression.getExpression() + " = ", { to_string(calRes) });
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			}
		}
		else
			switch (Win_Select("算法表达式求值计算器", "表达式已输入，请选择操作：", { "再次求值",  "重新输入", "返回上一级", "退出" }))
			{
			case 0:
				Dialog_Info(expression.getExpression() + " = ", { to_string(expression.calculate()) });
				break;
			case 1:
				expression.init(Dialog_Input("请重新输入算法表达式，不输入任何内容按下回车取消："));
				if (!expression.getExpression().empty())
					Dialog_Info(expression.getExpression() + " = ", { to_string(expression.calculate()) });
				break;
			case 2:
				return 0;
			case 3:
				return 1;
			}
	}
}