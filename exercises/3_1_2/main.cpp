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
		int *mass1 = obj1.get_mass();
		obj1 = obj2;
		obj1.change_mass(mass1);
		obj1.output();
		cout << endl;
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
