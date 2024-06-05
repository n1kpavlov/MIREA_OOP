#include "Obj_2.h"

Obj_2::Obj_2(string name, int number): Obj_1(name, number)
{
	this->name = name + "_2";
	this->number = pow(number, 2);
}

void Obj_2::output()
{
	cout << this->name << " " << this->number << endl;
}
