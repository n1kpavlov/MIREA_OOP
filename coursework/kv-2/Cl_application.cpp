#include "Cl_application.h"

Cl_application::Cl_application(Cl_base* p_head_object, string s_name_object):Cl_base(p_head_object, s_name_object)
{
	cin >> s_name_object;//ввод имени объекта
	change_object_name(s_name_object);//изменение имени объекта
}

void Cl_application::build_tree_objects()
{
	string head, sub;//переменные имен объектов
	Cl_base* head_object;//указатель на головной объект
	int iClass, iState;//номера классов и состояний
	while (true) {//ввод дерева
		cin >> head;//ввод имени головного объекта
		if (head == "endtree") {//если endtree то выход из цикла
			break;
		}
		cin >> sub >> iClass;//ввод номера класса
		head_object = get_object_by_name(head);//поиск годовного объекта по имени
		if (head_object != nullptr && head_object -> get_branch_object_by_name(sub) == nullptr) {//если есть головной объект и нет повторений имен в подчиенных
			switch(iClass)//создание объекта по номеру класса
			{
				case 2:
					new Cl_child_2(head_object, sub);
					break;
				case 3:
					new Cl_child_3(head_object, sub);
					break;
				case 4:
					new Cl_child_4(head_object, sub);
					break;
				case 5:
					new Cl_child_5(head_object, sub);
					break;
				case 6:
					new Cl_child_6(head_object, sub);
					break;
			}
		}
	}
	while (cin >> head) {//Цикл ввода состояний объектов
		cin >> iState;//ввод состояния
		get_object_by_name(head) -> change_object_state(iState);//Смена состояния
	}
}

int Cl_application::exec_app()
{
	cout << "Object tree" << endl;
	show_object_tree();//вывод дерева объектов
	cout << "The tree of objects and their readiness" << endl;
	show_object_tree_full();//вывод состояний объектов
	return 0;
}
