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

	int Count = 1;
	cout << "   ";
	cout << "--------------------------------- " << (int)roomNumber + 1 << "�� ---------------------------------" << endl;
	cout << "   ";
	cout.setf(ios::left);
	cout << setw(20) << "��ȭ ����";
	cout << setw(20) << "���� �ð�";
	cout << setw(20) << "���� �ð�";
	cout << setw(20) << "�ܿ� �¼�";

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		/*temp->info->printInfo();
		cout << temp->startTime;
		cout << temp->restSeat();*/
		cout << Count << ". ";
		cout << setw(20) << temp->info->title;
		string start_string = to_string(temp->startTime / 100) + "�� " + to_string(temp->startTime % 100) + "��";
		string end_string = to_string(temp->endTime / 100) + "�� " + to_string(temp->endTime % 100) + "��";
		cout << setw(20) << start_string;
		cout << setw(20) << end_string;
		cout << temp->restSeat() << "/25" << endl;
		Count++;
	}
	cout << endl;
}

//��ȭ ���� ���� ���� Ȯ�� (�̶�, �������� �������� ���� �� ��带 return ���ش�.)
MoviePlay* MovieRoom::canAddMovie(MovieInfo* info, short select) {
	//list <MoviePlay>::iterator index = movielist.begin();
	MoviePlay* temp = head->nextPlay;
	unsigned short runningTime = info->runningTime;
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
		//temp->nextPlay = prevmov->nextPlay;
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

int MovieRoom::printMovieInfo(MovieInfo* mov) {

	MoviePlay* start = head;
	MoviePlay* temp = start->nextPlay;

	int Count = 0;

	while (temp != NULL) {
		if (temp->info == mov) {
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
		cout << "   ";
		cout << "--------------------------------- " << (int)roomNumber + 1 << "�� ---------------------------------" << endl;
		cout << "   ";
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "���� �ð�";
		cout << setw(20) << "�ܿ� �¼�" << endl;
		Count = 1;
		while (temp != NULL) {
			if (temp->info == mov) {
				//Info movieinfo = temp->info->getInfo();
				cout << Count << ". ";
				string start_string = to_string(temp->startTime / 100) + "�� " + to_string(temp->startTime % 100) + "��";
				string end_string = to_string(temp->endTime / 100) + "�� " + to_string(temp->endTime % 100) + "��";
				cout << setw(20) << start_string;
				cout << setw(20) << end_string;
				cout << temp->restSeat() << " / "<< SIZE_COLUMN*SIZE_ROW << endl;
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
	return Count;

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