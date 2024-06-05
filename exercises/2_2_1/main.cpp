#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

int main()
{
	int i_data;
	cin >> i_data;
	Test a(i_data);
	a.output();
	a.change_open_close();
	a.output();
	cin >> i_data;
	a.open *= i_data;
	a.output();
	a.call_private();
	a.output();
	return (0);
}
