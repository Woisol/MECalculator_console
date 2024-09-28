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
		// !������֧��0��index����
		init_pair(1, COLOR_WHITE, COLOR_BLACK);		// �׵׺���
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// @�ڵ׻���
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// �Ƶ׺���
		init_pair(4, COLOR_BLACK, COLOR_WHITE);		// ##�ڵװ���
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
	mvprintw(WIN_HEIGHT / 2 + index + 1, 10, title.c_str());
}
int Win_Select(string title, string description, vector<string> options) {
	char ch;
	const int optionsSize = options.size();
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
		mvprintw(WIN_HEIGHT / 2, 6, description.c_str());

		for (auto i = 0; i < optionsSize; i++)
		{
			SelectOption(options[i], i);
		}

		ch = getch();
		if (ch == 2)selectOption = (selectOption + 1) % optionsSize;
		else if (ch == 3)selectOption = (selectOption - 1 > -1 ? selectOption - 1 : optionsSize - 1) % optionsSize;
		// !KEY_UP��KEY_DOWN���񲻶ԡ���
		else if (ch > 48 && ch <= 48 + optionsSize) { return ch - 49; }
		else if (ch == 10) { return selectOption; }

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

stringstream Dialog_Input(char* title) {
	clear();
	echo();
	setColor(2);
	box(stdscr, 15, 15);
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title) / 2, title);
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
	return stringstream(input);
	// !���������е����ˡ���
	// return input;
}
void Dialog_Info(string title, vector<string> info) {
	clear();
	setColor(2);
	box(stdscr, 15, 15);
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
	setColor();
	for (auto i = 0; i < info.size(); i++)
	{
		mvprintw(WIN_HEIGHT / 2 + i, 10, info[i].c_str());
	}
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "�����������");
	refresh();
	getch();
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
	// 	// ~~������С������ˡ���
	// 	// !ܳ�����WIN_WIDTH̫���˵���ˢ�������ˡ����㻹��Ϊ��vsc������cmd�Ͳ��С�������
	// 	// mvprintw(WIN_HEIGHT / 2 - 1, WIN_WIDTH / 2, "E");
	// 	// mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2, "END");
	// 	const char program_title[] = " ��ӭʹ�ñ����! ";
	// 	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(program_title) / 2, program_title);
	// 	setColor(3);
	// 	mvprintw(WIN_HEIGHT / 2, 6, " ʹ�����·����ѡ��һ��ģʽ: ");
	// 	if (selectOption == 0)setColor(4);
	// 	else setColor();
	// 	mvprintw(WIN_HEIGHT / 2 + 1, 10, " 1. һԪϡ�����ʽ ");
	// 	if (selectOption == 1)setColor(4);
	// 	else setColor();
	// 	mvprintw(WIN_HEIGHT / 2 + 2, 10, " 2. �㷨���ʽ��ֵ ");
	// 	char ch = getch();
	// 	if (ch == 2 || ch == 3)selectOption = selectOption == 0 ? 1 : 0;
	// 	// !KEY_UP��KEY_DOWN���񲻶ԡ���
	// 	else if (ch == 10) { return selectOption; }


	// 	// mvprintw(WIN_HEIGHT / 2 + 3, 10, "Mode:	");
	// 	// move(WIN_HEIGHT /2 + 3, 10)
	// 	// mvprintw(0, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	// 	// mvprintw(1, 0, "#       Welcome to the Calculator!               #");
	// 	// mvprintw(2, 0, "#  Please select a mode:                         #");
	// 	// mvprintw(3, 0, "#  1. һԪϡ�����ʽ                             #");
	// 	// mvprintw(4, 0, "#  2. �㷨���ʽ��ֵ                             #");
	// 	// mvprintw(5, 0, "#                                                 #");
	// 	// mvprintw(6, 0, "#  ��ǰҳ��Ϊ�����н��棬��C++���Ա�д��Ϊ�˸��õ����飬 #");
	// 	// mvprintw(7, 0, "#  �����Դ���Ŀ�е�Calculator_GUI.exe�ļ���ʹ��ͼ�λ�  #");
	// 	// mvprintw(8, 0, "#  ������в�����                               #");
	// 	// mvprintw(9, 0, "#  ��Ŀ��ȫ����������Դ�뷢������Github�ϣ�ϣ�����Եõ�����#");
	// 	// mvprintw(10, 0, "#  star                                          #");
	// 	// mvprintw(11, 0, "#                       2024-09-28             #");
	// 	// mvprintw(12, 0, "#                Copyright @ 2024 Woisol-G     #");
	// 	// mvprintw(13, 0, "#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##");
	// 	refresh();             // ˢ����Ļ����ʾ����

	// }

	return Win_Select("��ӭʹ�ñ����!", " ʹ�����·����ѡ��һ��ģʽ: ", { "һԪϡ�����ʽ ", "�㷨���ʽ��ֵ" });
	// !����ֱ��������js�������ʽ��ʽת����vector��wok���·�����
}

void Page_Multinomial() {
	bool back = false;
	while (!back)
	{
		// const string description = ();
		vector<string> options;
		if (Multinomial::initNum == 2) options = { "�鿴����ʽa,b","�������ʽa+b", "�������ʽa-b", "�˳�" };
		else options = { "�������ʽ" };
		switch (Win_Select(" һԪϡ�����ʽ ", Multinomial::initNum == 0 ? " ���ڻ�û���������ʽ����ѡ������ " : "��ǰ������" + to_string(Multinomial::initNum) + "������ʽ�����ֻ������2������ѡ�����: ", options))
		{
		case 0:
			if (Multinomial::initNum == 2)
				Dialog_Info("a,b����ʽ���£�", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
			else
				multinomials[Multinomial::initNum].init(Dialog_Input("���������ʽ����n����ϵ��ָ��: "));
			break;
		case 1:
			if (Multinomial::initNum == 2)
			{
				res = multinomials[0] + multinomials[1];
				Dialog_Info("a + b = ", { res.print() });
			}
			break;
		case 2:
			if (Multinomial::initNum == 2)
			{
				res = multinomials[0] - multinomials[1];
				Dialog_Info("a - b = ", { res.print() });
			}
			break;
		case 3:
			back = true;
		}
	}
}

void Page_Expression(const std::string& tilte) {
	clear();
	setColor(2);
	box(stdscr, 15, 15);
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(tilte.c_str()) / 2, tilte.c_str());
	mvprintw(WIN_HEIGHT / 2, 10, "  �����룺");
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
