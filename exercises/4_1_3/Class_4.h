#ifndef __CLASS_4__H
#define __CLASS_4__H
#include <iostream>
#include <string>
#include "Class_1.h"

using namespace std;

class Class_4: virtual public Class_1
{
private:
	string name;
public:
	Class_4(string s);
	string get();
};


#endif
