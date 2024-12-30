#ifndef __ELEVATOR__H
#define __ELEVATOR__H
#include "Cl_base.h"

const string elevator_name = "object_elevator";

class Elevator : public Cl_base
{
public:
	enum directions{up = 1, down = -1, stop = 0} dir, prev_dir;//переменные отслеживания движения лифта
	int mass, floor;//вместимость лифта и текущий этаж
	Elevator (Cl_base* p_head_object);//Параметризированный конструктор
	void signal_output(string&);//Метод сигнала вывода
	void handler_condition(string);//Метод обработчика сигнала вывода состояния лифта
	void handler_receive_mass(string);//Метод обработчика сигнала изменения вместимости лифта
	void handler_syscon(string);//Метод обработчика сигнала вывода состояния системы
	void upd();//Метод обновления состояния
};

#endif
