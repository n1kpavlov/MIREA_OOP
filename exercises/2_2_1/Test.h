#ifndef __TEST__H
#define __TEST__H
#include <iostream>

using namespace std;

class Test
{
private:
	int close;
	void hide();
public:
	int open;
	Test(int i_data);
	void change_open_close();
	void call_private();
	void output();
};
