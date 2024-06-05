#ifndef __CLASS_3__H
#define __CLASS_3__H
#include <iostream>
#include <string>
#include "Class_1.h"

using namespace std;

class Class_3: public Class_1
{
private:
	string name;
public:
	Class_3(string s);
	string get();
};


#endif
