#include <iostream>
#include"TUI.cpp"
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

	start:

		// create_centered_window("��ӭʹ�ü�������");
		// while (true)
		// {

		switch (Page_Welcome())
		{
		case 0:
			Page_Multinomial();
			break;
		case 1:
			Page_Expression("�㷨���ʽ��ֵ������");
			break;
		default:
			clear();
			mvprintw(10, 1, "Unexpect error");
			refresh();
		}
		// }
		endwin();              // ����ncursesģʽ
	}
	return 0;
}

