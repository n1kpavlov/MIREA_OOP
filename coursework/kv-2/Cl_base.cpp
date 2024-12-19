#include "Cl_base.h"

Cl_base::Cl_base(Cl_base* p_head_object, string s_object_name)
{
	this -> p_head_object = p_head_object;//присвоение указателя на родительский объект
	this -> s_object_name = s_object_name;//присвоение имени объекта
	if ( p_head_object ) {//есть родительский объект?
		p_head_object -> subordinate_objects.push_back(this);//добавить в производные объекты
	}
}

bool Cl_base::change_object_name(string s_object_name)
{
	if (s_object_name.empty()) {//пустая строка?
		return false;
	}
	for (Cl_base* subordinate_object : subordinate_objects) {//для всех объектов из списка
		if (subordinate_object -> get_object_name() == s_object_name) {//если имя равно искомому
			return false;
		}
	}
	this -> s_object_name = s_object_name;//сменить имя
	return true;
}

string Cl_base::get_object_name()
{
	return s_object_name;//вернуть имя объекта
}

Cl_base* Cl_base::get_head_object()
{
	return p_head_object;//вернуть указатель на родительский объект
}

void Cl_base::show_object_tree()
{
	Cl_base* head_object = p_head_object;//указатель на головной объект
	while (head_object != nullptr) {//существует головной объект?
		cout << "    ";//отступ
		head_object = head_object -> p_head_object;//обновление головного объекта
	}
	cout << s_object_name << endl;//вывод имени объекта
	for (Cl_base* subordinate_object : subordinate_objects) {//для всех подчиненных объектов
		subordinate_object -> show_object_tree();//уход в рекурсию
	}
}

Cl_base* Cl_base::get_sub_object_by_name(string s_object_name)
{
	if (!s_object_name.empty()) {//строка не пустая?
		for (Cl_base* subordinate_object : subordinate_objects) {//для всех объектов из списка
			if (subordinate_object -> get_object_name() == s_object_name) {//имя равно искомому?
				return subordinate_object;//вернуть указатель на подчиненный объект
			}
		}
	}
	return nullptr;
}

Cl_base* Cl_base::get_branch_object_by_name(string s_object_name)
{
	if (this -> s_object_name == s_object_name) {//строка совпадает с именем объекта?
		return this;//вернуть объект
	}
	for (Cl_base* subordinate_object : subordinate_objects) {//для всех подчиненных объеков
		if (subordinate_object -> get_object_name() == s_object_name) {//строка совпадает с именем объекта?
			return subordinate_object;//вернуть объект
		}
	}
	for (Cl_base* subordinate_object : subordinate_objects) {//для всех подчиненных объектов
		if (subordinate_object -> get_branch_object_by_name(s_object_name)) {//есть в ветви такое имя?
			return subordinate_object -> get_branch_object_by_name(s_object_name);//вернуть объект, если есть
		}
	}
	return nullptr;
}

Cl_base* Cl_base::get_object_by_name(string s_object_name)
{
	Cl_base* base = this;//указатель на текущий объект
	while (true) {
		if (base -> get_head_object()) {//существует головной объект?
			base = base -> get_head_object();//обновить текущий объект
		}
		else {
			break;
		}
	}
	if (base -> get_branch_object_by_name(s_object_name)) {//есть в дереве такое имя?
		return base -> get_branch_object_by_name(s_object_name);//вернуть объект, если есть
	}
	return nullptr;
}

void Cl_base::show_object_tree_full()
{
	Cl_base* head_object = p_head_object;//указатель на головной объект
	while (head_object != nullptr) {//головной объект существует?
		cout << "    ";//отступ
		head_object = head_object -> p_head_object;//обновление головного объекта
	}
	cout << s_object_name;//вывод имени объекта
	if (object_state != 0) {//вывод состояния
		cout << " is ready" << endl;
	}
	else {
		cout << " is not ready" << endl;
	}
	for (Cl_base* subordinate_object : subordinate_objects) {//для всех подчиненных объектов
		subordinate_object -> show_object_tree_full();//уход в рекурсию
	}
}

void Cl_base::change_object_state(int object_state)
{
	if (object_state != 0) {//состояние отлично от 0?
		Cl_base* head_object = p_head_object;//указатель на головной объект
		bool f = true;//объявление флага
		while (head_object != nullptr) {//головной объект существует?
			if (head_object -> object_state == 0) {//состояние головного объекта 0?
				f = false;
				break;
			}
			head_object = head_object -> p_head_object;//обновление головного объекта
		}
		if (f) {
			this -> object_state = object_state;//обновление состояния объекта
		}
	}
	else {
		this -> object_state = 0;//обнуление состояния объекта
		for (Cl_base* subordinate_object : subordinate_objects) {//для всех подчиненных объектов
			subordinate_object -> change_object_state(0);//обнуление
		}
	}
}
