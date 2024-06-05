#include "Test.h"

Test::Test(int i_data)
{
	open = i_data;
	close = i_data * 3;
}

void Test::change_open_close()
{
	open += 4;
	close++;
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
	open += 7;
	close += 5;
}
