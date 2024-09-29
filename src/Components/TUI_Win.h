#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include "../../lib/include/curses.h"
// #include <algorithm>
using namespace std;
#define WIN_WIDTH 58
#define WIN_HEIGHT 22
bool COLOR_SUPPORT = false;
void initColor() {
	if (COLOR_SUPPORT = has_colors())
	{
		start_color();
		// !啊，不支持0的index……
		init_pair(1, COLOR_WHITE, COLOR_BLACK);		// 白底黑字
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// @黑底黄字
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// 黄底黑字
		init_pair(4, COLOR_BLACK, COLOR_WHITE);		// ##黑底白字
		init_pair(5, COLOR_RED, COLOR_WHITE);		// ！红底白字
		init_pair(6, COLOR_WHITE, COLOR_RED);		// ！白底红字

	}
	else
	{
		cerr << "Err: Color support not available." << endl;
	}
}
int setColor(int pair = 1) {
	if (COLOR_SUPPORT)
	{
		return attron(COLOR_PAIR(pair));
	}
	return 0;
}

//**----------------------------Windows-----------------------------------------------------
int selectOption = 0;
// !借鉴了一下React的状态;)
void SelectOption(string title, int index) {
	if (index == selectOption)setColor(4);
	else setColor();
	title = " " + to_string(index + 1) + ". " + title + " ";
	mvprintw(WIN_HEIGHT / 2 + index + 1, 15, title.c_str());
}
int Win_Select(string title, string description, vector<string> options) {
	char ch;
	const int optionsSize = options.size();
	selectOption %= optionsSize;
	title = " " + title + " ";
	while (1)
	{
		clear();
		setColor(2);
		// box(stdscr, 3, 3);
		box(stdscr, 15, 15);
		// box(stdscr, 0, 0);
		setColor(2);
		// printw("Welcome to the Calculator!");
		// ~~这个就行……服了……
		// !艹是你的WIN_WIDTH太高了导致刷到下面了……你还以为是vsc启动的cmd就不行……啊啊
		// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
		// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
		// const char program_title[] = title;
		mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
		setColor(3);
		mvprintw(WIN_HEIGHT / 2, 10, description.c_str());

		const char* COPYRIGHT = "Copyright @ 2024 Woisol-G";
		mvprintw(WIN_HEIGHT - 1, WIN_WIDTH - strlen(COPYRIGHT) - 1, COPYRIGHT);
		// !害算了……

		for (auto i = 0; i < optionsSize; i++)
		{
			SelectOption(options[i], i);
		}

		ch = getch();
		if (ch == 2)selectOption = (selectOption + 1) % optionsSize;
		else if (ch == 3)selectOption = (selectOption - 1 > -1 ? selectOption - 1 : optionsSize - 1) % optionsSize;
		// !KEY_UP和KEY_DOWN好像不对……
		else if (ch > 48 && ch <= 48 + optionsSize) { return ch - 49; }
		else if (ch == 10 || ch == ' ') { return selectOption; }

		// mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
		// move(WIN_HEIGHT /2 + 3, 10)
		// mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
		// mvprintw(1, 0, "#       Welcome to the Calculator!               #");
		// mvprintw(2, 0, "#  Please select a mode:                         #");
		// mvprintw(3, 0, "#  1. 一元稀疏多项式                             #");
		// mvprintw(4, 0, "#  2. 算法表达式求值                             #");
		// mvprintw(5, 0, "#                                                 #");
		// mvprintw(6, 0, "#  当前页面为命令行界面，由C++语言编写。为了更好的体验， #");
		// mvprintw(7, 0, "#  您可以打开项目中的Calculator_GUI.exe文件，使用图形化  #");
		// mvprintw(8, 0, "#  界面进行操作。                               #");
		// mvprintw(9, 0, "#  项目完全独立制作，源码发布在了Github上，希望可以得到您的#");
		// mvprintw(10, 0, "#  star                                          #");
		// mvprintw(11, 0, "#                       2024-09-28             #");
		// mvprintw(12, 0, "#                Copyright @ 2024 Woisol-G     #");
		// mvprintw(13, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
		refresh();             // 刷新屏幕以显示内容
	}
}
// !难以像js那样灵活的把这些放到另一个文件……
void Dialog_Info(string title, vector<string> info) {
	clear();
	setColor(2);
	box(stdscr, 15, 15);
	title = " " + title + " ";
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
	setColor();
	for (auto i = 0; i < info.size(); i++)
	{
		mvprintw(WIN_HEIGHT / 2 + i, WIN_WIDTH / 2 - strlen(info[i].c_str()) / 2, info[i].c_str());
	}
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "按任意键返回");
	refresh();
	getch();
}
void Dialog_Error(string title, string error) {
	clear();
	setColor(6);
	box(stdscr, 15, 15);
	title = " " + title + " ";
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
	setColor(5);
	mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2 - strlen(error.c_str()) / 2, error.c_str());
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "按任意键返回");
	refresh();
	getch();
}

// ~~ ！可以用stod来直接读取string的数字！
// !不行用这个就无法像流那样依次读取了……
string Dialog_Input(string title) {
	clear();
	echo();
	setColor(2);
	box(stdscr, 15, 15);
	title = " " + title + " ";
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
	move(WIN_HEIGHT / 2, 10);
	setColor();
	refresh();
	// !wok我说……忘记refresh了……
	char input[100];
	// getline(cin, input);

	// stringstream sStream;
	// while (inputChar != 10)
	// {
	// 	// sStream.
	// 	sStream << inputChar;
	// 	inputChar = getch();
	// }
	getnstr(input, 100);
	// !内置的不更香……
	stringstream checkStream = stringstream(input);
	// !艹不能直接存储……不然>>了就回不来了……
	// !额不过还是必须先定义一个不然“非常量引用的初始值必须为左值”
	// if ((*inputCheckFunc)(stringstream(input)))
	// if ((*inputCheckFunc)(checkStream))
	// return stringstream(input);
	// ！所以其实原因在于stringstream不能拷贝构造…………
	// Dialog_Error("输入错误！", "输入的数据有问题，再试试吧！");
	// !wok忘记C++和js'和"是不同的了……
	// return stringstream();
	// !麻了这里有点绕了……
	return input;
}
