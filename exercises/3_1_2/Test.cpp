#include "Test.h"

Test::Test(int i)
{
	mass = new int[i];
	for (int j = 0; j < i; j++)
	{
		mass[j] = i;
	}
}

int *Test::get_mass()
{
	return (mass);
}

void Test::change_mass(int *x)
{
	mass = x;
}

void Test::output()
{
	for (int j = 0; j < mass[0] - 1; j++)
	{
		cout << mass[j] << "  ";
	}

	cout << mass[0];
}

Test::~Test()
{
	delete[] mass;
}
