#ifndef __OBJ_4__H
#define __OBJ_4__H
#include <iostream>
#include <string>
#include <cmath>
#include "Obj_3.h"

using namespace std;

class Obj_4: private Obj_3
{
private:
	string name;
	int number;
public:
	Obj_4(string name, int number);
	void output();
};


#endif
