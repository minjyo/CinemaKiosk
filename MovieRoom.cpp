#include "Header.hpp"

MovieRoom::MovieRoom(unsigned short roomNumber) {
	head = new MoviePlay();
	head->nextPlay = NULL;
	this->roomNumber = roomNumber;
	this->movieCount = 0;
}

MovieRoom::~MovieRoom() {

}

// 영화관의 영화 타임 테이블 출력
void MovieRoom::printTimeTable() {
	MoviePlay* temp = head;

	int Count = 1;
	cout << setw(6) << " ";
	cout << "--------------------------------- " << roomNumber + 1 << "관 ---------------------------------" << endl;
	cout.setf(ios::left);
	cout << setw(6) << "■";
	cout << setw(20) << "영화 제목";
	cout << setw(20) << "시작 시간";
	cout << setw(20) << "종료 시간";
	cout << setw(20) << "잔여 좌석" << endl;

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		cout << setw(3) << "■";
		cout << setw(3) << to_string(Count) + ".";
		cout << setw(20) << temp->info->title;
		cout << setw(20) << to_string((temp->startTime / 100) % 24) + "시 " + to_string(temp->startTime % 100) + "분";
		cout << setw(20) << to_string((temp->endTime / 100) % 24) + "시 " + to_string(temp->endTime % 100) + "분";
		cout << temp->restSeat() << " / " << SIZE_COLUMN * SIZE_ROW << endl;
		Count++;
	}
	cout << endl;
}

// 해당 관 안에서 특정 영화만 출력
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
		cout << setw(6) << "■";
		cout << "--------------------------------- " << roomNumber + 1 << "관 ---------------------------------" << endl;
		cout << setw(6) << "■";
		cout << setw(20) << "시작 시간";
		cout << setw(20) << "종료 시간";
		cout << setw(20) << "잔여 좌석" << endl;
		Count = 1;
		while (temp != NULL) {
			if (temp->info == mov) {
				cout << setw(3) << "■";
				cout << setw(3) << to_string(Count) + ".";
				cout << setw(20) << to_string((temp->startTime / 100) % 24) + "시 " + to_string(temp->startTime % 100) + "분";
				cout << setw(20) << to_string((temp->endTime / 100) % 24) + "시 " + to_string(temp->endTime % 100) + "분";
				cout << temp->restSeat() << " / " << SIZE_COLUMN * SIZE_ROW << endl;
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

// 시작시간, 러닝타임으로 종료시간 리턴
unsigned short MovieRoom::getEndTime(unsigned short startTime, unsigned short runningTime) {
	unsigned short endTime = 0;
	if (((startTime % 100) + (runningTime % 100)) > 60) {
		/* 60분 빼고 1시간 더하니까 40을 더함 */
		endTime = startTime + runningTime + 40;
	}
	else {
		endTime = startTime + runningTime;
	}
	return endTime;
}

// 영화관에 영화 추가 가능하면 추가할 곳의 앞 영화 인덱스, 불가능하면 -1 리턴
int MovieRoom::canAddMovie(MovieInfo* info, unsigned short select) {
	MoviePlay* temp = head->nextPlay;
	unsigned short runningTime = info->runningTime;
	unsigned short endTime = 0;
	//시간을 입력시 주의사항은 분 단위가 아닌 시와 분을 둘다 써줄것.
	//Ex) 90분 영화면 1시간 30분이므로 130 이라고 써줄것.
	endTime = getEndTime(select, runningTime);
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

// 인덱스를 받아와서 -1이면 생성 X 그 외에는 추가해줄 곳의 앞 인덱스를 받아서 추가해줌
bool MovieRoom::addMovieToRoom(MovieInfo* info, unsigned short select) {
	int select_index = canAddMovie(info, select);
	if (select_index == -1) {
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
		insertMovie->endTime = getEndTime(select, info->runningTime);
		insertMovie->nextPlay = temp->nextPlay;
		temp->nextPlay = insertMovie;
		this->movieCount++;
		return TRUE;
	}
}

// 해당 관 안에서 상영중인 영화중 일치하는 영화 모두 삭제
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
	this->movieCount -= deleteCount;
}

// 해당 관 안에서 상영중인 특정영화 하나 삭제
int MovieRoom::deleteMoviePlay(short starttime) {

	MoviePlay* start = head;
	MoviePlay* temp = start->nextPlay;

	int deleteCount = 0;

	while (temp != NULL) {
		if (temp->startTime == starttime) {
			start->nextPlay = temp->nextPlay;
			temp ->~MoviePlay();
			deleteCount++;
			temp = start->nextPlay;
		}
		else {
			start = temp;
			temp = start->nextPlay;
		}
	}
	this->movieCount--;
	return deleteCount;
}

// 영화관에서 몇번째 상영중인 특정 영화 객체 리턴
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