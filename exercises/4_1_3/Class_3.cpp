#include "Class_3.h"

Class_3::Class_3(string s): Class_1(s + "_3")
{
	name = s + "_3";
}

string Class_3::get()
{
	return name;
}
