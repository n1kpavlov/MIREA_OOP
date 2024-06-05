#include "Class_6.h"

Class_6::Class_6(string s): Class_2(s + "_6"), Class_3(s + "_6")
{
	name = s + "_6";
}

string Class_6::get()
{
	return name;
}
