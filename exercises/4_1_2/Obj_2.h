#ifndef __OBJ_2__H
#define __OBJ_2__H
#include <iostream>
#include <string>
#include <cmath>
#include "Obj_1.h"

using namespace std;

class Obj_2: private Obj_1
{
private:
  string name;
	int number;
public:
  Obj_2(string name, int number);
	void output();
};


#endif
