#include "myhead.h"
#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	string A = "521+(1+520*10000+666+1)+125";
	cout << (int)TheValueOf(A) << endl;

	return 0;
}