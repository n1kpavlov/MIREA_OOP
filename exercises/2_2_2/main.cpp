#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

int main()
{
	int i_data;
	cin >> i_data;
	Test *a = new Test(i_data);
	a->output();
	a->change_open_close();
	a->output();
	cin >> i_data;
	if (i_data > a->open)
	{
		a->open = i_data * 8;
	}

	a->output();
	a->call_private();
	a->output();
	delete[] a;
	return (0);
}
