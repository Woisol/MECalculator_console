// td ���test
// dtd �ֳ�.h������ȫ����cpp
// dtd ����ʽ��ֵ��֧��С������
#include <iostream>
#include"TUI.h"
#include"./Components/TUI_Win.h"
#include"multinomial.h"
#include"expression.h"
using namespace std;
int main(int argc, char* argv[]) {
	// ~~ΪʲôĬ����1������
	// !����argc���������������
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
	else if (argc > 1)
		//  && strcmp(argv[1], "--cmd") == 0
		// ������������woc����strcmp����ܳ������ == 0����
	{
		cmdMode = true;
		// cout << "cmd mode" << endl;
		// for (int i = 0;i < argc;i++)
		// {
		// 	cout << argv[i] << " ";
		// }
		// cout << endl;
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
		// !��д��''�˾�char const too long for its type����
		if (strcmp(argv[1], "-M") == 0)
		{
			if (strcmp(argv[2], "--cal") == 0)
			{
				if (argc < 5)
				{
					cout << "err: δ�����㹻�����������Ƿ�������x" << endl;
					return -1;
				}
				// **main.exe --cmd 1 1 x 1 1 1
				x = atof(argv[3]);
				// for (int i = 5;i < argc;i++)
				// {
				// 	input += argv[i];input += " ";
				// }
				input = argv[4];
				multinomials[0].init(input);
				cout << multinomials[0].calculate(x) << endl;
			}
			else if (strcmp(argv[2], "--de") == 0)
			{
				// **main.exe --cmd 1 2 1 1 1
				// for (int i = 3;i < argc;i++)
				// {
				// 	input += argv[i];input += " ";
				// }
				input = argv[3];
				multinomials[0].init(input);
				res = multinomials[0].derivative();
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--add") == 0)
			{
				// **main.exe --cmd 1 3 1 1 1 ; 1 1 2
				// for (int i = 3;i < argc;i++)
				// {
				// 	if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
				// 	if (isNext) { input2 += argv[i];input2 += " "; }
				// 	else { input += argv[i];input += " "; }
				// }
				input = argv[3];
				input2 = argv[4];
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] + (multinomials[1]);
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--sub") == 0)
			{
				// **main.exe --cmd 1 4 1 1 1 ; 1 1 2
				isNext = false;
				// for (int i = 3;i < argc;i++)
				// {
				// 	if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
				// 	if (isNext) { input2 += argv[i];input2 += " "; }
				// 	else { input += argv[i];input += " "; }
				// }
				input = argv[3];
				input2 = argv[4];
				multinomials[0].init(input);
				multinomials[1].init(input2);
				res = multinomials[0] - (multinomials[1]);
				cout << res.print() << endl;
			}
			else if (strcmp(argv[2], "--mul") == 0)
			{
				// **main.exe --cmd 1 5 1 1 1 ; 1 1 2
				isNext = false;
				// for (int i = 3;i < argc;i++)
				// {
				// 	if (strcmp(argv[i], "-") == 0) { isNext = true; continue; }
				// 	if (isNext) { input2 += argv[i];input2 += " "; }
				// 	else { input += argv[i];input += " "; }
				// }
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
			// input = to_string(argv[3]);
			input = argv[2];
			// !az��ȫ����ֱ�Ӹ�ֵ������Ȼto_string��ʵ���ܰ�char[]ת��ȥ�ġ���
			expression.init(input);
			cout << expression.calculate() << endl;
		}
		else
		{
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

