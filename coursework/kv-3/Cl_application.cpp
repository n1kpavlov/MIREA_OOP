#include "Cl_application.h"

Cl_application::Cl_application(Cl_base*  p_head_object,  string s_name_object):Cl_base(p_head_object, s_name_object)
{
    cin >> s_name_object; // ввод имени объекта
    change_object_name(s_name_object); // изменение имени объекта
}

void Cl_application::build_tree_objects()
{
    string head, sub; // переменные имен объектов
    Cl_base* head_object; // указатель на головной объект
    int iClass; // номера классов
    while (true) { //ввод дерева
        cin >> head; // ввод имени головного объекта
        if (head == "endtree") { //если endtree то выход из цикла
            break;
        }
        cin >> sub >> iClass; // ввод номера класса
        head_object = get_object_by_coordinate(head); // поиск головного объекта по координате
        if (head_object) { //координата не nullptr?
            if (head_object -> get_sub_object_by_name(sub)) { //есть ли дубль?
                cout << head << "Dubbing the names of subordinate objects" << endl; // сообщение о дубле
                continue;
            }
            switch (iClass) { //создание объекта по номеру класса
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
            this -> show_object_tree(); // Вывод построенного дерева
            cout << "The head object " << head << " is not found"; //вывод сообщения об ошибке
            exit(1);
        }
    }
}

int Cl_application::exec_app()
{
    string command, args; // строки для парсинга команды
    vector<string> commands, callback; // вектора команд и вывода
    Cl_base* from = this, *target = nullptr; // указатели на текущий и целевой объект
    while (true) {
        getline(cin, command); // чтение команды
        commands.push_back(command); // добавление команды в список
        if (command == "END") { //команда end?
            break;
        }
    }
    cout << "Object tree" << endl;
    show_object_tree(); // вывод дерева объектов
    for (string doing : commands) { //для всех элементов вектора
        command = doing; // обновление команды
        if (command == "END") { //команда end?
            callback.push_back("Current object hierarchy tree"); // добавить сообщение в вывод
            break;
        }
        args = command.substr(command.find(' ') + 1); // извлечение координаты
        command = command.substr(0, command.find(' ')); // извлечение команды
        target = from -> get_object_by_coordinate(args); // определение целевого объекта
        if (command == "SET") { //команда set?
            if (target) { //существует?
                from = target; // обновление указателя
                callback.push_back("Object is set: " + from -> get_object_name()); // добавить сообщение в вывод
            } else {
                callback.push_back("The object was not found at the specified coordinate " + args); // добавить сообщение в вывод
            }
        } else if (command == "FIND") { //команда find?
            if (target) { //существует?
                callback.push_back(args + "      Object name: " + target -> get_object_name()); // добавить сообщение в вывод
            } else {
                callback.push_back(args + "     Object is not found"); // добавить сообщение в вывод
            }
        } else if (command == "MOVE") {
            if (target) { //существует?
                if (from -> get_branch_object_by_name(target -> get_object_name()) == target) {
                    callback.push_back(args + "     Redefining the head object failed"); // добавить сообщение в вывод
                } else if (target -> get_sub_object_by_name(from -> get_object_name())) {
                    callback.push_back(args + "      Dubbing the names of subordinate objects"); // добавить сообщение в вывод
                } else if (from -> change_head_object(target)) {
                    callback.push_back("New head object: " + from -> get_head_object() -> get_object_name()); // добавить сообщение в вывод
                }
            } else {
                callback.push_back(args + "      Head object is not found"); // добавить сообщение в вывод
            }
        } else if (command == "DELETE") {
            if (target) { //существует?
                Cl_base* to = target -> get_head_object(); // указатель на головной объект целевого
                if (to) {
                    string absolute = target -> get_object_name(); // добавление имени target в координату
                    to -> delete_sub_object_by_name(absolute); // удаление absolute из списка подчиненных
                    while (to -> get_head_object()) {
                        absolute = to -> get_object_name() + '/' + absolute; // добавление координаты
                        to = to -> get_head_object(); // обновление указателя
                    }
                    callback.push_back("The object /" + absolute + " has been deleted"); // добавить сообщение в вывод
                }
            }
        }
    }
    for (string back : callback) {
        cout << back << endl; // вывод элемента
    }
    show_object_tree(); // вывод дерева объектов
    return 0;
}
