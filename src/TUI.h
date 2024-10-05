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

int Multinomial::initNum = 0;
int Page_Welcome() {
	return Win_Select("��ӭʹ�ñ����!", "���������Ӧ�����ּ�ѡ��ģʽ:", { "һԪϡ�����ʽ ", "�㷨���ʽ��ֵ","��GitHub�ϲ鿴�����","�˳�" });
}

int Page_Multinomial() {
	while (true)
	{
		switch (Multinomial::initNum)
		{
		case 0:
			switch (Win_Select(" һԪϡ�����ʽ ", "���ڻ�û���������ʽ����ѡ������", { "�������ʽ","������һ��","�˳�" }))
			{
			case 0:
				multinomials[Multinomial::initNum].init(Dialog_Input("���������ʽ����n����ϵ��ָ��: "));
				break;
			case 1:
				return 0;
			case 2:
				return 1;
			default:
				break;
			}
			break;
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
				}
				break;
			case 5:
				return 0;
			case 6:
				return 1;
			}
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
				calRes = expression.calculate();
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