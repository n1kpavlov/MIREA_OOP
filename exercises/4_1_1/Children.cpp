#include "Children.h"

Children::Children(int x, int y): Parent(x, y)
{
	close = x;
	open = y;
}

void Children::set(int x, int y)
{
	close = x;
	open = y;
}

void Children::output()
{
	cout << close << "    " << open << endl;
}
