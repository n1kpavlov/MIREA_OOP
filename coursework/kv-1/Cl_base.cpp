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
	if (subordinate_objects.size() > 0){//есть подчиненные объекты?
		cout << endl << get_object_name();//вывод имени объекта
		for (Cl_base* subordinate_object : subordinate_objects) {//для всех обектов из списка
			cout << "  " << subordinate_object -> get_object_name();//вывод имени объета
		}
		for (Cl_base* subordinate_object : subordinate_objects) {//для всех объектов из списка
			if (subordinate_object -> subordinate_objects.size() > 0) {//есть подчиненные объекты?
				subordinate_object -> show_object_tree();//уход в рекурсию
			}
		}
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
