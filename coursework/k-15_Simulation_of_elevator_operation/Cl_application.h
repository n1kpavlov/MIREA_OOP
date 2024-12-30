#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "Cl_base.h"

class Cl_application: public Cl_base//наследование класса
{
public:
	Cl_application(Cl_base* p_head_object, string = "Base_object");//параметризированный конструктор
	void build_tree_objects();//метод построения дерева
	int exec_app();//метод запуска системы
	void handler_add_floor(string);//Метод обработчика сигнала добавления этажа
	void handler_turn_off(string);//Метод обработчика сигнала завершения работы
	void handler_syscon(string);//Метод обработчика сигнала вывода состояния системы
	void handler_show_tree(string);//Метод обработчика сигнала вывода иерархии объектов
	void signal_input(string&);//Метод сигнала ввода
	void signal_output(string&);//Метод сигнала вывода
	void signal_upd(string&);//Метод сигнала обновления состояния системы

private:
	bool run;//флаг на выполнение программы
	int tik;//номер такта
};

#endif
