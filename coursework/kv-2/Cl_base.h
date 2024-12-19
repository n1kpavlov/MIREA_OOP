#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cl_base//наименование класса
{
public:
	Cl_base (Cl_base* p_head_object, string s_object_name = "Base_object");//параметризированный конструктор
	bool change_object_name(string);//метод изменения имени
	string get_object_name();//метод получения имени
	Cl_base* get_head_object();//метод получения указателя на родительский объект
	Cl_base* get_sub_object_by_name(string);//метод поиска подчиненного объекта по имени
	Cl_base* get_branch_object_by_name(string);//метод поиска объекта на ветке по имени
	Cl_base* get_object_by_name(string);//метод поиска объекта по имени
	void show_object_tree();//метод вывода дерева объектов
	void show_object_tree_full();//метод вывода дерева объектов и состояния
	void change_object_state(int);//метод установки состояния

private:
	int object_state;//состояние объекта
	string s_object_name;//имя объекта
	Cl_base* p_head_object;//указатель на родительский объект
	vector <Cl_base*> subordinate_objects;//подчиненные объекты
};

#endif
