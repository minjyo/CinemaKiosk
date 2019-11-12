#include "Header.hpp"
#include <iostream>

using namespace std;

int main(void) {
	MovieInfo Joc("Á¶Ä¿", "kjs", 130, 1000);
	MoviePlay mov(1330, &Joc, NULL);
	mov.printSeat();
	mov.changeSeat(1, 1, true);
	mov.changeSeat(3, 1, true);
	cout << mov.restSeat() << endl;
} 