#include "Elevator.h"
#include "Passenger.h"

Elevator::Elevator(Cl_base* p_head_object) : Cl_base(p_head_object, elevator_name) {
    dir = stop;  // остановка движения
    floor = 1;  // первый этаж
    prev_dir = up;  // предыдущее перемещение вверх
}

void Elevator::signal_output(string &message) {}

void Elevator::handler_condition(string message) {
    string output = "\nElevator condition: " + to_string(floor) + " " + to_string(get_subordinate_objects().size()) + " ";

    if (dir != Elevator::stop) {  // лифт не стоит?
        output += "direction ";
        if (dir == Elevator::up) {
            output += "up";
        } else {
            output += "down";
        }
    } else {
        output += "stop";
    }
    emit_signal(SIGNAL_D(Elevator::signal_output), output);  // выдача сигнала на вывод
}

void Elevator::handler_receive_mass(string message) {
    mass = stoi(message);  // обновление вместимости лифта
}

void Elevator::handler_syscon(string message) {
    message = "Elevator: " + to_string(floor) + " " + to_string(get_subordinate_objects().size()) + " Floors:";
    emit_signal(SIGNAL_D(Elevator::signal_output), message);  // выдать сигнал на вывод
}

void Elevator::upd() {
    floor += dir;  // смена этажа по ходу движения
}
