#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

int main()
{
	int x1, x2;
	cin >> x1;
	cin >> x2;
	if (x1 > 4 && x2 > 4)
	{
		Test obj1(x1), obj2(x2);
		obj1 = obj2;
		for (int i = 0; i < x1; i++)
		{
			obj1.mass[i] = x1;
		}

		obj1.output();
		cout << endl;
		for (int i = 0; i < x2; i++)
		{
			obj2.mass[i] = x2;
		}

		obj2.output();
	}
	else if (x1 <= 4)
	{
		cout << x1 << "?";
	}
	else
	{
		cout << x2 << "?";
	}
}
