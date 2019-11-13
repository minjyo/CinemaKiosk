//
//  System.c
//  CinemaKiosk
//
//  Created by minjyo on 12/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//
#include "Header.hpp"

Admin::Admin() {
	ticketHead = NULL;
	ticketTail = NULL;
}

//영화 리스트 출력
void Admin::printInfoTable(void) {
	for (int i = 0; i < MOVIE_INFO_ARR_SIZE; i++) {
		infoTable[i]->printInfo();
	}
}

//영화관 선택 시 시작시간 순으로 상영영화 출력
void Admin::printTimetable(short index) {
	roomTable[index]->printTimeTable();
}

//영화 정보 만들기
void Admin::createMovieInfo() {
	string title, pd;
	short runningTime, price;

	cout << "영화 정보를 입력해주세요." << endl;
	cout << "영화 제목: ";
	cin >> title;
	cout << "영화 감독: ";
	cin >> pd;
	cout << "러닝타임: ";
	cin >> runningTime;
	cout << "영화 가격: ";
	cin >> price;

	MovieInfo movie(title, pd, runningTime, price);

	if (maxIndex + 1 >= MOVIE_INFO_ARR_SIZE) {
		cout << "최대 영화 개수를 넘었습니다." << endl;
		return;
	}
	else {
		infoTable[maxIndex + 1] = &movie;
		maxIndex++;
		cout << "영화가 추가되었습니다.";
	}
}

//영화 정보 삭제하면서 해당 상영영화 모두 삭제
void Admin::deleteMovieInfo(MovieInfo* info) {

}

//영화관 사용 가능, 불가능
void Admin::setMovieRoomStatus(MovieRoom& room, bool status) {
	room.setStatus(status);
	cout << "해당 영화관 사용이 " << (status ? "가능" : "불가능") << "으로 변경되었습니다." << endl;
}

//영화관 내 상영영화 Linked List에 시간 검사 후 생성하기 (movie room의 canaddmovie + addmovie 호출)
void Admin::addMovie(MovieInfo* info, MovieRoom& room, short selectTime) {
	if (room.canAddMovie(info, selectTime)) {
		room.addMovieToRoom(info, selectTime);
		cout << "영화가 추가되었습니다." << endl;
		room.printTimeTable();
		return;
	}
	cout << "해당 시간에 영화를 추가할 수 없습니다. 다시 선택해주세요." << endl;
}

//티켓 테이블에서 티켓번호로 티켓 정보 찾기
Ticket* Admin::findTicket(int tNumber) {
	Ticket* temp = ticketHead;

	while (ticketHead->nextTicket != ticketTail) {
		if (temp->ticketNumber == tNumber) {
			return temp;
		}
		temp = temp->nextTicket;
	}

	return NULL;
}

//예매 번호로 티켓 정보 출력
void Admin::printTicket(int tNumber) {
	Ticket* temp = findTicket(tNumber);

	if (temp != NULL) {
		temp->printTicket();
		return;
	}
	cout << "해당 번호로 예매된 예매 정보가 없습니다." << endl;
}

//예매
void Admin::addTicket(MoviePlay* movie) {

}

//예매 번호로 티켓 삭제 (예매취소)
void Admin::deleteTicket(int tNumber) {

}