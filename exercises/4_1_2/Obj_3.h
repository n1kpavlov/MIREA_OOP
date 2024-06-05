#ifndef __OBJ_3__H
#define __OBJ_3__H
#include <iostream>
#include <string>
#include <cmath>
#include "Obj_2.h"

using namespace std;

class Obj_3: private Obj_2
{
private:
  string name;
  int number;
public:
  Obj_3(string name, int number);
  void output();
};


#endif
