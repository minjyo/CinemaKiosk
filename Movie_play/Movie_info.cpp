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
	cout << "��ȭ���� �����ðڽ��ϱ�? Y/N" << endl;
	cin >> check;
	if (check == 'Y') {
		state = true;
	}
	else if (check == 'N') {
		state = false;
	}
	else
		cout << "�߸��� �Է��Դϴ�!" << endl;
}