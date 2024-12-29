#include "RemoteController.h"
#include "Elevator.h"
#include "Passenger.h"
#include "Floor.h"

RemoteController::RemoteController(Cl_base* p_head_object) :
    Cl_base(p_head_object, remote_controller_name) {}

void RemoteController::handler_upd(string message) {
    Elevator* elevator =
        (Elevator*)get_sub_object_by_name(elevator_name); // объект лифта

    if (!elevator) {
        return;
    }

    Floor* floor = (Floor*)get_object_by_coordinate("/" + floor_name +
                                                  to_string(elevator->floor));
    if (!floor) {
        return;
    }

    if (elevator->dir != Elevator::stop) { // лифт движется?
        elevator->prev_dir = elevator->dir; // обновление предыдущего состояния

        for (auto subordinate_object : elevator->get_subordinate_objects()) {
            if (((Passenger*)subordinate_object)->wish_floor == elevator->floor) {
                elevator->dir = Elevator::stop; // остановка лифта
                break;
            }
        }

        if (elevator->mass - elevator->get_subordinate_objects().size() > 0) {
            for (auto subordinate_object : floor->get_subordinate_objects()) {
                if ((((Passenger*)subordinate_object)->wish_floor - elevator->floor) *
                        elevator->dir >
                    0 ||
                    elevator->get_subordinate_objects().empty()) {
                    elevator->dir = Elevator::stop; // остановка лифта
                    break;
                }
            }
        }
    }

    if (elevator->dir == Elevator::stop) { // лифт стоит?
        bool should_move = true; // разрешение на движение
        for (auto subordinate_object : elevator->get_subordinate_objects()) {
            if (((Passenger*)subordinate_object)->wish_floor == floor->number) {
                should_move = false; // не двигается
                elevator->delete_sub_object_by_name(subordinate_object->get_object_name()); // пассажир выходит из лифта
            }
        }

        if (elevator->get_subordinate_objects().empty()) {
            if (!req.empty() && abs(req[0]) == floor->number) {
                elevator->prev_dir = req[0] > 0 ? Elevator::up : Elevator::down;
            } else {
                elevator->prev_dir = Elevator::stop;
            }
        }

        int entered = 0; // число вошедших в лифт
        for (auto subordinate_object : floor->get_subordinate_objects()) {
            if (elevator->mass > elevator->get_subordinate_objects().size() &&
                (((Passenger*)subordinate_object)->wish_floor - floor->number) *
                        elevator->prev_dir >
                    0) {
                subordinate_object->change_head_object(elevator); // пассажир заходит в лифт
                should_move = false; // не двигается
                entered++;
            }
        }

        int shift = 0;
        for (int i = 0; i < req.size(); i++) {
            if (entered && req[i] * elevator->prev_dir == floor->number) {
                shift++;
                entered--;
            } else if (i >= shift) {
                req[i - shift] = req[i];
            }
        }

        req.resize(req.size() - shift); // смена размера очереди
        if (should_move) {
            elevator->dir = elevator->prev_dir; // переопределение направления движения
        }
    }

    elevator->upd(); // обновление состояния лифта
}

void RemoteController::handler_input(string message) {
    if (message.empty()) {
        return;
    }

    if (message == "End of settings") {
        return;
    }

    if (message == "Turn off the system") {
        emit_signal(SIGNAL_D(RemoteController::signal_turn_off), message);
        return;
    }

    if (message == "SHOWTREE") {
        emit_signal(SIGNAL_D(RemoteController::signal_show_tree), message);
        return;
    }

    vector<string> command(1, "");
    for (char i : message) {
        if (i == ' ') {
            command.emplace_back();
        } else {
            command.back().push_back(i);
        }
    }

    if (command[0] == "Passenger") {
        if (command[1] == "condition") {
            string output;
            message = message.substr(20);
            Cl_base* passenger = get_object_by_name("object_FIO_" + message);
            if (passenger) {
                if (passenger->get_head_object()->get_object_name() == elevator_name) {
                    output = "\nPassenger condition: " + message + " in the elevator";
                } else {
                    output = "\nPassenger condition: " + message + " on the floor " +
                             to_string(((Floor*)passenger->get_head_object())->number);
                }
            } else {
                output = "\nPassenger " + message + " not found";
            }
            emit_signal(SIGNAL_D(RemoteController::signal_output), output);
        } else {
            message = message.substr(10);
            emit_signal(SIGNAL_D(RemoteController::signal_add_passenger), message);
        }
    } else if (command[0] == "Condition") {
        emit_signal(SIGNAL_D(RemoteController::signal_floor_condition), command[4]);
    } else if (command[0] == "Elevator") {
        emit_signal(SIGNAL_D(RemoteController::signal_elevator_condition), message);
    } else if (command[0] == "System") {
        emit_signal(SIGNAL_D(RemoteController::signal_syscon), message);
    } else {
        emit_signal(SIGNAL_D(RemoteController::signal_set_mass), command[1]);
        emit_signal(SIGNAL_D(RemoteController::signal_add_floor), command[0]);
    }
}

void RemoteController::handler_button(string message) {
    req.push_back(stoi(message));
}

void RemoteController::signal_add_floor(string& message) {}
void RemoteController::signal_set_mass(string& message) {}
void RemoteController::signal_turn_off(string& message) {}
void RemoteController::signal_add_passenger(string& message) {}
void RemoteController::signal_output(string& message) {}
void RemoteController::signal_floor_condition(string& message) {}
void RemoteController::signal_elevator_condition(string& message) {}
void RemoteController::signal_syscon(string& message) {}
void RemoteController::signal_show_tree(string& message) {}
