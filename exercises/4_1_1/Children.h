#ifndef __CHILDREN__H
#define __CHILDREN__H
#include <iostream>
#include "Parent.h"

using namespace std;

class Children: public Parent
{
private:
	int close;
public:
	int open;
	Children(int x, int y);
	void set(int x, int y);
	void output();
};

#endif
