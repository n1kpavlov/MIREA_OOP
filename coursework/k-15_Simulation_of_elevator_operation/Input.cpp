#include "Input.h"

Input::Input(Cl_base* p_head_object) : Cl_base(p_head_object, "object_read_command"){}

void Input::signal_input(string& message){}

void Input::handler_input(string message)
{
	getline(cin, message);//ввод строки
	emit_signal(SIGNAL_D(Input::signal_input), message);//выдача сигнала
}
