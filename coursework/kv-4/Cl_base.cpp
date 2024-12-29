#include "Cl_base.h"

Cl_base::Cl_base(Cl_base* p_head_object, string s_object_name)
{
    this->p_head_object = p_head_object; // Присвоение указателя на родительский объект
    this->s_object_name = s_object_name; // Присвоение имени объекта
    if (p_head_object) { // Есть родительский объект?
        p_head_object->subordinate_objects.push_back(this); // Добавить в производные объекты
    }
}

bool Cl_base::change_object_name(string s_object_name)
{
    if (s_object_name.empty()) { // Пустая строка?
        return false;
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех объектов из списка
        if (subordinate_object->get_object_name() == s_object_name) { // Если имя равно искомому
            return false;
        }
    }
    this->s_object_name = s_object_name; // Сменить имя
    return true;
}

string Cl_base::get_object_name()
{
    return s_object_name; // Вернуть имя объекта
}

Cl_base* Cl_base::get_head_object()
{
    return p_head_object; // Вернуть указатель на родительский объект
}

void Cl_base::show_object_tree()
{
    cout << endl;
    Cl_base* head_object = p_head_object; // Указатель на головной объект
    while (head_object != nullptr) { // Существует головной объект?
        cout << "    "; // Отступ
        head_object = head_object->p_head_object; // Обновление головного объекта
    }
    cout << s_object_name; // Вывод имени объекта
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
        subordinate_object->show_object_tree(); // Уход в рекурсию
    }
}

Cl_base* Cl_base::get_sub_object_by_name(string s_object_name)
{
    if (!s_object_name.empty()) { // Строка не пустая?
        for (Cl_base* subordinate_object : subordinate_objects) { // Для всех объектов из списка
            if (subordinate_object->get_object_name() == s_object_name) { // Имя равно искомому?
                return subordinate_object; // Вернуть указатель на подчиненный объект
            }
        }
    }
    return nullptr;
}

Cl_base* Cl_base::get_branch_object_by_name(string s_object_name)
{
    if (this->s_object_name == s_object_name) { // Строка совпадает с именем объекта?
        return this; // Вернуть объект
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
        if (subordinate_object->get_object_name() == s_object_name) { // Строка совпадает с именем объекта?
            return subordinate_object; // Вернуть объект
        }
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
        if (subordinate_object->get_branch_object_by_name(s_object_name)) { // Есть в ветви такое имя?
            return subordinate_object->get_branch_object_by_name(s_object_name); // Вернуть объект, если есть
        }
    }
    return nullptr;
}

Cl_base* Cl_base::get_object_by_name(string s_object_name)
{
    Cl_base* base = this; // Указатель на текущий объект
    while (true) {
        if (base->get_head_object()) { // Существует головной объект?
            base = base->get_head_object(); // Обновить текущий объект
        } else {
            break;
        }
    }
    if (base->get_branch_object_by_name(s_object_name)) { // Есть в дереве такое имя?
        return base->get_branch_object_by_name(s_object_name); // Вернуть объект, если есть
    }
    return nullptr;
}

void Cl_base::show_object_tree_full()
{
    Cl_base* head_object = p_head_object; // Указатель на головной объект
    while (head_object != nullptr) { // Головной объект существует?
        cout << "    "; // Отступ
        head_object = head_object->p_head_object; // Обновление головного объекта
    }
    cout << s_object_name; // Вывод имени объекта
    if (object_state != 0) { // Вывод состояния
        cout << " is ready" << endl;
    } else {
        cout << " is not ready" << endl;
    }
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
        subordinate_object->show_object_tree_full(); // Уход в рекурсию
    }
}

void Cl_base::change_object_state(int object_state)
{
    if (object_state != 0) { // Состояние отлично от 0?
        Cl_base* head_object = p_head_object; // Указатель на головной объект
        bool f = true; // Объявление флага
        while (head_object != nullptr) { // Головной объект существует?
            if (head_object->object_state == 0) { // Состояние головного объекта 0?
                f = false;
                break;
            }
            head_object = head_object->p_head_object; // Обновление головного объекта
        }
        if (f) {
            this->object_state = object_state; // Обновление состояния объекта
        }
    } else {
        this->object_state = 0; // Обнуление состояния объекта
        for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
            subordinate_object->change_object_state(0); // Обнуление
        }
    }
}

bool Cl_base::change_head_object(Cl_base* p_head_object)
{
    if (!p_head_object || !get_head_object()) { // Создается новый корневой объект или переопределяется корневой объект?
        return false;
    }
    if (p_head_object->get_sub_object_by_name(this->get_object_name()) != nullptr) { // При переопределении появляется дубль?
        return false;
    }
    if (this->get_branch_object_by_name(p_head_object->s_object_name) == p_head_object) { // Новый головной объект в ветви текущего объекта?
        return false;
    }
    int k = 0; // Переменная счетчик
    for (Cl_base* subordinate_object : get_head_object()->subordinate_objects) { // Для всех подчиненных объектов
        if (subordinate_object->get_object_name() == this->get_object_name()) { // Имя объекта равно искомому?
            get_head_object()->subordinate_objects.erase(subordinate_objects.begin() + k); // Удаление текущего объекта из списка подчиненных
            break;
        } else {
            k++; // Увеличение счетчика
        }
    }
    this->p_head_object = p_head_object; // Переопределение указателя на головной объект
    this->p_head_object->subordinate_objects.push_back(this); // Добавление объекта в список подчиненных
    return true;
}

