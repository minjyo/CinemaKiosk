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

//영화관의 영화 타임 테이블 출력
void MovieRoom::printTimeTable() {
	MoviePlay* temp = head;

	int Count = 1;
	cout << setw(6) << " ";
	cout << "--------------------------------- " << (int)roomNumber + 1 << "관 ---------------------------------" << endl;
	cout.setf(ios::left);
	cout << setw(6) << " ";
	cout << setw(20) << "영화 제목";
	cout << setw(20) << "시작 시간";
	cout << setw(20) << "종료 시간";
	cout << setw(20) << "잔여 좌석" << endl;

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		cout << setw(6) << to_string(Count) + ".";
		cout << setw(20) << temp->info->getInfo().title;
		cout << setw(20) << to_string((temp->startTime / 100) % 24) + "시 " + to_string(temp->startTime % 100) + "분";
		cout << setw(20) << to_string((temp->endTime / 100) % 24) + "시 " + to_string(temp->endTime % 100) + "분";
		cout << temp->restSeat() << "/25" << endl;
		Count++;
	}
	cout << endl;
}

//영화 삽입 가능 여부 확인 (이때, 넣으려는 곳의 앞 노드의 index를 리턴해준다) 근영수정
int MovieRoom::canAddMovie(MovieInfo* info, short select) {
	MoviePlay* temp = head->nextPlay;
	unsigned short runningTime = info->getInfo().runningTime;
	unsigned short endTime = 0;
	//시간을 입력시 주의사항은 분 단위가 아닌 시와 분을 둘다 써줄것.
	//Ex) 90분 영화면 1시간 30분이므로 130 이라고 써줄것.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60분 빼고 1시간 더하니까 40을 더함 */
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
		cout << "영화를 넣을 수 있는 시간이 없습니다." << endl;
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

//1125 근영 수정/추가 삭제하는 영화 개수는 확인용, 지워도 무방
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
	cout << "삭제가 완료되었습니다!" << endl;
	this->movieCount -= deleteCount;
}

//1125 근영 추가 일치하는 영화 개수는 확인용, 지워도 무방
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
		cout << "--------------------------------- " << (int)roomNumber + 1 << "관 ---------------------------------" << endl;
		cout << setw(6) << " ";
		cout << setw(20) << "시작 시간";
		cout << setw(20) << "종료 시간";
		cout << setw(20) << "잔여 좌석" << endl;
		Count = 1;
		while (temp != NULL) {
			if (temp->info == mov) {
				cout << setw(6) << to_string(Count) + ".";
				cout << setw(20) << to_string((temp->startTime / 100) % 24) + "시 " + to_string(temp->startTime % 100) + "분";
				cout << setw(20) << to_string((temp->endTime / 100) % 24) + "시 " + to_string(temp->endTime % 100) + "분";
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
	cout << "삭제가 완료되었습니다!" << endl;
}