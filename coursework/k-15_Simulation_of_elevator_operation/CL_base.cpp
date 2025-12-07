#include "CL_base.h"

CL_base::CL_base(CL_base* p_head_object, string s_object_name)
{
    this -> p_head_object = p_head_object;
    this -> s_object_name = s_object_name;
    if (p_head_object) {
        p_head_object -> subordinate_objects.push_back(this);
    }
}

bool CL_base::change_object_name(string s_object_name)
{
    if (s_object_name.empty()) {
        return false;
    }
    for (CL_base* subordinate_object : subordinate_objects) {
        if (subordinate_object -> get_object_name() == s_object_name) {
            return false;
        }
    }
    this -> s_object_name = s_object_name;
    return true;
}

string CL_base::get_object_name()
{
    return s_object_name;
}

CL_base* CL_base::get_head_object()
{
    return p_head_object;
}

void CL_base::show_object_tree()
{
    cout << endl;
    CL_base* head_object = p_head_object;
    while (head_object != nullptr) {
        cout << " ";
        head_object = head_object -> p_head_object;
    }
    cout << s_object_name;
    for (CL_base* subordinate_object : subordinate_objects) {
        subordinate_object -> show_object_tree();
    }
}

CL_base* CL_base::get_sub_object_by_name(string s_object_name)
{
    if (!s_object_name.empty()) {
        for (CL_base* subordinate_object : subordinate_objects) {
            if (subordinate_object -> get_object_name() == s_object_name) {
                return subordinate_object;
            }
        }
    }
    return nullptr;
}

CL_base* CL_base::get_branch_object_by_name(string s_object_name)
{
    if (this -> s_object_name == s_object_name) {
        return this;
    }
    for (CL_base* subordinate_object : subordinate_objects) {
        if (subordinate_object -> get_object_name() == s_object_name) {
            return subordinate_object;
        }
    }
    for (CL_base* subordinate_object : subordinate_objects) {
        if (subordinate_object -> get_branch_object_by_name(s_object_name)) {
            return subordinate_object -> get_branch_object_by_name(s_object_name);
        }
    }
    return nullptr;
}

CL_base* CL_base::get_object_by_name(string s_object_name)
{
    CL_base* base = this;
    while (true) {
        if (base -> get_head_object()) {
            base = base -> get_head_object();
        }
        else {
            break;
        }
    }
    if (base -> get_branch_object_by_name(s_object_name)) {
        return base -> get_branch_object_by_name(s_object_name);
    }
    return nullptr;
}

void CL_base::show_object_tree_full()
{
    CL_base* head_object = p_head_object;
    while (head_object != nullptr) {
        cout << " ";
        head_object = head_object -> p_head_object;
    }
    cout << s_object_name;
    if (object_state != 0) {
        cout << " is ready" << endl;
    }
    else {
        cout << " is not ready" << endl;
    }
    for (CL_base* subordinate_object : subordinate_objects) {
        subordinate_object -> show_object_tree_full();
    }
}

void CL_base::change_object_state(int object_state)
{
    if (object_state != 0) {
        CL_base* head_object = p_head_object;
        bool f = true;
        while (head_object != nullptr) {
            if (head_object -> object_state == 0) {
                f = false;
                break;
            }
            head_object = head_object -> p_head_object;
        }
        if (f) {
            this -> object_state = object_state;
        }
    }
    else {
        this -> object_state = 0;
        for (CL_base* subordinate_object : subordinate_objects) {
            subordinate_object -> change_object_state(0);
        }
    }
}

bool CL_base::change_head_object(CL_base* p_head_object)
{
    if (!p_head_object || !get_head_object()) {
        return false;
    }
    if (p_head_object -> get_sub_object_by_name(this -> get_object_name()) != nullptr) {
        return false;
    }
    if (this -> get_branch_object_by_name(p_head_object -> s_object_name) == p_head_object) {
        return false;
    }
    CL_base* head_object = get_head_object();
    int k = 0;
    for (CL_base* subordinate_object : head_object -> subordinate_objects) {
        if (subordinate_object == this) {
            subordinate_objects.erase(subordinate_objects.begin() + k);
            swap(head_object -> subordinate_objects[k], head_object -> subordinate_objects.back());
            head_object -> subordinate_objects.pop_back();
            break;
        }
        else {
            k++;
        }
    }
    this -> p_head_object = p_head_object;
    this -> p_head_object -> subordinate_objects.push_back(this);
    return true;
}

