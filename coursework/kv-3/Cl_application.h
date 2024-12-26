#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "Cl_child_2.h"
#include "Cl_child_3.h"
#include "Cl_child_4.h"
#include "Cl_child_5.h"
#include "Cl_child_6.h"

class Cl_application: public Cl_base // наследование класса
{
public:
    Cl_application(Cl_base* p_head_object, string = "Base_object"); // параметризированный конструктор
    void build_tree_objects(); // метод построения дерева
    int exec_app(); // метод запуска системы
};

#endif
