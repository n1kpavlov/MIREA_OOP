#ifndef __CL_CHILD__H
#define __CL_CHILD__H
#include "Cl_base.h"

class Cl_child : public Cl_base//наследование класса
{
public:
  Cl_child(Cl_base*, string);//параметризированный конструктор
};

#endif