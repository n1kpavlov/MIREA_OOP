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
	void input();
	int sum();
	int metod1();
	int metod2();
	~Test();
};


#endif
