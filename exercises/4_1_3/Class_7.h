#ifndef __CLASS_7__H
#define __CLASS_7__H
#include <iostream>
#include <string>
#include "Class_4.h"
#include "Class_5.h"

using namespace std;

class Class_7: public Class_4, public Class_5
{
private:
	string name;
public:
	Class_7(string s);
	string get();
};


#endif
