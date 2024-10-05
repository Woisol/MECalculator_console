#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include "../../lib/include/curses.h"
using namespace std;
#define WIN_WIDTH 58
#define WIN_HEIGHT 28
bool COLOR_SUPPORT = false;
bool cmdMode = false;
void initColor() {
	if (COLOR_SUPPORT = has_colors())
	{
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);		// °×µ×ºÚ×Ö
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// @ºÚµ×»Æ×Ö
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// »Æµ×ºÚ×Ö
		init_pair(4, COLOR_BLACK, COLOR_WHITE);		// ##ºÚµ×°××Ö
		init_pair(5, COLOR_RED, COLOR_WHITE);		// £¡ºìµ×°××Ö
		init_pair(6, COLOR_WHITE, COLOR_RED);		// £¡°×µ×ºì×Ö

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
		box(stdscr, 15, 15);
		setColor(2);
		mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
		setColor(3);
		mvprintw(WIN_HEIGHT / 2, 10, description.c_str());

		const char* COPYRIGHT = "Copyright @ 2024 Woisol-G";
		mvprintw(WIN_HEIGHT - 1, WIN_WIDTH - strlen(COPYRIGHT) - 1, COPYRIGHT);

		for (auto i = 0; i < optionsSize; i++)
		{
			SelectOption(options[i], i);
		}

		ch = getch();
		if (ch == 2)selectOption = (selectOption + 1) % optionsSize;
		else if (ch == 3)selectOption = (selectOption - 1 > -1 ? selectOption - 1 : optionsSize - 1) % optionsSize;
		else if (ch > 48 && ch <= 48 + optionsSize) { return ch - 49; }
		else if (ch == 10 || ch == ' ') { return selectOption; }
		refresh();
	}
}
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
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "°´ÈÎÒâ¼ü·µ»Ø");
	refresh();
	if (!cmdMode)
		getch();
}
void Dialog_Error(string title, string error) {
	if (cmdMode)
	{
		cout << "err: " << error << endl;
		return;
	}
	clear();
	setColor(6);
	box(stdscr, 15, 15);
	title = " " + title + " ";
	mvprintw(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - strlen(title.c_str()) / 2, title.c_str());
	setColor(5);
	mvprintw(WIN_HEIGHT / 2, WIN_WIDTH / 2 - strlen(error.c_str()) / 2, error.c_str());
	mvprintw(WIN_HEIGHT - 2, WIN_WIDTH / 2 - 6, "°´ÈÎÒâ¼ü·µ»Ø");
	refresh();
	if (!cmdMode)
		getch();
}

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
	// !wokÎÒËµ¡­¡­Íü¼ÇrefreshÁË¡­¡­
	char input[100];
	getnstr(input, 100);
	stringstream checkStream = stringstream(input);
	return input;
}
