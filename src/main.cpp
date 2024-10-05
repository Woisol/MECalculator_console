// td 添加test
// dtd 分成.h而不是全部用cpp
// dtd 多项式求值不支持小数……
#include <iostream>
#include"TUI.h"
#include"./Components/TUI_Win.h"
#include"multinomial.h"
#include"expression.h"
using namespace std;
int main(int argc, char* argv[]) {
	if (argc == 1)
	{
		setlocale(LC_ALL, "");
		initscr();
		cbreak();
		noecho();
		keypad(stdscr, TRUE);
		initColor();
		// system("chcp 65001");

		bool back = false;
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
				system("start https://github.com/Woisol/MECalculator_console");
				break;
			case 3:
				back = true;
				break;
			default:
				clear();
				mvprintw(10, 1, "Unexpect error");
				refresh();
			}

		}
		endwin();
	}
	else if (argc > 1)
	{
		cmdMode = true;
		string input, input2;
		bool isNext = false;
		double x;
		if (strcmp(argv[1], "--help") == 0)
		{
			cout << "[-M(Multinomial)|-E(Expression)] [...option] [...input]" << endl << \
				"\t" << endl << \
				"-M:[option=--cal(calculate)|--de(derivative)|--add(add)|" << endl << \
				"\t--sub(sub)|--mul(mul)] [x?] [input1] [input2?]" << endl << \
				"-E:[input]" << endl;
			return 0;
		}
		if (strcmp(argv[1], "-M") == 0)
		{
			if (strcmp(argv[2], "--cal") == 0)
			{
				if (argc < 5)
				{
					cout << "err: 未输入足够参数，请检查是否输入了x" << endl;
					return -1;
				}
				// **main.exe -M --cal x 1 1 1
				x = atof(argv[3]);
				input = argv[4];
				multinomials[0].init(input);
				cout << multinomials[0].calculate(x) << endl;
			}
			else if (strcmp(argv[2], "--de") == 0)
			{
				// **main.exe -M --de 2 1 1 1
				input = argv[3];
				multinomials[0].init(input);
				res = multinomials[0].derivative();
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--add") == 0)
			{
				// **main.exe -M --add 3 1 1 1 ; 1 1 2
				input = argv[3];
				input2 = argv[4];
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] + (multinomials[1]);
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--sub") == 0)
			{
				// **main.exe -M --sub 4 1 1 1 ; 1 1 2
				isNext = false;
				input = argv[3];
				input2 = argv[4];
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] - (multinomials[1]);
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--mul") == 0)
			{
				// **main.exe -M --mul 5 1 1 1 ; 1 1 2
				isNext = false;
				input = argv[3];
				input2 = argv[4];
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] * (multinomials[1]);
				cout << res.print() << endl;
			}
			else
			{
				cout << "Unknown Mode" << endl;
			}
		}
		else if (strcmp(argv[1], "-E") == 0)
		{
			// **main.exe --cmd 2 90-(5-4)*2-2^3
			input = argv[2];
			expression.init(input);
			cout << expression.calculate() << endl;
		}
		else
		{
			cout << "Unknown command" << endl;
		}
		// system("pause");
	}
	return 0;
}

