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

//영화관의 영화 타임 테이블 출력
void MovieRoom::printTimeTable() {
	MoviePlay* temp = head;

	cout << "------------------- " << roomNumber << "관 -------------------" << endl;
	cout << "       영화 제목       영화 감독       러닝타임        " << endl;
	cout.fill(' ');
	cout.width(10);

	while (temp->nextPlay != NULL) {
		temp->info->printInfo();
		temp = temp->nextPlay;
	}
}


//영화 삽입 가능 여부 확인 (이때, 마지막에 넣으려는 곳의 전 노드를 return 해준다.)
MoviePlay* canAddMovie(MovieInfo* info, short select) {
	MoviePlay* head = NULL;
	unsigned short runningTime = info->getInfo.runningTime;
	unsigned short endTime;
	//시간을 입력시 주의사항은 분 단위가 아닌 시와 분을 둘다 써줄것.
	//Ex) 90분 영화면 1시간 30분이므로 130 이라고 써줄것.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60분 빼고 1시간 더하니까 40을 더함 */
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
	//count는 한 영화관에 들어갈 수 있는 영화 수의 최댓값
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

	//temp에 넣으려는 영화들의 정보를 넣어준다.
	temp->startTime = select;
	temp->info = info;

	if (canAddMovie(info, select) == NULL) {
		cout << "영화를 넣을 수 있는 시간이 없습니다." << endl;
	}

	else {
		temp->nextPlay = canAddMovie(info, select)->nextPlay;
		canAddMovie(info, select)->nextPlay = temp;
	}
}