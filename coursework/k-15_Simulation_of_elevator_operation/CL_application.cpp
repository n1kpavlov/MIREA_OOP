#include "CL_application.h"
#include "Elevator.h"
#include "Floor.h"
#include "Input.h"
#include "Output.h"
#include "Passenger.h"
#include "RemoteController.h"

CL_application::CL_application(CL_base* p_head_object, string s_name_object):CL_base(p_head_object, s_name_object)
{
    change_object_name("object_system");
    tik = 1;
}

void CL_application::build_tree_objects()
{
    RemoteController* remote_control = new RemoteController(this);
    Elevator* elevator = new Elevator(remote_control);
    Input* input = new Input(this);
    Output* output = new Output(this);
    activate();
    set_connect(SIGNAL_D(CL_application::signal_input), input, HANDLER_D(Input::handler_input));
    input -> set_connect(SIGNAL_D(Input::signal_input), remote_control, HANDLER_D(RemoteController::handler_input));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_set_mass), elevator, HANDLER_D(Elevator::handler_receive_mass));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_add_floor), this, HANDLER_D(CL_application::handler_add_floor));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_syscon), this, HANDLER_D(CL_application::handler_syscon));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_syscon), elevator, HANDLER_D(Elevator::handler_syscon));
    string message;
    emit_signal(SIGNAL_D(CL_application::signal_input), message);
    emit_signal(SIGNAL_D(CL_application::signal_input), message);
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_turn_off), this, HANDLER_D(CL_application::handler_turn_off));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_output), output, HANDLER_D(output::handler_output));
    set_connect(SIGNAL_D(CL_application::signal_output), output, HANDLER_D(output::handler_output));
    set_connect(SIGNAL_D(CL_application::signal_upd), remote_control, HANDLER_D(RemoteController::handler_upd));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_elevator_condition), elevator, HANDLER_D(Elevator::handler_condition));
    elevator -> set_connect(SIGNAL_D(Elevator::signal_output), output, HANDLER_D(output::handler_output));
    remote_control -> set_connect(SIGNAL_D(RemoteController::signal_show_tree), this, HANDLER_D(CL_application::handler_show_tree));
}

int CL_application::exec_app()
{
    string message = "Ready to work";
    emit_signal(SIGNAL_D(CL_application::signal_output), message);
    run = true;
    while(true) {
        emit_signal(SIGNAL_D(CL_application::signal_input), message);
        if (run) {
            string text = "";
            emit_signal(SIGNAL_D(CL_application::signal_upd), text);
        }
        else {
            break;
        }
        tikt++;
    }
    return 0;
}

void CL_application::handler_add_floor(string message) {
    int num = stoi(message);
    CL_base* remote_control = get_sub_object_by_name(remote_controller_name);
    CL_base* output = get_sub_object_by_name("object_display_screen");
    for (int i = 0; i < num; i++) {
        Floor* f = new Floor(this, i + 1);
        f -> activate();
        if (i) {
            f -> set_connect(SIGNAL_D(Floor::signal_button_down), remote_control, HANDLER_D(RemoteController::handler_button));
        }
        if (i < num - 1) {
            f -> set_connect(SIGNAL_D(Floor::signal_button_up), remote_control, HANDLER_D(RemoteController::handler_button));
        }
        remote_control -> set_connect(SIGNAL_D(RemoteController::signal_add_passenger), f, HANDLER_D(Floor::handler_add_passenger));
        remote_control -> set_connect(SIGNAL_D(RemoteController::signal_floor_condition), f, HANDLER_D(Floor::handler_condition));
        remote_control -> set_connect(SIGNAL_D(RemoteController::signal_syscon), f, HANDLER_D(Floor::handler_syscon));
        f -> set_connect(SIGNAL_D(Floor::signal_output), output, HANDLER_D(output::handler_output));
    }
}

void CL_application::handler_turn_off(string message) {
    run = false;
    message = "\n" + message;
    emit_signal(SIGNAL_D(CL_application::signal_output), message);
    return;
}

void CL_application::handler_syscon(string message) {
    message = "\n" + to_string(tik) + ": ";
    emit_signal(SIGNAL_D(CL_application::signal_output), message);
}

void CL_application::handler_show_tree(string message) {
    run = false;
    message = "\n";
    emit_signal(SIGNAL_D(CL_application::signal_output), message);
    show_object_tree_full();
}

void CL_application::signal_input(string& message){}
void CL_application::signal_output(string& message){}
void CL_application::signal_upd(string& message){}
