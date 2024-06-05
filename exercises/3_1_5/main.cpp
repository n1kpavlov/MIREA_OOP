#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

Test* func(int x)
{
	Test *local = new Test(x);
	local->new_mass();
	local->input();
	local->metod2();
	return local;
}

int main()
{
	int x;
	cin >> x;
	if (x > 2 && x % 2 == 0)
	{
		cout << x << endl;
		Test * obj1;
		obj1 = func(x);
		obj1->metod1();
		Test *obj2 = new Test(*obj1);
		obj2->metod2();
		obj1->output();
		cout << obj1->sum() << endl;
		obj2->output();
		cout << obj2->sum() << endl;
		int *arr = obj2->get_mass();
		*obj2 = *obj1;
		obj2->put_mass(arr);
		obj1->metod1();
		obj2->output();
		cout << obj2->sum() << endl;
		delete obj1;
		delete obj2;
	}
	else
	{
		cout << x << "?";
		exit(0);
	}
}
