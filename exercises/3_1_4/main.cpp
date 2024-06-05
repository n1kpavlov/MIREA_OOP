#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

Test func(int x)
{
	Test local(x);
	return local;
}

int main()
{
	int x;
	cin >> x;
	if (x > 2 && x % 2 == 0)
	{
		cout << x << endl;
		Test obj1;
		obj1 = func(x);
		obj1.new_mass();
		obj1.input();
		obj1.metod2();
		Test obj2 = obj1;
		obj2.metod1();
		obj1.output();
		cout << obj1.sum() << endl;
		obj2.output();
		cout << obj2.sum() << endl;
	}
	else
	{
		cout << x << "?";
		exit(0);
	}
}
