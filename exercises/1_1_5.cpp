#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	if (N >= 1 && N <= 9)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= i - 1; j++)
			{
				cout << j << " ";
			}

			cout << i;
			if (i != N)
			{
				cout << endl;
			}
		}
	}
	else
	{
		cout << "N is wrong: " << N << endl;
	}
}
