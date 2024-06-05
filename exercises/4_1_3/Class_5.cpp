#include "Class_5.h"

Class_5::Class_5(string s): Class_1(s + "_5")
{
	name = s + "_5";
}

string Class_5::get()
{
	return name;
}
