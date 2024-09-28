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
		// !������֧��0��index����
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
	// ~~������С������ˡ���
	// !ܳ�����WIN_WIDTH̫���˵���ˢ�������ˡ����㻹��Ϊ��vsc������cmd�Ͳ��С�������
	// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
	// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - 14, "  Welcome to the Calculator!  ");
	setColor(3);
	mvprintw(WIN_HEIGHT / 2, 10, "Please select a mode:");
	setColor();
	mvprintw(WIN_HEIGHT / 2 + 1, 10, "1. һԪϡ�����ʽ");
	mvprintw(WIN_HEIGHT / 2 + 2, 10, "2. �㷨���ʽ��ֵ");
	mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
	// move(WIN_HEIGHT /2 + 3, 10)
	// mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	// mvprintw(1, 0, "#       Welcome to the Calculator!               #");
	// mvprintw(2, 0, "#  Please select a mode:                         #");
	// mvprintw(3, 0, "#  1. һԪϡ�����ʽ                             #");
	// mvprintw(4, 0, "#  2. �㷨���ʽ��ֵ                             #");
	// mvprintw(5, 0, "#                                                 #");
	// mvprintw(6, 0, "#  ��ǰҳ��Ϊ�����н��棬��C++���Ա�д��Ϊ�˸��õ����飬 #");
	// mvprintw(7, 0, "#  �����Դ���Ŀ�е�Calculator_GUI.exe�ļ���ʹ��ͼ�λ�  #");
	// mvprintw(8, 0, "#  ������в�����                               #");
	// mvprintw(9, 0, "#  ��Ŀ��ȫ����������Դ�뷢������Github�ϣ�ϣ�����Եõ�����#");
	// mvprintw(10, 0, "#  star                                          #");
	// mvprintw(11, 0, "#                       2024-09-28             #");
	// mvprintw(12, 0, "#                Copyright @ 2024 Woisol-G     #");
	// mvprintw(13, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	refresh();             // ˢ����Ļ����ʾ����
}

void print_mode_selection_screen(const std::string& mode) {
	mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	mvprintw(1, 0, "  %s                              ", mode.c_str());
	mvprintw(2, 0, "  �����룺                             ");
	refresh();
}
// void create_centered_window(const char* message) {
// 	int height = 10;  // ���ڸ߶�
// 	int width = 40;   // ���ڿ��
// 	int start_y = (LINES - height) / 2;  // ���е���ʼ y ����
// 	int start_x = (COLS - width) / 2;    // ���е���ʼ x ����

// 	// ����һ���´���
// 	WINDOW* win = newwin(height, width, start_y, start_x);
// 	box(win, 0, 0);  // ���Ʊ߿�
// 	mvwprintw(win, height / 2, (width - strlen(message)) / 2, "%s", message); // ������ʾ�ı�
// 	wrefresh(win);   // ˢ�´�������ʾ����

// 	getch();  // �ȴ��û�����
// 	delwin(win); // ɾ������
// }
