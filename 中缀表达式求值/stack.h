#pragma once
#ifndef		STACK_H
#define		STACK_H
#define		ERROR		"错误"

#include <vector>
#include <string>

using std::vector;
;
typedef std::string syDataType;

typedef struct node
{
	syDataType data;		// 数据
	struct node *next;	// 下一节点
} Node;

typedef struct
{
	Node *head;			// 用不带头结点的线性表来实现栈
	int elemNumber;		// 栈中元素的个数
}Stack;

inline void initStack(Stack &stack)
{
	stack.head = nullptr;
	stack.elemNumber = 0;
}

inline void StackPush(Stack &stack, const syDataType data)
{
	Node *p = new Node;
	p->next = nullptr;
	p->data = data;

	stack.elemNumber++;
	p->next = stack.head;
	stack.head = p;
}

inline syDataType StackPop(Stack &stack)
{
	if (stack.elemNumber <= 0)
		return ERROR;
	stack.elemNumber--;
	syDataType temp = stack.head->data;
	Node *p = stack.head;
	stack.head = p->next;

	delete p;
	return temp;
}

inline syDataType StackGetTop(const Stack stack)
{
	return stack.head->data;
}

// 得到从栈顶到栈底的一个顺序序列放入vec中
inline void StackForEach(vector<syDataType> &vec, const Stack stack)
{
	Node *ptr = stack.head;
	while (ptr != nullptr)
	{
		vec.push_back(ptr->data);
		ptr = ptr->next;
	}
}

inline bool StackEmpty(Stack stack)
{
	if (stack.elemNumber == 0)
		return true;
	return false;
}
#endif // ! STACK_H
