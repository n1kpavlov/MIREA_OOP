#ifndef __CLASS_2__H
#define __CLASS_2__H
#include <iostream>
#include <string>
#include "Class_1.h"

using namespace std;

class Class_2: public Class_1
{
private:
	string name;
public:
	Class_2(string s);
	string get();
};


#endif
