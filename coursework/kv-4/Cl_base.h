#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <iostream>
#include <vector>
#include <string>
#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f)

using namespace std;

class Cl_base;
typedef void(Cl_base::*TYPE_SIGNAL)(string&);//тип сигнала
typedef void(Cl_base::*TYPE_HANDLER)(string);//тип обработчика
struct connection//структура связи
{
	TYPE_SIGNAL p_signal;//указатель на метод сигнала
	Cl_base* p_target;//указатель на целевой объект
	TYPE_HANDLER p_handler;//указатель на метод обработчика
};

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

	bool change_head_object(Cl_base*);//метод переопределения головного объекта
	void delete_sub_object_by_name(string);//метод удаления подчиненного объекта по наименованию
	Cl_base* get_object_by_coordinate(string);//метод получения указателя на объект по его координате

	void set_connect(TYPE_SIGNAL, Cl_base*, TYPE_HANDLER);//метод установки связи
	void delete_connect(TYPE_SIGNAL, Cl_base*, TYPE_HANDLER);//метод удаления связи
	void emit_signal(TYPE_SIGNAL, string&);//метод выдачи синала
	string get_absolute_coordinate();//метод получения абсолютной координаты
	int object_class = 1;//класс объекта

private:
	int object_state = 1;//состояние объекта
	string s_object_name;//имя объекта
	Cl_base* p_head_object;//указатель на родительский объект
	vector <Cl_base*> subordinate_objects;//подчиненные объекты
	vector <connection*> connects;//установленные связи
};

#endif
