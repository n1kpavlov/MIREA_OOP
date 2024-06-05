#ifndef __CLASS_5__H
#define __CLASS_5__H
#include <iostream>
#include <string>
#include "Class_1.h"

using namespace std;

class Class_5: virtual public Class_1
{
private:
	string name;
public:
	Class_5(string s);
	string get();
};


#endif
