#include <iostream>
#include"TUI.cpp"
using namespace std;
int main() {
	int modeSelectInput;

start:
	initscr();               // 初始化ncurses
	cbreak();                // 允许接收特殊键
	echo();                // 不显示输入的字符
	keypad(stdscr, TRUE);   // 启用功能键识别}
	initColor();
	// system("chcp 65001");

	print_welcome_screen();
	// create_centered_window("欢迎使用计算器！");
	cin >> modeSelectInput;
	switch (modeSelectInput)
	{
	case 1:
		print_mode_selection_screen("一元稀疏多项式计算器");
		break;
	case 2:
		print_mode_selection_screen("算法表达式求值计算器");
		break;
	default:
		clear();
		mvprintw(10, 1, "请输入正确的选项！");
		refresh();
	}

	mvprintw(12, 0, "按任意键退出...");
	getch();               // 等待用户按键

	endwin();              // 结束ncurses模式
	return 0;
}

