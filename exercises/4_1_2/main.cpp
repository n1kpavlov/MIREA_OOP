#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Obj_4.h"

using namespace std;

int main()
{
	string name;
	int number;
	cin >> name >> number;
	if (number >= 2 && number <= 10)
	{
		Obj_4 *obj = new Obj_4(name, number);
		((Obj_1*) obj)->output();
		((Obj_2*) obj)->output();
		((Obj_3*) obj)->output();
		obj->output();
	}
	else
	{
		exit(0);
	}
}
