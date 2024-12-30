#ifndef __OUTPUT__H
#define __OUTPUT__H
#include "Cl_base.h"

class Output : public Cl_base
{
public:
	Output(Cl_base* p_head_object);//Параметризированный конструктор
	void handler_output(string);//Метод обработчика сигнала вывода
};

#endif
