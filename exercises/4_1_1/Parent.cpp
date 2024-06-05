#include "Parent.h"

Parent::Parent(int x, int y)
{
	change(x);
	open = y;
}

void Parent::change(int x)
{
	close = 2 * x;
}

void Parent::set(int x, int y)
{
	change(x);
	open = y;
}

void Parent::output()
{
	cout << close << "    " << open << endl;
}
