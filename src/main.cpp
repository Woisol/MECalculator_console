#include <iostream>
#include"TUI.cpp"
using namespace std;
int main() {
	int modeSelectInput;

start:
	initscr();               // ��ʼ��ncurses
	cbreak();                // ������������
	echo();                // ����ʾ������ַ�
	keypad(stdscr, TRUE);   // ���ù��ܼ�ʶ��}
	initColor();
	// system("chcp 65001");

	print_welcome_screen();
	// create_centered_window("��ӭʹ�ü�������");
	cin >> modeSelectInput;
	switch (modeSelectInput)
	{
	case 1:
		print_mode_selection_screen("һԪϡ�����ʽ������");
		break;
	case 2:
		print_mode_selection_screen("�㷨���ʽ��ֵ������");
		break;
	default:
		clear();
		mvprintw(10, 1, "��������ȷ��ѡ�");
		refresh();
	}

	mvprintw(12, 0, "��������˳�...");
	getch();               // �ȴ��û�����

	endwin();              // ����ncursesģʽ
	return 0;
}

