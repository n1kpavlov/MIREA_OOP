#include "Class_7.h"

Class_7::Class_7(string s): Class_1(s + "_7"), Class_4(s + "_7"), Class_5(s +
	"_7")
{
	name = s + "_7";
}

string Class_7::get()
{
	return name;
}
