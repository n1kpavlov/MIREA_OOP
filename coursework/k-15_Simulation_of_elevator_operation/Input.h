#ifndef __INPUT__H
#define __INPUT__H
#include "Cl_base.h"

class Input : public Cl_base
{
public:
	Input(Cl_base* p_head_object);//Параметризированный конструктор
	void signal_input(string&);//Метод сигнала ввода
	void handler_input(string);//Метод обработчика сигнала ввода
};

#endif
