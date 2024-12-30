#include <stdlib.h>
#include <stdio.h>
#include "Cl_application.h"

int main()
{
	Cl_application ob_cl_application(nullptr);//создание объекта приложения
	ob_cl_application.build_tree_objects();//конструирование системы
	return ob_cl_application.exec_app();//запуск системы
}
