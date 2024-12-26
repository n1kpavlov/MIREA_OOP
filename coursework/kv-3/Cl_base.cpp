#include "Cl_base.h"

Cl_base::Cl_base(Cl_base* p_head_object, string s_object_name) {
    this->p_head_object = p_head_object; // присвоение указателя на родительский объект
    this->s_object_name = s_object_name; // присвоение имени объекта
    if (p_head_object) { // есть родительский объект?
        p_head_object->subordinate_objects.push_back(this); // добавить в подчиненные объекты
    }
}

bool Cl_base::change_object_name(string s_object_name) {
    if (s_object_name.empty()) { // пустая строка?
        return false;
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех объектов из списка
        if (subordinate_object->get_object_name() == s_object_name) { // если имя равно искомому
            return false;
        }
    }
    this->s_object_name = s_object_name; // сменить имя
    return true;
}

string Cl_base::get_object_name() {
    return s_object_name; // вернуть имя объекта
}

Cl_base* Cl_base::get_head_object() {
    return p_head_object; // вернуть указатель на родительский объект
}

void Cl_base::show_object_tree() {
    Cl_base* head_object = p_head_object; // указатель на головной объект
    while (head_object != nullptr) { // существует головной объект?
        cout << "    "; // отступ
        head_object = head_object->p_head_object; // обновление головного объекта
    }
    cout << s_object_name << endl; // вывод имени объекта
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
        subordinate_object->show_object_tree(); // уход в рекурсию
    }
}

Cl_base* Cl_base::get_sub_object_by_name(string s_object_name) {
    if (!s_object_name.empty()) { // строка не пустая?
        for (Cl_base* subordinate_object : subordinate_objects) { // для всех объектов из списка
            if (subordinate_object->get_object_name() == s_object_name) { // имя равно искомому?
                return subordinate_object; // вернуть указатель на подчиненный объект
            }
        }
    }
    return nullptr;
}

Cl_base* Cl_base::get_branch_object_by_name(string s_object_name) {
    if (this->s_object_name == s_object_name) { // строка совпадает с именем объекта?
        return this; // вернуть объект
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
        if (subordinate_object->get_object_name() == s_object_name) { // строка совпадает с именем объекта?
            return subordinate_object; // вернуть объект
        }
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
        if (subordinate_object->get_branch_object_by_name(s_object_name)) { // есть в ветви такое имя?
            return subordinate_object->get_branch_object_by_name(s_object_name); // вернуть объект, если есть
        }
    }
    return nullptr;
}

Cl_base* Cl_base::get_object_by_name(string s_object_name) {
    Cl_base* base = this; // указатель на текущий объект
    while (true) {
        if (base->get_head_object()) { // существует головной объект?
            base = base->get_head_object(); // обновить текущий объект
        } else {
            break;
        }
    }
    if (base->get_branch_object_by_name(s_object_name)) { // есть в дереве такое имя?
        return base->get_branch_object_by_name(s_object_name); // вернуть объект, если есть
    }
    return nullptr;
}

void Cl_base::show_object_tree_full() {
    Cl_base* head_object = p_head_object; // указатель на головной объект
    while (head_object != nullptr) { // головной объект существует?
        cout << "    "; // отступ
        head_object = head_object->p_head_object; // обновление головного объекта
    }
    cout << s_object_name; // вывод имени объекта
    if (object_state != 0) { // вывод состояния
        cout << " is ready" << endl;
    } else {
        cout << " is not ready" << endl;
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
        subordinate_object->show_object_tree_full(); // уход в рекурсию
    }
}

void Cl_base::change_object_state(int object_state) {
    if (object_state != 0) { // состояние отлично от 0?
        Cl_base* head_object = p_head_object; // указатель на головной объект
        bool f = true; // объявление флага
        while (head_object != nullptr) { // головной объект существует?
            if (head_object->object_state == 0) { // состояние головного объекта 0?
                f = false;
                break;
            }
            head_object = head_object->p_head_object; // обновление головного объекта
        }
        if (f) {
            this->object_state = object_state; // обновление состояния объекта
        }
    } else {
        this->object_state = 0; // обнуление состояния объекта
        for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
            subordinate_object->change_object_state(0); // обнуление
        }
    }
}

bool Cl_base::change_head_object(Cl_base* p_head_object) {
    if (!p_head_object || !get_head_object()) { // создается новый корневой объект или переопределяется корневой объект?
        return false;
    }
    if (p_head_object->get_sub_object_by_name(this->get_object_name()) != nullptr) { // при переопределении появляется дубль?
        return false;
    }
    if (this->get_branch_object_by_name(p_head_object->s_object_name) == p_head_object) { // новый головной объект в ветви текущего объекта?
        return false;
    }
    get_head_object()->delete_sub_object_by_name(this->get_object_name()); // удаление объекта из списка подчиненных
    this->p_head_object = p_head_object; // переопределение указателя на головной объект
    this->p_head_object->subordinate_objects.push_back(this); // добавление объекта в список подчиненных
    return true;
}

void Cl_base::delete_sub_object_by_name(string s_object_name) {
    if (s_object_name.empty()) { // строка пустая?
        return;
    }
    int k = 0; // переменная счетчик
    for (Cl_base* subordinate_object : subordinate_objects) { // для всех подчиненных объектов
        if (subordinate_object->get_object_name() == s_object_name) { // имя объекта равно искомому?
            subordinate_objects.erase(subordinate_objects.begin() + k); // удаление текущего объекта из списка подчиненных
        } else {
            k++; // увеличение счетчика
        }
    }
}

Cl_base* Cl_base::get_object_by_coordinate(string coordinate) {
    if (!coordinate.empty()) { // координата не пустая?
        Cl_base* base = this; // указатель на текущий объект
        if (coordinate[0] == '.') { // координата начинается с точки?
            if (coordinate.length() == 1) { // длина равна 1?
                return this; // вернуть текущий объект
            }
            return get_branch_object_by_name(coordinate.substr(1)); // вернуть объект, найденный по имени на ветке
        }
        if (coordinate[0] == '/') { // координата начинается со слеша?
            while (true) {
                if (base->get_head_object()) { // существует головной объект?
                    base = base->get_head_object(); // обновить текущий объект
                } else {
                    break;
                }
            }
            if (coordinate.length() == 1) { // длина равна 1?
                return base; // вернуть корневой объект
            }
            if (coordinate[1] == '/') { // второй элемент координаты равен слешу?
                return base->get_sub_object_by_name(coordinate.substr(2)); // вернуть объект, найденный среди подчиненных по имени
            }
            coordinate = coordinate.substr(1); // отрезать первый элемент координаты
        }
        vector<string> names; // массив для записи имен объектов в координате
        while (true) {
            if (coordinate.find('/') != string::npos) { // в координате есть слеш?
                names.push_back(coordinate.substr(0, coordinate.find('/'))); // добавить в массив имя объекта до слеша
                coordinate = coordinate.substr(coordinate.find('/') + 1); // отрезать первое имя и слеш
            } else {
                names.push_back(coordinate); // добавить в массив имя объекта
                break;
            }
        }
        for (string name : names) { // для всех элементов массива
            base = base->get_sub_object_by_name(name); // обновить текущий объект
            if (!base) { // нет подчиненного с таким именем?
                break;
            }
        }
        return base; // вернуть текущий объект
    }
    return nullptr;
}
