#ifndef __TEST__H
#define __TEST__H
#include <iostream>

using namespace std;

class Test
{
private:
	int *mass;
public:
	Test(int i);
	~Test();
	int *get_mass();
	void change_mass(int *x);
	void output();
};

#endif
