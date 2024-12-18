#include "Cl_application.h"

Cl_application::Cl_application(Cl_base* p_head_object, string s_name_object):Cl_base(p_head_object, s_name_object)
{
	cin >> s_name_object;//ввод имени объекта
	change_object_name(s_name_object);//изменение имени объекта
}

void Cl_application::build_tree_objects()
{
	Cl_base* last_object = this;//Создание указателя на текущий объект
	string sub, head;//Создание строк
	cin >> head >> sub;//Ввод значения строк
	while (head != sub) {//пока значения строк не равны
		if (last_object -> get_object_name() == head || (last_object -> get_head_object() != nullptr && last_object -> get_head_object() -> get_object_name() == head)) {//если имя равно head или есть родительский объект и имя родительсякого равно head
			auto *head_object = last_object -> get_object_name() == head ?//новому указателю присваиваем значение текущего, если имя равно строке head
				last_object : last_object -> get_head_object();
			if (head_object -> get_sub_object_by_name(sub) == nullptr) {//если имя не найдено, то
				auto *subordinate_object = new Cl_child(head_object, sub);//Создаем новый объект
				last_object = subordinate_object;//новый объект становится последним
			}
		}
		cin >> head >> sub;//Ввод значения строк
	}
}

int Cl_application::exec_app()
{
	cout << get_object_name();//вывод имени головного объекта
	show_object_tree();//вывод дерева объектов
	return 0;
}
