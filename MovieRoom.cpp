#include "Header.hpp"

MovieRoom::MovieRoom(char roomNumber) {
	head = new MoviePlay();
	head->nextPlay = NULL;
	this->roomNumber = roomNumber;
	this->status = true;
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

	int Count = 1;
	cout << setw(6) << " ";
	cout << "--------------------------------- " << (int)roomNumber + 1 << "�� ---------------------------------" << endl;
	cout.setf(ios::left);
	cout << setw(6) << " ";
	cout << setw(20) << "��ȭ ����";
	cout << setw(20) << "���� �ð�";
	cout << setw(20) << "���� �ð�";
	cout << setw(20) << "�ܿ� �¼�" << endl;

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		cout << setw(6) << to_string(Count) + ".";
		cout << setw(20) << temp->info->getInfo().title;
		cout << setw(20) << to_string((temp->startTime / 100) % 24) + "�� " + to_string(temp->startTime % 100) + "��";
		cout << setw(20) << to_string((temp->endTime / 100) % 24) + "�� " + to_string(temp->endTime % 100) + "��";
		cout << temp->restSeat() << "/25" << endl;
		Count++;
	}
	cout << endl;
}

//��ȭ ���� ���� ���� Ȯ�� (�̶�, �������� ���� �� ����� index�� �������ش�) �ٿ�����
int MovieRoom::canAddMovie(MovieInfo* info, short select) {
	MoviePlay* temp = head->nextPlay;
	unsigned short runningTime = info->getInfo().runningTime;
	unsigned short endTime = 0;
	//�ð��� �Է½� ���ǻ����� �� ������ �ƴ� �ÿ� ���� �Ѵ� ���ٰ�.
	//Ex) 90�� ��ȭ�� 1�ð� 30���̹Ƿ� 130 �̶�� ���ٰ�.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60�� ���� 1�ð� ���ϴϱ� 40�� ���� */
		endTime = select + runningTime + 40;
	}
	else {
		endTime = select + runningTime;
	}
	int select_index = 1;
	if (this->movieCount == 0 || head->nextPlay->startTime > endTime) {
		return 0;
	}
	else {
		while (temp->nextPlay != NULL) {
			if (temp->endTime < select && endTime < temp->nextPlay->startTime) {
				return select_index;
			}
			else {
				temp = temp->nextPlay;
				select_index++;
			}
		}
		if (temp->endTime < select) {
			return select_index;
		}
		else
			return -1;
	}
}

bool MovieRoom::addMovieToRoom(MovieInfo* info, short select) {
	int select_index = canAddMovie(info, select);
	if (select_index == -1) {
		cout << "��ȭ�� ���� �� �ִ� �ð��� �����ϴ�." << endl;
		return FALSE;
	}
	else {
		int search_index = 0;
		MoviePlay* temp = head;
		while (search_index != select_index) {
			temp = temp->nextPlay;
			search_index++;
		}
		MoviePlay* insertMovie = new MoviePlay(select, info, temp->nextPlay);
		insertMovie->nextPlay = temp->nextPlay;
		temp->nextPlay = insertMovie;
		this->movieCount++;
		return TRUE;
	}
}

//1125 �ٿ� ����/�߰� �����ϴ� ��ȭ ������ Ȯ�ο�, ������ ����
void MovieRoom::deleteMovieInfo(MovieInfo* mov) {

	MoviePlay* start = head;
	MoviePlay* temp = start->nextPlay;

	int deleteCount = 0;

	while (temp != NULL) {
		if (temp->info == mov) {
			start->nextPlay = temp->nextPlay;
			temp ->~MoviePlay();
			temp = start->nextPlay;
			deleteCount++;
		}
		else {
			start = temp;
			temp = start->nextPlay;
		}
	}
	cout << "������ �Ϸ�Ǿ����ϴ�!" << endl;
	this->movieCount -= deleteCount;
}

//1125 �ٿ� �߰� ��ġ�ϴ� ��ȭ ������ Ȯ�ο�, ������ ����
void MovieRoom::printMovieInfo(MovieInfo* mov) {

	MoviePlay* start = head;
	MoviePlay* temp = start->nextPlay;

	int Count = 0;

	while (temp != NULL) {
		if (temp->info == mov) {
			Info movieinfo = temp->info->getInfo();
			start = temp;
			temp = start->nextPlay;
			Count++;
		}
		else {
			start = temp;
			temp = start->nextPlay;
		}
	}

	if (Count != 0) {
		temp = head->nextPlay;
		cout << setw(6) << " ";
		cout << "--------------------------------- " << (int)roomNumber + 1 << "�� ---------------------------------" << endl;
		cout << setw(6) << " ";
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "�ܿ� �¼�" << endl;
		Count = 1;
		while (temp != NULL) {
			if (temp->info == mov) {
				cout << setw(6) << to_string(Count) + ".";
				cout << setw(20) << to_string((temp->startTime / 100) % 24) + "�� " + to_string(temp->startTime % 100) + "��";
				cout << setw(20) << to_string((temp->endTime / 100) % 24) + "�� " + to_string(temp->endTime % 100) + "��";
				cout << temp->restSeat() << "/25" << endl;
				start = temp;
				temp = start->nextPlay;
				Count++;
			}
			else {
				start = temp;
				temp = start->nextPlay;
			}
		}
	}
}

MoviePlay* MovieRoom::findMoviePlay(MovieInfo* minfo, int index) {

	MoviePlay* temp = head->nextPlay;
	int compareIndex = 1;
	while (temp != NULL) {
		if (temp->info == minfo) {
			if (compareIndex == index)
				return temp;
			else {
				temp = temp->nextPlay;
				compareIndex++;
			}
		}
		else {
			temp = temp->nextPlay;
		}
	}
	return NULL;
}

void MovieRoom::deleteMoviePlay(short starttime) {

	MoviePlay* start = head;
	MoviePlay* temp = start->nextPlay;

	while (temp != NULL) {
		if (temp->startTime == starttime) {
			start->nextPlay = temp->nextPlay;
			temp ->~MoviePlay();
			temp = start->nextPlay;
		}
		else {
			start = temp;
			temp = start->nextPlay;
		}
	}
	this->movieCount--;
	cout << "������ �Ϸ�Ǿ����ϴ�!" << endl;
}