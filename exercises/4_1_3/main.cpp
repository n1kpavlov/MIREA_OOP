#include <stdlib.h>
#include <stdio.h>
#include "Class_8.h"

int main()
{
	Class_8 * obj;
	string s;
	cin >> s;
	obj = new Class_8(s);
	cout << ((Class_1*)((Class_2*)(Class_6*) obj))->get() << endl;
	cout << ((Class_1*)((Class_3*)(Class_6*) obj))->get() << endl;
	cout << ((Class_1*)((Class_4*)(Class_7*) obj))->get() << endl;
	cout << ((Class_1*)((Class_5*)(Class_7*) obj))->get() << endl;
	cout << ((Class_2*)(Class_6*) obj)->get() << endl;
	cout << ((Class_3*)(Class_6*) obj)->get() << endl;
	cout << ((Class_4*)(Class_7*) obj)->get() << endl;
	cout << ((Class_5*)(Class_7*) obj)->get() << endl;
	cout << ((Class_6*) obj)->get() << endl;
	cout << ((Class_7*) obj)->get() << endl;
	cout << obj->get();
}
