#ifndef __CL_BASE__H
#define __CL_BASE__H

#include <iostream>
#include <vector>
#include <string>

#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f)

using namespace std;

class Cl_base;
typedef void(Cl_base::*TYPE_SIGNAL)(string&); // тип сигнала
typedef void(Cl_base::*TYPE_HANDLER)(string); // тип обработчика

struct connection {
    TYPE_SIGNAL p_signal;        // указатель на метод сигнала
    Cl_base* p_target;           // указатель на целевой объект
    TYPE_HANDLER p_handler;      // указатель на метод обработчика
};

class Cl_base {
public:
    Cl_base(Cl_base* p_head_object = nullptr, string s_object_name = "Base_object");

    bool change_object_name(string);
    string get_object_name();
    Cl_base* get_head_object();
    Cl_base* get_sub_object_by_name(string);
    Cl_base* get_branch_object_by_name(string);
    Cl_base* get_object_by_name(string);
    void show_object_tree();
    void show_object_tree_full();
    void change_object_state(int);
    bool change_head_object(Cl_base*);
    void delete_sub_object_by_name(string);
    Cl_base* get_object_by_coordinate(string);
    void set_connect(TYPE_SIGNAL, Cl_base*, TYPE_HANDLER);
    void delete_connect(TYPE_SIGNAL, Cl_base*, TYPE_HANDLER);
    void emit_signal(TYPE_SIGNAL, string&);
    string get_absolute_coordinate();
    void activate();
    vector<Cl_base*> get_subordinate_objects();

private:
    int object_state = 0;                  // состояние объекта
    string s_object_name;                  // имя объекта
    Cl_base* p_head_object;                // указатель на родительский объект
    vector<Cl_base*> subordinate_objects;  // подчиненные объекты
    vector<connection*> connects;          // установленные связи
};

#endif
