#include "Header.hpp"


MoviePlay::MoviePlay(short sTime, MovieInfo* minfo, MoviePlay* nextP) {
	//this->seat[SIZE_ROW][SIZE_COLUMN] = { false, };
	Info temp = minfo->getInfo();
	unsigned short running_time = temp.runningTime;

	/* ���� ���� 60���� ������ */
	if (((sTime % 100) + (running_time % 100)) > 60) {
		/* 60�� ���� 1�ð� ���ϴϱ� 40�� ���� */
		this->endTime += 40;
	}
	else {
		this->endTime = sTime + running_time;
	}
	this->info = minfo;
	//this->nextPlay = nextP;
	nextPlay = NULL;
	this->startTime = sTime;
}

MoviePlay::~MoviePlay() {
}

//�¼� ��Ȳ ���. ���� �����ϸ� ��, �ȵǸ� ��
void MoviePlay::printSeat() {
	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COLUMN; j++) {
			if (seat[i][j] == true)
				cout << "��";
			else
				cout << "��";
		}
		cout << endl;
	}
}

//�ش� ��ǥ�� �ִ� �¼��� ���� �������� ����. �ڸ��� �̹� ����Ǿ� ������ True, �׷��� ���� ��� False ����.
bool MoviePlay::checkSeat(short x, short y) {
	if (x > 5 || y > 5 || x < 1 || y < 1) {
		cout << "�߸��� �Է��Դϴ�" << endl;
	}
	else {
		if (seat[x - 1][y - 1] == true) {
			return true;
		}
		else if (seat[x - 1][y - 1] == false) {
			return false;
		}
	}
	return false;
}

//������ ���� status True, ����Ҷ��� Status False.
void MoviePlay::changeSeat(short x, short y, bool status) {
	if (x > 5 || y > 5 || x < 1 || y < 1) {
		cout << "�߸��� �Է��Դϴ�" << endl;
	}
	else {

		if (status == true) {
			if (checkSeat(x, y) == true) {
				cout << "�¼��� á���ϴ�." << endl;
			}
			else {
				seat[x - 1][y - 1] = true;
				cout << "�¼� ���� �Ϸ�" << endl;
			}
		}
		else {
			if (checkSeat(x, y) == false) {
				cout << "�¼��� ����� ���°� �ƴմϴ�." << endl;
			}
			else {
				seat[x - 1][y - 1] = false;
				cout << "�¼� ��� �Ϸ�" << endl;
			}
		}
		printSeat();
	}

}

//���� ������ ���ڸ� ����.
unsigned short MoviePlay::restSeat() {
	unsigned short count = 0;
	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COLUMN; j++) {
			if (seat[i][j] == false) {
				count++;
			}
		}
	}
	return count;
}