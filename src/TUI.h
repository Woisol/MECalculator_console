#pragma once

#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include "../lib/include/curses.h"
#include "./Components/TUI_Win.h"
#include "multinomial.h"
#include"expression.h"
using namespace std;

// bool multinomialInputCheck(stringstream& sstream) {
// 	int n, count;
// 	int input;
// 	sstream >> n;
// 	while (sstream >> input)
// 	{
// 		count++;
// 	}
// 	return count == 2 * n;
// }
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

	return Win_Select("��ӭʹ�ñ����!", "���������Ӧ�����ּ�ѡ��ģʽ:", { "һԪϡ�����ʽ ", "�㷨���ʽ��ֵ","���ڴ��������","�˳�" });
	// !����ֱ��������js�������ʽ��ʽת����vector��wok���·�����
}

int Page_Multinomial() {
	// bool back = false;
	// while (!back)
	while (true)
	{
		// const string description = ();
		// vector<string> options;
		// if (Multinomial::initNum == 2) options = { "�鿴����ʽa,b","�������ʽa+b", "�������ʽa-b","��������", "������һ��", "�˳�" };
		// else options = { "�������ʽ" };
		switch (Multinomial::initNum)
		{
		case 0:
			switch (Win_Select(" һԪϡ�����ʽ ", "���ڻ�û���������ʽ����ѡ������", { "�������ʽ","������һ��","�˳�" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("���������ʽ����n����ϵ��ָ��: "));
				// multinomials[Multinomial::initNum].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: ", multinomialInputCheck));
				// !������ǰԤ���������ᵼ����ֵ��İ�����
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			default:
				break;
			}
			break;
			// !��������break�ˡ����������뿴����������һ��Ч������İ�bug�ˡ���
		case 1:
			switch (Win_Select(" һԪϡ�����ʽ ", "��ǰ������1������ʽ����ѡ��", { "����ڶ�������ʽ","�鿴��һ������ʽ","��ֵ","��","���������һ������ʽ","������һ��","�˳�" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: "));
				break;
			case 1:
				Dialog_Info("��һ������ʽ���£�", { multinomials[0].print() });
				break;
			case 2:
				double x;
				// Dialog_Input("����x = ��") >> x;
				x = atof(Dialog_Input("������x = ��").c_str());
				Dialog_Info(" x = " + better_double_to_string(x) + "ʱ��" + multinomials[0].print() + " =", { better_double_to_string(multinomials[0].calculate(x)) });
				break;
			case 3:
				Dialog_Info(multinomials[0].print() + "�ĵ���Ϊ��", { multinomials[0].derivative().print() });
				break;
			case 4:
				Multinomial::initNum = 0;
				multinomials[0].init(Dialog_Input("�����������һ������ʽ����n����ϵ��ָ��: "));
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
			break;
		case 2:
			switch (Win_Select(" һԪϡ�����ʽ ", "��ǰ������2������ʽ����ѡ��", { "�鿴����ʽa,b","�������ʽa+b", "�������ʽa-b","�������ʽa*b","��������","������һ��","�˳�" }))
			{
			case 0:
				Dialog_Info("a,b����ʽ���£�", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
				break;
			case 1:
				res = multinomials[0] + multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " + (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 2:
				res = multinomials[0] - multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " - (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 3:
				res = multinomials[0] * multinomials[1];
				Dialog_Info("(" + multinomials[0].print() + ")" + " * (" + multinomials[1].print() + ") =", { res.print() });
				break;
			case 4:
				switch (Win_Select("��������", "��Ҫ����������Щ����ʽ��", { "��һ������ʽ", "�ڶ�������ʽ","С���Ӳ���ѡ��()","�������ˣ��Ҳ�����" }))
					// !ܳ��ôͻȻ�Ϳɰ����ˡ���
				{
				case 0:
					Multinomial::initNum = 1;
					multinomials[0].init(Dialog_Input("�������һ������ʽ����n����ϵ��ָ��: "));
					break;
				case 1:
					Multinomial::initNum = 1;
					multinomials[1].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: "));
					break;
				case 2:
					Multinomial::initNum = 0;
					multinomials[0].init(Dialog_Input("�������һ������ʽ����n����ϵ��ָ��: "));
					multinomials[1].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: "));
					break;
				default:
					break;
					// Dialog_Error("Error", "Unknown Error");
				}
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
			// switch (Win_Select(" һԪϡ�����ʽ ", Multinomial::initNum == 0 ? "���ڻ�û���������ʽ����ѡ������" : "��ǰ������" + to_string(Multinomial::initNum) + "������ʽ�����ֻ������2������ѡ�����:", options))
			// {
			// case 0:
			// 	if (Multinomial::initNum == 2)
			// 		Dialog_Info("a,b����ʽ���£�", { "a = " + multinomials[0].print(),"b = " + multinomials[1].print() });
			// 	else
			// 	{
			// 	}
			// 	break;
			// case 1:
			// 	if (Multinomial::initNum == 2)
			// 	{
			// 		res = multinomials[0] + multinomials[1];
			// 		Dialog_Info(multinomials[0].print() + " + " + multinomials[1].print() + " =", { res.print() });
			// 	}
			// 	break;
			// case 2:
			// 	if (Multinomial::initNum == 2)
			// 	{
			// 		res = multinomials[0] - multinomials[1];
			// 		Dialog_Info(multinomials[0].print() + " - " + multinomials[1].print() + " =", { res.print() });
			// 	}
			// 	break;
			// case 3:

			// 	switch (Win_Select("��������", "��Ҫ����������Щ����ʽ��", { "��һ������ʽ", "�ڶ�������ʽ","С���Ӳ���ѡ��()","�������ˣ��Ҳ�����" }))
			// 		// !ܳ��ôͻȻ�Ϳɰ����ˡ���
			// 	{
			// 	case 0:
			// 		Multinomial::initNum = 1;
			// 		multinomials[0].init(Dialog_Input("�������һ������ʽ����n����ϵ��ָ��: ", multinomialInputCheck));
			// 		break;
			// 	case 1:
			// 		Multinomial::initNum = 1;
			// 		multinomials[1].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: ", multinomialInputCheck));
			// 		break;
			// 	case 2:
			// 		Multinomial::initNum = 0;
			// 		multinomials[0].init(Dialog_Input("�������һ������ʽ����n����ϵ��ָ��: ", multinomialInputCheck));
			// 		multinomials[1].init(Dialog_Input("������ڶ�������ʽ����n����ϵ��ָ��: ", multinomialInputCheck));
			// 		break;
			// 	default:
			// 		break;
			// 		// Dialog_Error("Error", "Unknown Error");
			// 	}
			// 	break;
			// case 4:
			// 	// back = true;
			// 	return 0;
			// case 5:
			// 	return 1;
			// }
		}
	}
}

int Page_Expression() {
	while (true)
	{
		if (expression.empty())
		{
			int calRes;
			switch (Win_Select("�㷨���ʽ��ֵ������", "��ǰδ������ʽ����ѡ�����룺", { "������ʽ������", "������һ��", "�˳�" }))
			{
			case 0:
				expression.init(Dialog_Input("�������㷨���ʽ��ע�����ֺͷ���֮�䲻���пո�"));
				// !��[&]���&�Ͳ��������ˡ���
				calRes = expression.calculate();
				// !�������������switch��������������Ȼ����jump to case label���������ʲô��˭����ô�ġ�����
				if (expression.getExpression().empty())continue;
				Dialog_Info(expression.getExpression() + " = ", { to_string(calRes) });
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			}
		}
		else
			switch (Win_Select("�㷨���ʽ��ֵ������", "���ʽ�����룬��ѡ�������", { "�ٴ���ֵ",  "��������", "������һ��", "�˳�" }))
			{
			case 0:
				Dialog_Info(expression.getExpression() + " = ", { to_string(expression.calculate()) });
				break;
			case 1:
				expression.init(Dialog_Input("�����������㷨���ʽ���������κ����ݰ��»س�ȡ����"));
				if (!expression.getExpression().empty())
					Dialog_Info(expression.getExpression() + " = ", { to_string(expression.calculate()) });
				break;
			case 2:
				return 0;
			case 3:
				return 1;
			}
	}
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
