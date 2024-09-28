#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include "../lib/include/curses.h"
#include "multinomial.cpp"
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
	mvprintw(WIN_HEIGHT / 2 + index + 1, 10, title.c_str());
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
		mvprintw(WIN_HEIGHT / 2, 6, description.c_str());

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
		mvprintw(WIN_HEIGHT / 2 + i, 10, info[i].c_str());
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

stringstream Dialog_Input(string title, bool (*inputCheckFunc)(stringstream&)) {
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
	if ((*inputCheckFunc)(checkStream))
		return stringstream(input);
	// ！所以其实原因在于stringstream不能拷贝构造…………
	Dialog_Error("输入错误！", "输入的数据有问题，再试试吧！");
	// !wok忘记C++和js'和"是不同的了……
	return stringstream();
	// !麻了这里有点绕了……
	// return input;
}
bool multinomialInputCheck(stringstream& sstream) {
	int n, count;
	int input;
	sstream >> n;
	while (sstream >> input)
	{
		count++;
	}
	return count == 2 * n;

}
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

	return Win_Select("欢迎使用本软件!", " 使用上下方向键选择一个模式: ", { "一元稀疏多项式 ", "算法表达式求值","关于此软件作者","退出" });
	// !可以直接用类似js对象的形式隐式转换成vector！wok这下方便了
}

int Page_Multinomial() {
	// bool back = false;
	// while (!back)
	while (true)
	{
		// const string description = ();
		vector<string> options;
		if (Multinomial::initNum == 2) options = { "查看多项式a,b","计算多项式a+b", "计算多项式a-b","重新输入", "返回上一级", "退出" };
		else options = { "输入多项式" };
		switch (Win_Select(" 一元稀疏多项式 ", Multinomial::initNum == 0 ? "现在还没有输入多项式，请选择输入" : "当前输入了" + to_string(Multinomial::initNum) + "个多项式，最多只能输入2个，请选择操作:", options))
		{
		case 0:
			if (Multinomial::initNum == 2)
				Dialog_Info("a,b多项式如下：", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
			else
			{
				multinomials[Multinomial::initNum].init(Dialog_Input("请输入多项式项数n与其系数指数: ", multinomialInputCheck));
				// multinomials[Multinomial::initNum].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
				// !不行提前预定如果出错会导致奇怪的文案……
			}
			break;
		case 1:
			if (Multinomial::initNum == 2)
			{
				res = multinomials[0] + multinomials[1];
				Dialog_Info(multinomials[0].print() + " + " + multinomials[1].print() + " =", { res.print() });
			}
			break;
		case 2:
			if (Multinomial::initNum == 2)
			{
				res = multinomials[0] - multinomials[1];
				Dialog_Info(multinomials[0].print() + " - " + multinomials[1].print() + " =", { res.print() });
			}
			break;
		case 3:

			switch (Win_Select("重新输入", "需要重新输入哪些多项式？", { "第一个多项式", "第二个多项式","小孩子才做选择()","算了算了，我不想了" }))
				// !艹怎么突然就可爱风了……
			{
			case 0:
				Multinomial::initNum = 1;
				multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: ", multinomialInputCheck));
				break;
			case 1:
				Multinomial::initNum = 1;
				multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
				break;
			case 2:
				Multinomial::initNum = 0;
				multinomials[0].init(Dialog_Input("请输入第一个多项式项数n与其系数指数: ", multinomialInputCheck));
				multinomials[1].init(Dialog_Input("请输入第二个多项式项数n与其系数指数: ", multinomialInputCheck));
				break;
			default:
				break;
				// Dialog_Error("Error", "Unknown Error");
			}
			break;
		case 4:
			// back = true;
			return 0;
		case 5:
			return 1;
		}
	}
}

void Page_Expression(const std::string& tilte) {
	refresh();
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
