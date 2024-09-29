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

// bool multinomialInputCheck(stringstream& sstream) {
// 	int n, count;
// 	int input;
// 	sstream >> n;
// 	while (sstream >> input)
// 	{
// 		count++;
// 	}
// 	return count == 2 * n;
// }
int Multinomial::initNum = 0;
int Page_Welcome() {
	// while (1)
	// {
	// 	clear();
	// 	setColor(2);
	// 	// box(stdscr, 3, 3);
	// 	box(stdscr, 15, 15);
	// 	// box(stdscr, 0, 0);
	// 	setColor(2);
	// 	// printw("Welcome to the Calculator!");
	// 	// ~~这个就行……服了……
	// 	// !艹是你的WIN_WIDTH太高了导致刷到下面了……你还以为是vsc启动的cmd就不行……啊啊
	// 	// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
	// 	// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
	// 	const char program_title[] = " 欢迎使用本软件! ";
	// 	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(program_title) / 2, program_title);
	// 	setColor(3);
	// 	mvprintw(WIN_HEIGHT / 2, 6, " 使用上下方向键选择一个模式: ");
	// 	if (selectOption == 0)setColor(4);
	// 	else setColor();
	// 	mvprintw(WIN_HEIGHT / 2 + 1, 10, " 1. 一元稀疏多项式 ");
	// 	if (selectOption == 1)setColor(4);
	// 	else setColor();
	// 	mvprintw(WIN_HEIGHT / 2 + 2, 10, " 2. 算法表达式求值 ");
	// 	char ch = getch();
	// 	if (ch == 2 || ch == 3)selectOption = selectOption == 0 ? 1 : 0;
	// 	// !KEY_UP和KEY_DOWN好像不对……
	// 	else if (ch == 10) { return selectOption; }


	// 	// mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
	// 	// move(WIN_HEIGHT /2 + 3, 10)
	// 	// mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	// 	// mvprintw(1, 0, "#       Welcome to the Calculator!               #");
	// 	// mvprintw(2, 0, "#  Please select a mode:                         #");
	// 	// mvprintw(3, 0, "#  1. 一元稀疏多项式                             #");
	// 	// mvprintw(4, 0, "#  2. 算法表达式求值                             #");
	// 	// mvprintw(5, 0, "#                                                 #");
	// 	// mvprintw(6, 0, "#  当前页面为命令行界面，由C++语言编写。为了更好的体验， #");
	// 	// mvprintw(7, 0, "#  您可以打开项目中的Calculator_GUI.exe文件，使用图形化  #");
	// 	// mvprintw(8, 0, "#  界面进行操作。                               #");
	// 	// mvprintw(9, 0, "#  项目完全独立制作，源码发布在了Github上，希望可以得到您的#");
	// 	// mvprintw(10, 0, "#  star                                          #");
	// 	// mvprintw(11, 0, "#                       2024-09-28             #");
	// 	// mvprintw(12, 0, "#                Copyright @ 2024 Woisol-G     #");
	// 	// mvprintw(13, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	// 	refresh();             // 刷新屏幕以显示内容

	// }

	return Win_Select("欢迎使用本软件!", "按↑↓或对应的数字键选择模式:", { "一元稀疏多项式 ", "算法表达式求值","关于此软件作者","退出" });
	// !可以直接用类似js对象的形式隐式转换成vector！wok这下方便了
}

int Page_Multinomial() {
	// bool back = false;
	// while (!back)
	while (true)
	{
		// const string description = ();
		// vector<string> options;
		// if (Multinomial::initNum == 2) options = { "查看多项式a,b","计算多项式a+b", "计算多项式a-b","重新输入", "返回上一级", "退出" };
		// else options = { "输入多项式" };
		switch (Multinomial::initNum)
		{
		case 0:
			switch (Win_Select(" 一元稀疏多项式 ", "现在还没有输入多项式，请选择输入", { "输入多项式","返回上一级","退出" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("请输入多项式项数n与其系数指数: "));
				// multinomials[Multinomial::initNum].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
				// !不行提前预定如果出错会导致奇怪的文案……
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			default:
				break;
			}
			break;
			// !这里忘记break了……正常输入看不出来但是一无效输入就文案bug了……
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
				// Dialog_Input("输入x = ：") >> x;
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
					// !艹怎么突然就可爱风了……
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
					// Dialog_Error("Error", "Unknown Error");
				}
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
			// switch (Win_Select(" 一元稀疏多项式 ", Multinomial::initNum == 0 ? "现在还没有输入多项式，请选择输入" : "当前输入了" + to_string(Multinomial::initNum) + "个多项式，最多只能输入2个，请选择操作:", options))
			// {
			// case 0:
			// 	if (Multinomial::initNum == 2)
			// 		Dialog_Info("a,b多项式如下：", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
			// 	else
			// 	{
			// 	}
			// 	break;
			// case 1:
			// 	if (Multinomial::initNum == 2)
			// 	{
			// 		res = multinomials[0] + multinomials[1];
			// 		Dialog_Info(multinomials[0].print() + " + " + multinomials[1].print() + " =", { res.print() });
			// 	}
			// 	break;
			// case 2:
			// 	if (Multinomial::initNum == 2)
			// 	{
			// 		res = multinomials[0] - multinomials[1];
			// 		Dialog_Info(multinomials[0].print() + " - " + multinomials[1].print() + " =", { res.print() });
			// 	}
			// 	break;
			// case 3:

			// 	switch (Win_Select("重新输入", "需要重新输入哪些多项式？", { "第一个多项式", "第二个多项式","小孩子才做选择()","算了算了，我不想了" }))
			// 		// !艹怎么突然就可爱风了……
			// 	{
			// 	case 0:
			// 		Multinomial::initNum = 1;
			// 		multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: ", multinomialInputCheck));
			// 		break;
			// 	case 1:
			// 		Multinomial::initNum = 1;
			// 		multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
			// 		break;
			// 	case 2:
			// 		Multinomial::initNum = 0;
			// 		multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: ", multinomialInputCheck));
			// 		multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
			// 		break;
			// 	default:
			// 		break;
			// 		// Dialog_Error("Error", "Unknown Error");
			// 	}
			// 	break;
			// case 4:
			// 	// back = true;
			// 	return 0;
			// case 5:
			// 	return 1;
			// }
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
				// !额[&]多个&就不给传唤了……
				calRes = expression.calculate();
				// !这个变量必须在switch外面声明……不然报错jump to case label（这个报错什么鬼谁懂怎么改……）
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
// void create_centered_window(const char* message) {
// 	int height = 10;  // 窗口高度
// 	int width = 40;   // 窗口宽度
// 	int start_y = (LINES - height) / 2;  // 居中的起始 y 坐标
// 	int start_x = (COLS - width) / 2;    // 居中的起始 x 坐标

// 	// 创建一个新窗口
// 	WINDOW* win = newwin(height, width, start_y, start_x);
// 	box(win, 0, 0);  // 绘制边框
// 	mvwprintw(win, height / 2, (width - strlen(message)) / 2, "%s", message); // 居中显示文本
// 	wrefresh(win);   // 刷新窗口以显示内容

// 	getch();  // 等待用户输入
// 	delwin(win); // 删除窗口
// }
