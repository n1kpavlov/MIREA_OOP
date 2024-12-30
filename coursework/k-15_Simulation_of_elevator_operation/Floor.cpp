#include "Floor.h"
#include "Passenger.h"

Floor::Floor(Cl_base* p_head_object, int number) : Cl_base(p_head_object, floor_name + to_string(number))
{
	this -> number = number;//запонминание номера этажа
}

void Floor::signal_button_up(string &message)
{
	message = to_string(number);//обновление message
}

void Floor::signal_button_down(string &message)
{
	message = to_string(number * (-1));//обновление message
}

void Floor::signal_output(string &message){}

void Floor::handler_add_passenger(string message)
{
	int i = 0, num;
	while (message[i] != ' ') {//поиск пробела в строке
		i++;
	}
	num = stoi(message.substr(0, i));//извлечение номера этажа
	if (num != number) {//извлеченный этаж отличается от текущего?
		return;
	}
	i++;
	int j = i, wish_floor;
	while (message[j] != ' ') {//поиск пробела в строке
		j++;
	}
	wish_floor = stoi(message.substr(i, j - i));//извлечение целевого этажа
	string name = message.substr(j + 1);//извлечение имени пассажира
	Passenger* p = new Passenger(this, name, wish_floor);//создание нового пассажтра
	p -> activate();//активация объектов
	if (wish_floor > number) {//целевой этаж больше текущего?
		emit_signal(SIGNAL_D(Floor::signal_button_up), message); //выдача сигнала кнопки вверх
	}
	else {
		emit_signal(SIGNAL_D(Floor::signal_button_down), message; //выдача сигнала кнопки вниз
	}
}

void Floor::handler_condition(string message)
{
	if (stoi(message) != number){//не текущий этаж?
		return;
	}
	string up = "", down = "";//строки имен пассажиров на этаже
	for (auto subordinate_object : get_subordinate_objects()) {//для всех подчиненных объектав
		if (((Passenger*) subordinate_object) -> wish_floor > number) {//целевой этаж больше текущего?
			up += " " + subordinate_object -> get_object_name().substr(11);//добавить имя в up
		}
		else {
			down += " " + subordinate_object -> get_object_name().substr(11);//добавить имя в down
		}
	}
	message = "\nCondition on the floor " + message + " -up-" + up + "\nCondition on the floor " + message + " -down-" + down;//строка вывода
	emit_signal(SIGNAL_D(Floor::signal_output), message);//выдача сигнала вывода
}

void Floor::handler_syscon(string message)
{
	int up = 0, down = 0;//колличество пассажиров, желающих поехавть вверх и вниз
	for (auto subordinate_object : get_subordinate_objects()) {//для всех подчиненных объектов
		if (((Passenger*) subordinate_object) -> wish_floor > number) {//целевой этаж больше текущего?
			up++;//увеличение up
		}
		else {
			down++;//увеличение down
		}
	}
	if (up + down > 0) {//есть пассажиры на этаже?
		message = " (" + to_string(number) + ": " + to_string(up) + "-" + to_string(down) + ")";//строка вывода
		emit_signal(SIGNAL_D(Floor::signal_output), message);//выдача сигнала вывода
	}
}
