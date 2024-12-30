#include "Output.h"
#include "Cl_application.h"
#include "Elevator.h"
#include "Floor.h"
#include "Passenger.h"
#include "RemoteController.h"

Output::Output(Cl_base* p_head_object) : Cl_base(p_head_object, "object_display_screen"){}

void Output::handler_output(string message)
{
	cout << message;//вывод сообщения
}
