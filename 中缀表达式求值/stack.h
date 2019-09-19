#pragma once
#ifndef		STACK_H
#define		STACK_H
#define		ERROR		"����"

#include <vector>
#include <string>

using std::vector;
;
typedef std::string syDataType;

typedef struct node
{
	syDataType data;		// ����
	struct node *next;	// ��һ�ڵ�
} Node;

typedef struct
{
	Node *head;			// �ò���ͷ�������Ա���ʵ��ջ
	int elemNumber;		// ջ��Ԫ�صĸ���
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

// �õ���ջ����ջ�׵�һ��˳�����з���vec��
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