void Cl_base::delete_sub_object_by_name(string s_object_name)
{
    if (s_object_name.empty()) { // Строка пустая?
        return;
    }
    int k = 0; // Переменная счетчик
    for (Cl_base* subordinate_object : subordinate_objects) { // Для всех подчиненных объектов
        if (subordinate_object->get_object_name() == s_object_name) { // Имя объекта равно искомому?
            subordinate_objects.erase(subordinate_objects.begin() + k); // Удаление текущего объекта из списка подчиненных
            delete subordinate_object; // Очистка памяти
            break;
        } else {
            k++; // Увеличение счетчика
        }
    }
}

Cl_base* Cl_base::get_object_by_coordinate(string coordinate)
{
    if (!coordinate.empty()) { // Координата не пустая?
        Cl_base* base = this; // Указатель на текущий объект
        if (coordinate[0] == '.') { // Координата начинается с точки?
            if (coordinate.length() == 1) { // Длина равна 1?
                return this; // Вернуть текущий объект
            }
            return get_branch_object_by_name(coordinate.substr(1)); // Вернуть объект найденный по имени на ветке
        }
        if (coordinate[0] == '/') { // Координата начинается со слеша?
            while (true) {
                if (base->get_head_object()) { // Существует головной объект?
                    base = base->get_head_object(); // Обновить текущий объект
                } else {
                    break;
                }
            }
            if (coordinate.length() == 1) { // Длина равна 1?
                return base; // Вернуть корневой объект
            }
            if (coordinate[1] == '/') { // Второй элемент координаты равен слеш?
                return base->get_sub_object_by_name(coordinate.substr(2)); // Вернуть объект найденный среди подчиненных по имени
            }
            coordinate = coordinate.substr(1); // Отрезать первый элемент координаты
        }
        vector<string> names; // Массив для записи имен объектов в координате
        while (true) {
            if (coordinate.find('/') != string::npos) { // В координате есть слеш?
                names.push_back(coordinate.substr(0, coordinate.find('/'))); // Добавить в массив имя объекта до слеша
                coordinate = coordinate.substr(coordinate.find('/') + 1); // Обрезать первое имя и слеш
            } else {
                names.push_back(coordinate); // Добавить в массив имя объекта
                break;
            }
        }
        for (string name : names) { // Для всех элементов массива
            base = base->get_sub_object_by_name(name); // Обновить текущий объект
            if (!base) { // Нет подчиненного с таким именем?
                break;
            }
        }
        return base; // Вернуть текущий объект
    }
    return nullptr;
}

void Cl_base::set_connect(TYPE_SIGNAL p_signal, Cl_base* p_target, TYPE_HANDLER p_handler)
{
    for (connection* value : connects) { // Для всех элементов массива
        if (value->p_signal == p_signal && value->p_target == p_target && value->p_handler == p_handler) { // Существует уже такая связь?
            return;
        }
    }
    connection* value = new connection(); // Новый элемент
    value->p_signal = p_signal; // Присвоение значений свойств элемента
    value->p_target = p_target; // Присвоение значений свойств элемента
    value->p_handler = p_handler; // Присвоение значений свойств элемента
    connects.push_back(value); // Добавление в массив связей
}

void Cl_base::delete_connect(TYPE_SIGNAL p_signal, Cl_base* p_target, TYPE_HANDLER p_handler)
{
    bool f = false; // Флаг
    int index = 0; // Индекс
    connection* del; // Указатель на удаляемый элемент
    for (connection* value : connects) { // Для всех элементов массива
        if (value->p_signal == p_signal && value->p_target == p_target && value->p_handler == p_handler) { // Существует такая связь?
            f = true; // Смена флага
            del = value; // Запоминаем элемент
            break;
        } else {
            index++; // Увеличение индекса
        }
    }
    if (f) { // True?
        connects.erase(connects.begin() + index); // Удаление из списка
        delete del; // Очистка памяти
    }
}

void Cl_base::emit_signal(TYPE_SIGNAL p_signal, string& message)
{
    if (object_state == 0) { // Объект не активирован?
        return;
    }
    TYPE_HANDLER p_handler; // Указатель на метод обработчика
    Cl_base* p_target; // Указатель на целевой объект
    (this->*p_signal)(message); // Вызов метода сигнала
    for (connection* value : connects) { // Для всех элементов массива
        if (value->p_signal == p_signal) { // Нужный нам сигнал?
            p_target = value->p_target; // Извлечение указателя на целевой объект
            p_handler = value->p_handler; // Извлечение указателя на метод обработчика
            if (p_target->object_state != 0) { // Объект активирован?
                (p_target->*p_handler)(message); // Вызов метода обработчика
            }
        }
    }
}

string Cl_base::get_absolute_coordinate()
{
    Cl_base* object = this; // Указатель на текущий объект
    string absolute = ""; // Строка координаты
    while (object->get_head_object()) { // Пока есть головной объект
        absolute = "/" + object->get_object_name() + absolute; // Добавление имени объекта в координату
        object = object->get_head_object(); // Обновление объекта
    }
    if (absolute.empty()) { // Строка пустая?
        return "/";
    }
    return absolute;
}
