#include "Test.h"

Test::Test(int i_data)
{
	open = i_data;
	close = i_data * 2;
}

void Test::change_open_close()
{
	open++;
	close += 4;
}

void Test::call_private()
{
	hide();
}

void Test::output()
{
	cout << "Value of the available property " << open << "; Value of a hidden
	property " << close << endl;
}

void Test::hide()
{
	open += 5;
	close += 7;
}
