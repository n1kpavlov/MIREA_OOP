#include "Test.h"

using namespace std;

Test::Test()
{
	cout << "Default constructor" << endl;
}

Test::Test(int x)
{
	cout << "Constructor set" << endl;
	n = x;
}

Test::Test(const Test &ob)
{
	cout << "Copy constructor" << endl;
	n = ob.n;
	mass = new int[n];
	for (int i = 0; i < n; i++)
	{
		mass[i] = ob.mass[i];
	}
}

void Test::new_mass()
{
	mass = new int[n];
}

void Test::input()
{
	for (int i = 0; i < n; i++)
	{
		cin >> mass[i];
	}
}

void Test::output()
{
	for (int i = 0; i < n - 1; i++)
	{
		cout << mass[i] << "  ";
	}
	cout << mass[n - 1] << endl;

}

int Test::sum()
{
	int summ = 0;
	for (int i = 0; i < n; i++)
	{
		summ += mass[i];
	}
	return (summ);
}

void Test::metod1()
{
	for (int i = 0; i < n; i += 2)
	{
		mass[i] += mass[i + 1];
	}
}

void Test::metod2()
{
	for (int i = 0; i < n; i += 2)
	{
		mass[i] *= mass[i + 1];
	}
}

int *Test::get_mass()
{
	return mass;
}

void Test::put_mass(int *arr)
{
	mass = arr;
}

Test::~Test()
{
	cout << "Destructor" << endl;
}
