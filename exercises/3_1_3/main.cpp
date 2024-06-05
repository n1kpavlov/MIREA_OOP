#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

void func(Test ob_local)
{
	cout << ob_local.metod2() << endl;
}

int main()
{
	int x;
	cin >> x;
	if (x > 2 && x % 2 == 0)
	{
		cout << x << endl;
		Test obj(x);
		obj.input();
		func(obj);
		cout << obj.metod1() << endl;
	}
	else
	{
		cout << x << "?";
		exit(0);
	}
}
