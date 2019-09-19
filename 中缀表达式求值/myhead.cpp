#include "myhead.h"
#include <cmath>
#include <map>
#include <iostream>
using std::map;
using std::to_string;	// C++11
using std::stod;
/************************* 运算符优先级 *******************************
priority[0] 为op栈内元素优先级；
priority[1] 为待处理字符ch的优先级；

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
	Stack op;		// 字符栈
	Stack postexp;	// 后续栈

	// 初始化栈
	initStack(op);
	initStack(postexp);
	PostString(input, op, postexp);

	// 反转postexp
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
	// 首先等于号进栈
	StackPush(op, "=");
	int i = 0;
	for (int i = 0; i < input.length();)
	{
		if (input[i] >= '0' && input[i] <= '9')		// 数字进栈
		{
			string temp;
			temp.erase(temp.begin(), temp.end());	// 清空temp;
			for (; input[i] >= '0' && input[i] <= '9' || input[i] == '.'; i++)
				temp += input[i];
			StackPush(postexp, temp);				// 进栈
		}
		else if (input[i] != ' ')
		{
			string temp;
			temp.push_back(input[i]);
			if (_GetPriority(StackGetTop(op), 0) > _GetPriority(temp, 1))
			{
				StackPush(postexp, StackPop(op));	// 栈顶的优先级大于待处理字符，栈顶出栈进入postexp
			}
			else if (_GetPriority(StackGetTop(op), 0) == _GetPriority(temp, 1))
			{
				StackPop(op);						// 只有“（”与“）”会出现这种情况
				i++;
			}
			else
			{
				StackPush(op, temp);				// temp优先级高，则temp进栈
				i++;
			}
			temp.erase(temp.begin(), temp.end());	// 清除temp里的内容
		}
		else
		{
			i++;			// 忽略空格
		}
	}
	for (; !StackEmpty(op);)	// op不空全部进postexp
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
	Stack numStack;				// 运算数栈
	initStack(numStack);

	string temp;
	for (; !StackEmpty(postexp);)
	{
		temp = StackPop(postexp);		// 取栈顶元素
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
				std::cout << "除零错误！！！" << std::endl;
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

