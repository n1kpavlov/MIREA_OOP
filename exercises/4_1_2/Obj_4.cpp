#include "Obj_4.h"

Obj_4::Obj_4(string name, int number): Obj_3(name, number)
{
	this->name = name + "_4";
	this->number = pow(number, 4);
}

void Obj_4::output()
{
	cout << this->name << " " << this->number << endl;
}
