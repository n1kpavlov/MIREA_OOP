#include "Cl_application.h"

Cl_application::Cl_application(Cl_base* p_head_object, string s_name_object): Cl_base(p_head_object, s_name_object)
{
    cin >> s_name_object; // Ввод имени объекта
    change_object_name(s_name_object); // Изменение имени объекта
}

void Cl_application::build_tree_objects()
{
    string head, sub; // Переменные имен объектов
    Cl_base* head_object; // Указатель на головной объект
    int iClass; // Номера классов

    while (true) {
        cin >> head; // Ввод имени головного объекта
        if (head == "endtree") { // Если endtree, то выход из цикла
            break;
        }
        cin >> sub >> iClass; // Ввод имени подчиненного объекта и номера класса
        head_object = get_object_by_coordinate(head); // Поиск головного объекта по координате
        
        if (head_object) {
            if (head_object->get_sub_object_by_name(sub)) { // Есть ли дубль?
                cout << head << "     Dubbing the names of subordinate objects" << endl;
                continue;
            }
            
            switch (iClass) { // Создание объекта по номеру класса
                case 2:
                    new Cl_child_2(head_object, sub);
                    break;
                case 3:
                    new Cl_child_3(head_object, sub);
                    break;
                case 4:
                    new Cl_child_4(head_object, sub);
                    break;
                case 5:
                    new Cl_child_5(head_object, sub);
                    break;
                case 6:
                    new Cl_child_6(head_object, sub);
                    break;
            }
        } else {
            cout << "Object tree" << endl;
            this->show_object_tree(); // Вывод построенного дерева
            cout << "The head object " << head << " is not found" << endl;
            exit(1);
        }
    }
}

int Cl_application::exec_app()
{
    string command; // Строка команды
    vector<string> args; // Вектор для парсинга строки

    cout << "Object tree";
    show_object_tree(); // Вывод дерева объектов

    Cl_base* from = this, * to = nullptr; // Указатели на объект
    vector<TYPE_SIGNAL> signals = {SIGNAL_D(Cl_child_2::get_signal), SIGNAL_D(Cl_child_3::get_signal), SIGNAL_D(Cl_child_4::get_signal), SIGNAL_D(Cl_child_5::get_signal), SIGNAL_D(Cl_child_6::get_signal)}; // Вектор сигналов
    vector<TYPE_HANDLER> handlers = {HANDLER_D(Cl_child_2::get_handler), HANDLER_D(Cl_child_3::get_handler), HANDLER_D(Cl_child_4::get_handler), HANDLER_D(Cl_child_5::get_handler), HANDLER_D(Cl_child_6::get_handler)}; // Вектор обработчиков

    getline(cin, command); // Чтение строки
    while (true) {
        getline(cin, command); // Чтение строки
        if (command == "end_of_connections") { // Строка означает завершение?
            break;
        }
        
        args.clear(); // Очистить вектор
        while (command.find(' ') != string::npos) { // Пока есть пробел в строке
            args.push_back(command.substr(0, command.find(' '))); // Добавление в конец вектора
            command = command.substr(command.find(' ') + 1); // Обрезание строки до первого пробела
        }
        args.push_back(command); // Добавление в конец вектора

        if (args.size() < 3) { // Размер меньше 3?
            continue;
        }

        from = get_object_by_coordinate(args.at(1)); // Извлечение координаты первого объекта
        to = get_object_by_coordinate(args.at(2)); // Извлечение координаты второго объекта

        if (!from) { // Объект по координате не определен?
            cout << endl << "Object " << args.at(1) << " not found" << endl;
            continue;
        }

        if (args.at(0) == "SET_CONDITION") { // Команда set_condition?
            from->change_object_state(atoi(args.at(2).c_str())); // Изменение состояния объекта
            continue;
        }

        if (from->object_class < 2) { // Класс объекта меньше 2?
            continue;
        }

        if (args.at(0) == "EMIT") { // Команда emit?
            command = ""; // Очистка строки текста сообщения
            for (int i = 2; i < args.size(); i++) { // Цикл по элементам вектора со второго
                if (i != args.size() - 1) { // Элемент не последний?
                    command += args.at(i) + " "; // Добавление слова в текст сообщения и пробела
                } else {
                    command += args.at(i); // Добавление слова в текст сообщения
                }
            }
            from->emit_signal(signals.at(from->object_class - 2), command); // Вызов метода выдачи сигнала
        } else {
            if (to) { // Объект по координате определен?
                if (args.at(0) == "SET_CONNECT") { // Команда set_connect?
                    from->set_connect(signals.at(from->object_class - 2), to, handlers.at(from->object_class - 2)); // Установка связи
                } else if (args.at(0) == "DELETE_CONNECT") { // Команда delete_connect?
                    from->delete_connect(signals.at(from->object_class - 2), to, handlers.at(from->object_class - 2)); // Удаление связи
                }
            } else {
                cout << endl << "Handler object " << args.at(2) << " not found" << endl;
            }
        }
    }

    return 0;
}
