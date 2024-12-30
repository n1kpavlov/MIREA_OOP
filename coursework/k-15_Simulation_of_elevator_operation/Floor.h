#ifndef __FLOOR__H
#define __FLOOR__H
#include "Cl_base.h"

const string floor_name = "object_floor_";

class Floor : public Cl_base
{
public:
	int number;//номер этажа
	Floor(Cl_base* p_head_object, int number);//Параметризированный конструктор
	void signal_button_up(string&);//Метод сигнала нажатия кнопки "вверх"
	void signal_button_down(string&);//Метод сигнала нажатия кнопки "вниз"
	void signal_output(string&);//Метод сигнала вывода
	void handler_add_passenger(string);//Метод обработчика сигнала добавления пассажира
	void handler_condition(string);//Метод обработчика сигнала вывода состояния этажа
	void handler_syscon(string);//Метод обработчика сигнала вывода состояния системы
};

#endif
