#include "Passenger.h"

Passenger::Passenger(Cl_base* p_head_object, string name, int wish_floor) : Cl_base(p_head_object, "object_FIO_" + name)
{
	this -> wish_floor  = wish_floor;//установка желаемого этажа
}
