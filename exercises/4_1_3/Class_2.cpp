#include "Class_2.h"

Class_2::Class_2(string s): Class_1(s + "_2")
{
	name = s + "_2";
}

string Class_2::get()
{
	return name;
}
