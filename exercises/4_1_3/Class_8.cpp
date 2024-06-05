#include "Class_8.h"

Class_8::Class_8(string s): Class_1(s + "_8"), Class_6(s + "_8"), Class_7(s + "_8")
{
	name = s + "_8";
}

string Class_8::get()
{
	return name;
}
