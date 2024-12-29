#ifndef __REMOTECONTROLLER__H
#define __REMOTECONTROLLER__H
#include "Cl_base.h"

const string remote_controller_name = "object_remote_control";

class RemoteController : public Cl_base
{
public:
    RemoteController(Cl_base* p_head_object); // Параметризированный конструктор

    void handler_upd(string);              // Метод обработчика сигнала обновления состояния
    void handler_input(string);            // Метод обработчика сигнала ввода
    void handler_button(string);           // Метод обработчика сигнала нажатия на кнопку вызова
    void signal_add_floor(string&);        // Метод сигнала добавления этажа
    void signal_set_mass(string&);         // Метод сигнала изменения вместимости лифта
    void signal_turn_off(string&);         // Метод сигнала завершения работы системы
    void signal_add_passenger(string&);    // Метод сигнала добавления пассажира
    void signal_output(string&);           // Метод сигнала вывода
    void signal_floor_condition(string&);  // Метод сигнала вывода состояния этажа
    void signal_elevator_condition(string&); // Метод сигнала вывода состояния лифта
    void signal_syscon(string&);           // Метод сигнала вывода состояния системы
    void signal_show_tree(string&);        // Метод сигнала вывода иерархии объектов

private:
    vector<int> req; // Очередь пассажиров
};

#endif
