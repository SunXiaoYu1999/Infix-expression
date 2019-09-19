#ifndef MYHEAD_H
#define MYHEAD_H

#include "stack.h"

using std::string;


double TheValueOf(const string input);

void PostString(const string input, Stack &op, Stack &postexp);
int _GetPriority(string a, int flag);

double ValueOfPost(Stack &postexp);
double _StringToDouble(string str);



#endif // !MYHEAD_H