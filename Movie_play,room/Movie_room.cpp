#include <iostream>

using namespace std;

class Movie_room {
private:
	bool state = false;
public:
	Movie_room();
	void setState();
	unsigned short room_number;
};

void Movie_room::setState() {
	char check;
	cout << "영화관을 막으시겠습니까? Y/N" << endl;
	cin >> check;
	if (check == 'Y') {
		state = true;
	}
	else if (check == 'N') {
		state = false;
	}
	else
		cout << "잘못된 입력입니다!" << endl;
}