#include <iostream>
#include"TUI.cpp"
using namespace std;
int main(int argc, char* argv[]) {
	// !为什么默认是1啊……
	// int modeSelectInput;
	// if(argv[0] == "--tui")
	if (argc == 1)
	{
		setlocale(LC_ALL, "");
		initscr();               // 初始化ncurses
		cbreak();                // 允许接收特殊键
		noecho();
		keypad(stdscr, TRUE);   // 启用功能键识别}
		initColor();
		// system("chcp 65001");

		bool back = false;
		// start:

			// create_centered_window("欢迎使用计算器！");
			// while (true)
			// {

		while (!back)
		{
			switch (Page_Welcome())
			{
			case 0:
				back = Page_Multinomial();
				break;
			case 1:
				Page_Expression("算法表达式求值计算器");
				back = true;
				break;
			case 2:
				// Page_About();
				break;
			case 3:
				back = true;
				break;
			default:
				clear();
				mvprintw(10, 1, "Unexpect error");
				refresh();
			}
			// }

		}
		endwin();              // 结束ncurses模式
	}
	return 0;
}

