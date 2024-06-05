#ifndef __CLASS_8__H
#define __CLASS_8__H
#include <iostream>
#include <string>
#include "Class_6.h"
#include "Class_7.h"

using namespace std;

class Class_8: public Class_6, public Class_7
{
private:
  string name;
public:
  Class_8(string s);
  string get();
};

#endif
