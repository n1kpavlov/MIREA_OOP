#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Parent.h"
#include "Children.h"

using namespace std;

int main()
{
	int x, y;
	cin >> x >> y;
	Children children(x, y);
	children.Parent::output();
	children.output();
	if (x > 0)
	{
		children.set(x + 1, y + 1);
		children.Parent::set(x - 1, y - 1);
		children.output();
		children.Parent::output();
	}
	else
	{
		children.Parent::set(x + 1, y + 1);
		children.set(x - 1, y - 1);
		children.Parent::output();
		children.output();
	}
}
