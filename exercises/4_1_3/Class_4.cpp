#include "Class_4.h"

Class_4::Class_4(string s): Class_1(s + "_4")
{
	name = s + "_4";
}

string Class_4::get()
{
	return name;
}
