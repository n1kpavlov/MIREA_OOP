#include "Obj_3.h"

Obj_3::Obj_3(string name, int number): Obj_2(name, number)
{
	this->name = name + "_3";
	this->number = pow(number, 3);
}

void Obj_3::output()
{
	cout << this->name << " " << this->number << endl;
}
