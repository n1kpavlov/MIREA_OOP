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
	void show_object_tree();//метод вывода дерева объектов
	Cl_base* get_sub_object_by_name(string);//метод поиска объекта по имени

private:
	string s_object_name;//имя объекта
	Cl_base* p_head_object;//указатель на родительский объект
	vector <Cl_base*> subordinate_objects;//подчиненные объекты
};

#endif
