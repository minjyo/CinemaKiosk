#include "Header.hpp"

MovieRoom::MovieRoom(char roomNumber) {
	//list<MoviePlay> movielist;
	head = new MoviePlay();
	head->nextPlay = NULL;
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

	cout << "------------------- " << (int)roomNumber << "�� -------------------" << endl;
	cout << "       ��ȭ ����       ��ȭ ����       ����Ÿ��        " << endl;
	cout.fill(' ');
	cout.width(10);

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		temp->info->printInfo();
		cout << endl;
		cout << temp->startTime << temp->endTime;
	}
}


//��ȭ ���� ���� ���� Ȯ�� (�̶�, �������� �������� ���� �� ��带 return ���ش�.)
MoviePlay* MovieRoom::canAddMovie(MovieInfo* info, short select) {
	MoviePlay* temp = head;
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

	//MoviePlay* temp = head->nextPlay;

	//if (head->nextPlay->select > endTime) {
	//	return head;
	//}
	int i = 0;
	if (movieCount == 0) {
		return head;
	}
	else {
		//temp = temp->nextPlay;
		//count�� ���� ���ִ� ��ȭ�� ����
		while (i < movieCount) {
			//���� �߰����� ��ȭ�� �� �� ���� ��
			if (temp->endTime < select && endTime < temp->nextPlay->startTime) {
				return temp;
			}
			//������ �׳� pass, temp�� ���� ��ȭ�� �Ѱܹ���.
			/*else if (temp->endTime > select || temp->nextPlay->startTime < endTime) {
				temp = temp->nextPlay;

				return NULL;
			}*/
			else {
				temp = temp->nextPlay;
				i++;
			}
		}
		if (i == movieCount) {
			if (temp->endTime < select) {
				return temp;
			}
		}
		return NULL;
	}
}

void MovieRoom::addMovieToRoom(MovieInfo* info, short select) {
	MoviePlay* prevmov = canAddMovie(info, select);
	/*MoviePlay(short sTime, MovieInfo * minfo, MoviePlay * nextP)*/
	//temp�� �������� ��ȭ���� ������ �־��ش�.

	if (prevmov == NULL) {
		cout << "��ȭ�� ���� �� �ִ� �ð��� �����ϴ�." << endl;
	}
	else {
		MoviePlay* temp = new MoviePlay(select, info, prevmov->nextPlay);
		temp->nextPlay = prevmov->nextPlay;
		prevmov->nextPlay = temp;
		movieCount++;
	}
}