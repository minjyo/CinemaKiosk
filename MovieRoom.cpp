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

//영화관의 영화 타임 테이블 출력
void MovieRoom::printTimeTable() {
	MoviePlay* temp = head;

	int Count = 1;
	cout << "   ";
	cout << "--------------------------------- " << (int)roomNumber + 1 << "관 ---------------------------------" << endl;
	cout << "   ";
	cout.setf(ios::left);
	cout << setw(20) << "영화 제목";
	cout << setw(20) << "시작 시간";
	cout << setw(20) << "종료 시간";
	cout << setw(20) << "잔여 좌석";

	while (temp->nextPlay != NULL) {
		temp = temp->nextPlay;
		/*temp->info->printInfo();
		cout << temp->startTime;
		cout << temp->restSeat();*/
		cout << Count << ". ";
		cout << setw(20) << temp->info->getInfo().title;
		string start_string = to_string(temp->startTime / 100) + "시 " + to_string(temp->startTime % 100) + "분";
		string end_string = to_string(temp->endTime / 100) + "시 " + to_string(temp->endTime % 100) + "분";
		cout << setw(20) << start_string;
		cout << setw(20) << end_string;
		cout << temp->restSeat() << "/25" << endl;
		Count++;
	}
	cout << endl;
}

//영화 삽입 가능 여부 확인 (이때, 마지막에 넣으려는 곳의 전 노드를 return 해준다.)
MoviePlay* MovieRoom::canAddMovie(MovieInfo* info, short select) {
	//list <MoviePlay>::iterator index = movielist.begin();
	MoviePlay* temp = head->nextPlay;
	Info info_temp = info->getInfo();
	unsigned short runningTime = info_temp.runningTime;
	unsigned short endTime = 0;
	//시간을 입력시 주의사항은 분 단위가 아닌 시와 분을 둘다 써줄것.
	//Ex) 90분 영화면 1시간 30분이므로 130 이라고 써줄것.
	if (((select % 100) + (runningTime % 100)) > 60) {
		/* 60분 빼고 1시간 더하니까 40을 더함 */
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
		//count는 현재 들어가있는 영화의 개수
		while (temp != NULL) {
			if (temp->nextPlay == NULL) {
				if (temp->endTime < select) {
					return temp;
				}
				return NULL;
			}
			//새로 추가해줄 영화가 들어갈 수 있을 때
			if (temp->endTime < select && endTime < temp->nextPlay->startTime) {
				return temp;
			}
			//없으면 그냥 pass, temp를 다음 영화로 넘겨버림
			else {
				temp = temp->nextPlay;
				i++;
			}
		}
	}
}

bool MovieRoom::addMovieToRoom(MovieInfo* info, short select) {
	MoviePlay* prevmov = canAddMovie(info, select);
	//temp에 넣으려는 영화들의 정보를 넣어준다.

	if (prevmov == NULL) {
		//cout << "영화를 넣을 수 있는 시간이 없습니다." << endl;
		return FALSE;
	}
	else {
		MoviePlay* temp = new MoviePlay(select, info, prevmov->nextPlay);
		temp->nextPlay = prevmov->nextPlay;
		prevmov->nextPlay = temp;
		this->movieCount++;
		//cout << "영화 추가가 완료되었습니다." << endl;
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
		cout << "   ";
		cout << "--------------------------------- " << (int)roomNumber + 1 << "관 ---------------------------------" << endl;
		cout << "   ";
		cout << setw(20) << "시작 시간";
		cout << setw(20) << "종료 시간";
		cout << setw(20) << "잔여 좌석" << endl;
		Count = 1;
		while (temp != NULL) {
			if (temp->info == mov) {
				//Info movieinfo = temp->info->getInfo();
				cout << Count << ". ";
				string start_string = to_string(temp->startTime / 100) + "시 " + to_string(temp->startTime % 100) + "분";
				string end_string = to_string(temp->endTime / 100) + "시 " + to_string(temp->endTime % 100) + "분";
				cout << setw(20) << start_string;
				cout << setw(20) << end_string;
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
	cout << "삭제가 완료되었습니다!" << endl;

}