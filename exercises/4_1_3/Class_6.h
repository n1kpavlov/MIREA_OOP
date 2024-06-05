#ifndef __CLASS_6__H
#define __CLASS_6__H
#include <iostream>
#include <string>
#include "Class_2.h"
#include "Class_3.h"

using namespace std;

class Class_6: public Class_2, public Class_3
{
private:
	string name;
public:
	Class_6(string s);
	string get();
};


#endif
