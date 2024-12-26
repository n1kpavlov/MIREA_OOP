#ifndef __CL_CHILD_5__H
#define __CL_CHILD_5__H
#include "Cl_base.h"

class Cl_child_5 : public Cl_base//наследование класса
{
public:
	Cl_child_5(Cl_base*, string);//параметризированный конструктор

	void get_signal(string&);//метод сигнала
	void get_handler(string);//метод обработчика
};

#endif
