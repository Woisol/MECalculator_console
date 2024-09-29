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
		// !������֧��0��index����
		init_pair(1, COLOR_WHITE, COLOR_BLACK);		// �׵׺���
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// @�ڵ׻���
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// �Ƶ׺���
		init_pair(4, COLOR_BLACK, COLOR_WHITE);		// ##�ڵװ���
		init_pair(5, COLOR_RED, COLOR_WHITE);		// ����װ���
		init_pair(6, COLOR_WHITE, COLOR_RED);		// ���׵׺���

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
// !�����һ��React��״̬;)
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
		// ~~������С������ˡ���
		// !ܳ�����WIN_WIDTH̫���˵���ˢ�������ˡ����㻹��Ϊ��vsc������cmd�Ͳ��С�������
		// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
		// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
		// const char program_title[] = title;
		mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
		setColor(3);
		mvprintw(WIN_HEIGHT / 2, 10, description.c_str());

		const char* COPYRIGHT = "Copyright @ 2024 Woisol-G";
		mvprintw(WIN_HEIGHT - 1, WIN_WIDTH - strlen(COPYRIGHT) - 1, COPYRIGHT);
		// !�����ˡ���

		for (auto i = 0; i < optionsSize; i++)
		{
			SelectOption(options[i], i);
		}

		ch = getch();
		if (ch == 2)selectOption = (selectOption + 1) % optionsSize;
		else if (ch == 3)selectOption = (selectOption - 1 > -1 ? selectOption - 1 : optionsSize - 1) % optionsSize;
		// !KEY_UP��KEY_DOWN���񲻶ԡ���
		else if (ch > 48 && ch <= 48 + optionsSize) { return ch - 49; }
		else if (ch == 10 || ch == ' ') { return selectOption; }

		// mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
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
}
// !������js�������İ���Щ�ŵ���һ���ļ�����
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
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "�����������");
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
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "�����������");
	refresh();
	getch();
}

// ~~ ��������stod��ֱ�Ӷ�ȡstring�����֣�
// !������������޷������������ζ�ȡ�ˡ���
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
	// !wok��˵��������refresh�ˡ���
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
	// !���õĲ����㡭��
	stringstream checkStream = stringstream(input);
	// !ܳ����ֱ�Ӵ洢������Ȼ>>�˾ͻز����ˡ���
	// !������Ǳ����ȶ���һ����Ȼ���ǳ������õĳ�ʼֵ����Ϊ��ֵ��
	// if ((*inputCheckFunc)(stringstream(input)))
	// if ((*inputCheckFunc)(checkStream))
	// return stringstream(input);
	// ��������ʵԭ������stringstream���ܿ������졭������
	// Dialog_Error("�������", "��������������⣬�����԰ɣ�");
	// !wok����C++��js'��"�ǲ�ͬ���ˡ���
	// return stringstream();
	// !���������е����ˡ���
	return input;
}
