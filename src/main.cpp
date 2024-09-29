// td 添加test
// td 分成.h而不是全部用cpp
#include <iostream>
#include"TUI.h"
#include"multinomial.h"
#include"expression.h"
using namespace std;
int main(int argc, char* argv[]) {
	// ~~为什么默认是1啊……
	// !噢噢argc代表参数数量……
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
		endwin();              // 结束ncurses模式
	}
	else if (argc > 1 && strcmp(argv[1], "--cmd") == 0)
		// ！！！！！！woc……strcmp……艹而且是 == 0……
	{
		// cout << "cmd mode" << endl;
		// for (int i = 0;i < argc;i++)
		// {
		// 	cout << argv[i] << " ";
		// }
		// cout << endl;
		string input, input2;
		bool isNext = false;
		int x;
		if (strcmp(argv[2], "--help") == 0)
		{
			cout << "--cmd [mode=1(Multinomial)|2(Expression)] [...option] [...input]" << endl << \
				"mode=1:	[option=1(calculate)|2(derivative)|3(add)|4(sub)|5(mul)] [x?] [input1] [-?] [input2?]" << endl << \
				"mode=2:	[input]" << endl;
			return 0;
		}
		switch (*argv[2])
		{
			// !额写成''了就char const too long for its type……
		case '1':
			switch (*argv[3])
			{
			case '1':
				// **main.exe --cmd 1 1 x 1 1 1
				x = stoi(argv[4]);
				for (int i = 5;i < argc;i++)
				{
					input += argv[i];input += " ";
				}
				multinomials[0].init(input);
				cout << multinomials[0].calculate(x) << endl;
				break;
			case '2':
				// **main.exe --cmd 1 2 1 1 1
				for (int i = 4;i < argc;i++)
				{
					input += argv[i];input += " ";
				}
				multinomials[0].init(input);
				res = multinomials[0].derivative();
				cout << res.print() << endl;
				break;
			case '3':
				// **main.exe --cmd 1 3 1 1 1 ; 1 1 2
				for (int i = 4;i < argc;i++)
				{
					if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
					if (isNext) { input2 += argv[i];input2 += " "; }
					else { input += argv[i];input += " "; }
				}
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] + (multinomials[1]);
				cout << res.print() << endl;
				break;
			case '4':
				// **main.exe --cmd 1 4 1 1 1 ; 1 1 2
				isNext = false;
				for (int i = 4;i < argc;i++)
				{
					if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
					if (isNext) { input2 += argv[i];input2 += " "; }
					else { input += argv[i];input += " "; }
				}
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] - (multinomials[1]);
				cout << res.print() << endl;
				break;
			case '5':
				// **main.exe --cmd 1 5 1 1 1 ; 1 1 2
				isNext = false;
				for (int i = 4;i < argc;i++)
				{
					if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
					if (isNext) { input2 += argv[i];input2 += " "; }
					else { input += argv[i];input += " "; }
				}
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] * (multinomials[1]);
				cout << res.print() << endl;
				break;
			default:
				cout << "Unknown Mode" << endl;
				break;
			}
			break;
		case '2':
			// **main.exe --cmd 2 90-(5-4)*2-2^3
			// input = to_string(argv[3]);
			input = argv[3];
			// !az完全可以直接赋值……不然to_string其实不能把char[]转过去的……
			expression.init(input);
			cout << expression.calculate() << endl;
			break;
		default:
			cout << "Unknown command" << endl;
		}
		// system("pause");
	}
	// cout << "argc: " << argc << endl;
	// for (int i = 0;i < argc;i++)
	// {
	// 	cout << i << " " << argv[i] << endl;
	// }
	// // cout << endl;
	return 0;
}

