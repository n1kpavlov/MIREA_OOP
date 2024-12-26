#include "Cl_child_2.h"

Cl_child_2::Cl_child_2(Cl_base* p_head_object, string s_object_name):Cl_base(p_head_object, s_object_name)
{
	object_class = 2;//установка номера класса
}

void Cl_child_2::get_signal(string& message)
{
	cout << endl << "Signal from " << get_absolute_coordinate();//вывод соощения с координатой
	message += " (class: " + to_string(object_class) + ")";//изменение текстовой строки
}

void Cl_child_2::get_handler(string message)
{
	cout << endl << "Signal to " << get_absolute_coordinate() << " Text:  " << message;//вывод сообщения с координатой
}
