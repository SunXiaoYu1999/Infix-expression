#include "myhead.h"
#include <cmath>
#include <map>
#include <iostream>
using std::map;
using std::to_string;	// C++11
using std::stod;
/************************* ��������ȼ� *******************************
priority[0] Ϊopջ��Ԫ�����ȼ���
priority[1] Ϊ�������ַ�ch�����ȼ���

			=	(	+	-	*	/	)
lpri(ch)	0	1	3	3	5	5	6
rpri(ch)	0	6	2	2	4	4	1
***********************************************************************/
int priority[2][7] =
{
	0, 1, 3, 3, 5, 5, 6,
	0, 6, 2, 2, 4, 4, 1
};
map<string, int> M = {
	{"=",0},
	{"(",1},
	{"+",2},
	{"-",3},
	{"*",4},
	{"/",5},
	{")",6},
};

double TheValueOf(const string input)
{
	Stack op;		// �ַ�ջ
	Stack postexp;	// ����ջ

	// ��ʼ��ջ
	initStack(op);
	initStack(postexp);
	PostString(input, op, postexp);

	// ��תpostexp
	Stack temp;
	initStack(temp);
	for (; !StackEmpty(postexp);)
	{
		StackPush(temp, StackPop(postexp));
	}
	return ValueOfPost(temp);
}

void PostString(const string input, Stack & op, Stack & postexp)
{
	// ���ȵ��ںŽ�ջ
	StackPush(op, "=");
	int i = 0;
	for (int i = 0; i < input.length();)
	{
		if (input[i] >= '0' && input[i] <= '9')		// ���ֽ�ջ
		{
			string temp;
			temp.erase(temp.begin(), temp.end());	// ���temp;
			for (; input[i] >= '0' && input[i] <= '9' || input[i] == '.'; i++)
				temp += input[i];
			StackPush(postexp, temp);				// ��ջ
		}
		else if (input[i] != ' ')
		{
			string temp;
			temp.push_back(input[i]);
			if (_GetPriority(StackGetTop(op), 0) > _GetPriority(temp, 1))
			{
				StackPush(postexp, StackPop(op));	// ջ�������ȼ����ڴ������ַ���ջ����ջ����postexp
			}
			else if (_GetPriority(StackGetTop(op), 0) == _GetPriority(temp, 1))
			{
				StackPop(op);						// ֻ�С������롰����������������
				i++;
			}
			else
			{
				StackPush(op, temp);				// temp���ȼ��ߣ���temp��ջ
				i++;
			}
			temp.erase(temp.begin(), temp.end());	// ���temp�������
		}
		else
		{
			i++;			// ���Կո�
		}
	}
	for (; !StackEmpty(op);)	// op����ȫ����postexp
	{
		StackPush(postexp, StackPop(op));
	}
}

int _GetPriority(string a, int flag)
{
	if (flag >= 0 && flag <= 1)
	{
		return priority[flag][M.find(a)->second];
	}
	return -1;
}

double ValueOfPost(Stack &postexp)
{
	Stack numStack;				// ������ջ
	initStack(numStack);

	string temp;
	for (; !StackEmpty(postexp);)
	{
		temp = StackPop(postexp);		// ȡջ��Ԫ��
		double A, B;
		switch (temp[0])
		{
		case '+':
			A = _StringToDouble(StackPop(numStack));
			B = _StringToDouble(StackPop(numStack));
			StackPush(numStack, to_string(A + B));
			break;
		case '-':
			A = _StringToDouble(StackPop(numStack));
			B = _StringToDouble(StackPop(numStack));
			StackPush(numStack, to_string(B - A));
			break;
		case '*':
			A = _StringToDouble(StackPop(numStack));
			B = _StringToDouble(StackPop(numStack));
			StackPush(numStack, to_string(A * B));
			break;
		case '/':
			A = _StringToDouble(StackPop(numStack));
			B = _StringToDouble(StackPop(numStack));
			if (A - 0.0 >= 1e-6 || A - 0.0 <= 1e-6)
			{
				StackPush(numStack, to_string(B / A));
			}
			else
			{
				std::cout << "������󣡣���" << std::endl;
				exit(0);
			}
			break;
		case '=':
			return _StringToDouble(StackPop(numStack));
			break;
		default:
			StackPush(numStack, temp);
			break;
		}
	}
	return _StringToDouble(StackPop(numStack));
}

double _StringToDouble(string str)
{
	long long int left = 0;
	long long int right = 0;
	int len = 0;
	size_t i = 0;
	for (; str[i] != '.' && i < str.length(); i++)
	{
		left = left * 10 + str[i] - '0';
	}
	for (i++; i < str.length(); i++)
	{
		right = right * 10 + str[i] - '0';
		len++;
	}
	double temp = (double)left + (double)right / pow(10, len);

	return temp;
}

