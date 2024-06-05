#ifndef __PARENT__H
#define __PARENT__H
#include <iostream>

using namespace std;

class Parent
{
private:
	int close;
	void change(int x);
public:
	int open;
	Parent(int x, int y);
	void set(int x, int y);
	void output();

};

#endif
