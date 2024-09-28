#include<iostream>
#include<cstring>
#include "../lib/include/curses.h"
using namespace std;
#define WIN_WIDTH 58
#define WIN_HEIGHT 22
bool COLOR_SUPPORT = false;
void initColor() {
	if (COLOR_SUPPORT = has_colors())
	{
		start_color();
		// !啊，不支持0的index……
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
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
void print_welcome_screen() {
	clear();
	// box(stdscr, 3, 3);
	box(stdscr, 15, 15);
	// box(stdscr, ACS_PI, ACS_PI);
	setColor(2);
	// printw("Welcome to the Calculator!");
	// ~~这个就行……服了……
	// !艹是你的WIN_WIDTH太高了导致刷到下面了……你还以为是vsc启动的cmd就不行……啊啊
	// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
	// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - 14, "  Welcome to the Calculator!  ");
	setColor(3);
	mvprintw(WIN_HEIGHT / 2, 10, "Please select a mode:");
	setColor();
	mvprintw(WIN_HEIGHT / 2 + 1, 10, "1. 一元稀疏多项式");
	mvprintw(WIN_HEIGHT / 2 + 2, 10, "2. 算法表达式求值");
	mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
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

void print_mode_selection_screen(const std::string& mode) {
	mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	mvprintw(1, 0, "  %s                              ", mode.c_str());
	mvprintw(2, 0, "  请输入：                             ");
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
