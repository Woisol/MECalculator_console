// td ���test
// td �ֳ�.h������ȫ����cpp
#include <iostream>
#include"TUI.h"
using namespace std;
int main(int argc, char* argv[]) {
	// !ΪʲôĬ����1������
	// int modeSelectInput;
	// if(argv[0] == "--tui")
	if (argc == 1)
	{
		setlocale(LC_ALL, "");
		initscr();               // ��ʼ��ncurses
		cbreak();                // ������������
		noecho();
		keypad(stdscr, TRUE);   // ���ù��ܼ�ʶ��}
		initColor();
		// system("chcp 65001");

		bool back = false;
		// start:

			// create_centered_window("��ӭʹ�ü�������");
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
				back = Page_Expression();
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
		endwin();              // ����ncursesģʽ
	}
	return 0;
}

