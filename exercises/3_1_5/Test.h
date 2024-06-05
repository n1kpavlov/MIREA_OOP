#ifndef __TEST__H
#define __TEST__H
#include <iostream>

using namespace std;

class Test
{
private:
	int n;
	int *mass;
public:
	Test();
	Test(int x);
	Test(const Test &ob);
	void new_mass();
	void input();
	void output();
	int sum();
	void metod1();
	void metod2();
	int *get_mass();
	void put_mass(int *arr);
	~Test();
};


#endif
