#include "Obj_1.h"

Obj_1::Obj_1(string name, int number)
{
	this->name = name + "_1";
	this->number = pow(number, 1);
}

void Obj_1::output()
{
	cout << this->name << " " << this->number << endl;
}
