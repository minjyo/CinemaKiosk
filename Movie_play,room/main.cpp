#include "Movie_play.h"
#include <iostream>
using namespace std;

int main()
{
	Movie_play test;
	test.chooseSeat();
	test.add(10);
	test.add(20);
	test.add(30);
	test.add(3, 40);
	test.remove(0);
	test.set(0, 100);

	for (int i = 0; i < test.size(); i++)
	{
		cout << "data : " << test.get(i) << endl;
	}
	cout << "size : " << test.size() << endl;
	cout << "isEmpty : " << test.isEmpty() << endl;

	test.remove(10);
	return 0;
}
