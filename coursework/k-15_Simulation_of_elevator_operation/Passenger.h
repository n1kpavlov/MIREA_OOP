#ifndef __PASSENGER__H
#define __PASSENGER__H
#include "Cl_base.h"

class Passenger : public Cl_base
{
public:
	int wish_floor;//целевой этаж
	Passenger(Cl_base* p_head_object, string name, int wish_floor);//Параметризированный конструктор
};

#endif
