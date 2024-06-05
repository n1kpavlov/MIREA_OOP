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
	mass = new int[n];
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

void Test::input()
{
	for (int i = 0; i < n; i++)
	{
		cin >> mass[i];
	}
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

int Test::metod1()
{
	for (int i = 0; i < n; i += 2)
	{
		mass[i] += mass[i + 1];
	}
	return sum();
}

int Test::metod2()
{
	for (int i = 0; i < n; i += 2)
	{
		mass[i] *= mass[i + 1];
	}
	return sum();
}

Test::~Test()
{
	delete[] mass;
	cout << "Destructor" << endl;
}
