#include "Test.h"

Test::Test(int i)
{
	mass = new int[i];
	for (int j = 0; j < i; j++)
	{
		mass[j] = i;
	}
}

void Test::output()
{
	for (int j = 0; j < mass[0] - 1; j++)
	{
		cout << mass[j] << "  ";
	}

	cout << mass[0];
}