void CL_base::delete_sub_object_by_name(string s_object_name)
{
    if (s_object_name.empty()) {
        return;
    }
    int k = 0;
    for (CL_base* subordinate_object : subordinate_objects) {
        if (subordinate_object -> get_object_name() == s_object_name) {
            subordinate_objects.erase(subordinate_objects.begin() + k);
            delete subordinate_object;
            break;
        }
        else {
            k++;
        }
    }
}

CL_base* CL_base::get_object_by_coordinate(string coordinate)
{
    if (!coordinate.empty()) {
        CL_base* base = this;
        if (coordinate[0] == '.') {
            if (coordinate.length() == 1) {
                return this;
            }
            return get_branch_object_by_name(coordinate.substr(1));
        }
        if (coordinate[0] == '/') {
            while (true) {
                if (base -> get_head_object()) {
                    base = base -> get_head_object();
                }
                else {
                    break;
                }
            }
            if (coordinate.length() == 1) {
                return base;
            }
            if (coordinate[1] == '/') {
                return base -> get_sub_object_by_name(coordinate.substr(2));
            }
            coordinate = coordinate.substr(1);
        }
        vector<string> names;
        while (true) {
            if (coordinate.find('/') != string::npos) {
                names.push_back(coordinate.substr(0, coordinate.find('/')));
                coordinate = coordinate.substr(coordinate.find('/') + 1);
            }
            else {
                names.push_back(coordinate);
                break;
            }
        }
        for (string name : names) {
            base = base -> get_sub_object_by_name(name);
            if (!base) {
                break;
            }
        }
        return base;
    }
    return nullptr;
}

void CL_base::set_connect(TYPE_SIGNAL p_signal, CL_base* p_target, TYPE_HANDLER p_handler)
{
    for (connection* value : connects) {
        if (value -> p_signal == p_signal && value -> p_target == p_target && value -> p_handler == p_handler) {
            return;
        }
    }
    connection* value = new connection();
    value -> p_signal = p_signal;
    value -> p_target = p_target;
    value -> p_handler = p_handler;
    connects.push_back(value);
}

void CL_base::delete_connect(TYPE_SIGNAL p_signal, CL_base* p_target, TYPE_HANDLER p_handler)
{
    bool f = false;
    int index = 0;
    connection* del;
    for (connection* value : connects) {
        if (value -> p_signal == p_signal && value -> p_target == p_target && value -> p_handler == p_handler) {
            f = true;
            del = value;
            break;
        }
        else {
            index++;
        }
    }
    if (f) {
        connects.erase(connects.begin() + index);
        delete del;
    }
}

void CL_base::emit_signal(TYPE_SIGNAL p_signal, string& message)
{
    if (object_state == 0) {
        return;
    }
    TYPE_HANDLER p_handler;
    CL_base* p_target;
    (this ->* p_signal)(message);
    for (connection* value : connects) {
        if (value -> p_signal == p_signal) {
            p_target = value -> p_target;
            p_handler = value -> p_handler;
            if (p_target -> object_state != 0) {
                (p_target ->* p_handler)(message);
            }
        }
    }
}

string CL_base::get_absolute_coordinate()
{
    CL_base* object = this;
    string absolute = "";
    while (object -> get_head_object()) {
        absolute = "/" + object -> get_object_name() + absolute;
        object = object -> get_head_object();
    }
    if (absolute.empty()) {
        return "/";
    }
    return absolute;
}

void CL_base::activate()
{
    change_object_state(1);
    for (CL_base* subordinate_object : subordinate_objects){
        subordinate_object -> activate();
    }
}

vector <CL_base*> CL_base::get_subordinate_objects()
{
    return subordinate_objects;
}
