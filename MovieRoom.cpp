#include "Header.hpp"

MovieRoom::MovieRoom(char roomNumber) {
	//list<MoviePlay> movielist;
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

	cout << "------------------- " << (int)roomNumber + 1 << "�� -------------------" << endl;
	cout << "��ȭ ����       ���� �ð�       �ܿ��¼�        " << endl;
	cout.fill(' ');
	cout.width(10);

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		temp->info->printInfo();
		cout << temp->startTime;
		cout << temp->restSeat();
		cout << endl;
	}
}

//��ȭ ���� ���� ���� Ȯ�� (�̶�, �������� �������� ���� �� ��带 return ���ش�.)
MoviePlay* MovieRoom::canAddMovie(MovieInfo* info, short select) {
	//list <MoviePlay>::iterator index = movielist.begin();
	MoviePlay* temp = head->nextPlay;
	Info info_temp = info->getInfo();
	unsigned short runningTime = info_temp.runningTime;
	unsigned short endTime = 0;
	//�ð��� �Է½� ���ǻ����� �� ������ �ƴ� �ÿ� ���� �Ѵ� ���ٰ�.
	//Ex) 90�� ��ȭ�� 1�ð� 30���̹Ƿ� 130 �̶�� ���ٰ�.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60�� ���� 1�ð� ���ϴϱ� 40�� ���� */
		endTime += 40;
	}
	else {
		endTime = select + runningTime;
	}
	int i = 0;
	if (this->movieCount == 0) {
		return head;
	}
	else {
		//count�� ���� ���ִ� ��ȭ�� ����
		while (temp != NULL) {
			if (temp->nextPlay == NULL) {
				if (temp->endTime < select) {
					return temp;
				}
				return NULL;
			}
			//���� �߰����� ��ȭ�� �� �� ���� ��
			if (temp->endTime < select && endTime < temp->nextPlay->startTime) {
				return temp;
			}
			//������ �׳� pass, temp�� ���� ��ȭ�� �Ѱܹ���
			else {
				temp = temp->nextPlay;
				i++;
			}
		}
	}
}

bool MovieRoom::addMovieToRoom(MovieInfo* info, short select) {
	MoviePlay* prevmov = canAddMovie(info, select);
	//temp�� �������� ��ȭ���� ������ �־��ش�.

	if (prevmov == NULL) {
		//cout << "��ȭ�� ���� �� �ִ� �ð��� �����ϴ�." << endl;
		return FALSE;
	}
	else {
		MoviePlay* temp = new MoviePlay(select, info, prevmov->nextPlay);
		temp->nextPlay = prevmov->nextPlay;
		prevmov->nextPlay = temp;
		this->movieCount++;
		//cout << "��ȭ �߰��� �Ϸ�Ǿ����ϴ�." << endl;
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
		cout << "------------------- " << (int)roomNumber + 1 << "�� -------------------" << endl;
		cout.setf(ios::left);
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "�ܿ� �¼�" << endl;


		while (temp != NULL) {
			if (temp->info == mov) {
				Info movieinfo = temp->info->getInfo();
				cout << setw(20) << temp->startTime;
				cout << setw(20) << temp->endTime;
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