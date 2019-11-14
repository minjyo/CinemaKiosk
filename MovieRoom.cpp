#include "Header.hpp"

MovieRoom::MovieRoom(char roomNumber) {
	head = NULL;
	this->roomNumber = roomNumber;
	this->status = false;
	this->movieCount = 0;
}

void MovieRoom::setStatus(bool status) {
	this->status = status;
}

MovieRoom::~MovieRoom() {

}

//��ȭ���� ��ȭ Ÿ�� ���̺� ���
void MovieRoom::printTimeTable() {
	MoviePlay* temp = head;

	cout << "------------------- " << roomNumber << "�� -------------------" << endl;
	cout << "       ��ȭ ����       ��ȭ ����       ����Ÿ��        " << endl;
	cout.fill(' ');
	cout.width(10);

	while (temp->nextPlay != NULL) {
		temp->info->printInfo();
		temp = temp->nextPlay;
	}
}


//��ȭ ���� ���� ���� Ȯ�� (�̶�, �������� �������� ���� �� ��带 return ���ش�.)
MoviePlay* canAddMovie(MovieInfo* info, short select) {
	MoviePlay* head = NULL;
	unsigned short runningTime = info->getInfo.runningTime;
	unsigned short endTime;
	//�ð��� �Է½� ���ǻ����� �� ������ �ƴ� �ÿ� ���� �Ѵ� ���ٰ�.
	//Ex) 90�� ��ȭ�� 1�ð� 30���̹Ƿ� 130 �̶�� ���ٰ�.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60�� ���� 1�ð� ���ϴϱ� 40�� ���� */
		endTime += 40;
	}
	else {
		endTime = select + runningTime;
	}
	MoviePlay* temp = head->nextPlay;

	if (head->nextPlay->startTime > endTime) {
		return head;
	}
	int i = 0;
	//count�� �� ��ȭ���� �� �� �ִ� ��ȭ ���� �ִ�
	while (i < count - 1) {
		if (temp->endTime <= select && temp->nextPlay->startTime >= endTime) {
			return temp;
		}

		else if (temp->endTime > select || temp->nextPlay->startTime < endTime) {
			temp = temp->nextPlay;
			 
			return NULL;
		}
	}
}

void MovieRoom::addMovieToRoom(MovieInfo* info, short select) {
	MoviePlay* temp;

	//temp�� �������� ��ȭ���� ������ �־��ش�.
	temp->startTime = select;
	temp->info = info;

	if (canAddMovie(info, select) == NULL) {
		cout << "��ȭ�� ���� �� �ִ� �ð��� �����ϴ�." << endl;
	}

	else {
		temp->nextPlay = canAddMovie(info, select)->nextPlay;
		canAddMovie(info, select)->nextPlay = temp;
	}
}