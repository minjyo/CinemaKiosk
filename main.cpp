//
//  main.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright Â© 2019 minjyo. All rights reserved.
//

#include "Header.hpp"
#include <iostream>
#include <list>

using namespace std;

int main()
{
	char mode = HOME;
	char input[10] = { '\0', };

	//기본 객체 생성(admin, movie, movieroom)
	Admin admin;

	//영화관 기본 셋팅

	MovieRoom r1(1);
	MovieInfo mov1("Frozen2", "director1", 146, 8000);
	MovieInfo mov2("Jocker", "director2", 120, 9000);
	r1.addMovieToRoom(&mov1, 900);
	r1.addMovieToRoom(&mov2, 1000);
	r1.addMovieToRoom(&mov2, 1100);
	r1.addMovieToRoom(&mov1, 1500);
	r1.addMovieToRoom(&mov1, 1700);
	r1.addMovieToRoom(&mov2, 1900);
	admin.infoTable[0] = &mov1;
	admin.allCount++;
	admin.infoTable[1] = &mov2;
	admin.allCount++;

	while (input[0] != 'Q')
	{
		//관리자, 사용자 권한 변경
		if (input[0] == 'M')
		{
			mode = ADMIN;
			cout << "관리자 모드 전환" << endl;
			memset(input, 0, 10);
		}
		if (input[0] == 'U')
		{
			mode = USER;
			cout << "사용자 모드 전환" << endl;
			memset(input, 0, 10);
		}

		memset(input, 0, 10);

		switch(mode)
		{
		case HOME:
			cout << "사용자는 U, 관리자는 M 입력" << endl;
			cin >> input;
			break;
		case USER: //사용자 홈
			cout << "사용자 홈" << endl;
			cout << "1. 영화선택\t2. 티켓 정보 확인" << endl;
			cin >> input;
			if (input[0] == '1') {
				mode = CHOOSEMOVIE;
			}
			else if (input[0] == '2') {
				mode = TICKET;
			}
			break;
		case CHOOSEMOVIE: //영화 선택 
		{

			cout << "영화 선택" << endl;
			//전체 영화 리스트 출력
			admin.printInfoTable();

			int index;
			cout << "예매하실 영화를 선택해주세요 : ";
			cin >> index;

			//선택한 영화의 상영 리스트 (영화관별 시간, 잔여 좌석)
			MovieInfo* movie = admin.infoTable[index - 1];

			admin.roomTable[index - 1] = &r1;
			admin.roomTable[index - 1]->printMovieInfo(movie);

			int room, time;
			cout << "원하시는 영화관을 선택해주세요 : ";
			cin >> room;
			cout << "원하시는 시간을 선택해주세요 : ";
			cin >> time;

			int time_index = 0;
			Ticket* ticket = NULL;

			//선택한 영화가 상영되는 영화관의 좌석 상태 출력하고 좌석 선택
			MoviePlay* temp = admin.roomTable[room - 1]->head;
			while (temp != NULL) {
				if (temp->info == movie) {
					time_index++;
					if (time == time_index) {
						//예매
						ticket = admin.addTicket(temp);
					}
				}
				temp = temp->nextPlay;

			}


			//예매 결과 출력
			ticket->printTicket();

			//티켓에 예매 정보 추가


			mode = USER;
		}
		break;
		case TICKET: //티켓 정보 확인
			int number;
			Ticket* temp;

			cout << "티켓 정보 확인" << endl;
			//티켓 번호 입력
			cout << "티켓 번호 입력: ";
			cin >> number;
			//티켓 정보 출력

			temp = admin.findTicket(number);
			if (temp == NULL) {
				cout << "해당 예매 정보가 없습니다." << endl;
			}
			else {
				temp->printTicket();
			}

			mode = USER;
			break;



		case ADMIN: //관리자 홈
			cout << "관리자 홈" << endl;
			cout << "1. 영화관리 2. 영화관 관리" << endl;
			cin >> input;
			if (input[0] == '1') {
				mode = CHOOSEMOVIE;
			}
			else if (input[0] == '2') {
				mode = TICKET;
			}
			break;
		case MANMOVIE: // 영화 관리
			cout << "영화 관리" << endl;
			cout << "1. 영화 추가 2. 영화 삭제" << endl;
			cin >> input;
			if (input[0] == '1') {
				mode = MAKEMOVIE;
			}
			else if (input[0] == '2') {
				mode = DELETEALL;
			}
			//전체 영화 리스트 출력
			mode = ADMIN;
			break;
		case MAKEMOVIE: //새로운 영화 만들어서 추가
			mode = ADMIN;
			break;
		case DELETEALL: //영화 삭제 (모든 영화관에서 삭제)
			mode = ADMIN;
			break;
		case MANROOM: //영화관 관리
			//영화관 선택
			mode = ADMIN;
			break;
		case ROOMSTATUS: //영화관 상태 변경
			mode = ADMIN;
			break;
		case ADDMOVIE: //영화관에 영화 추가
			//영화관의 상영 영화 리스트 출력
			//전체 영화 리스트 출력
			//영화 선택 후, 영화관에 추가 가능한지 검사
			//영화관
			mode = ADMIN;
			break;
		case DELETEMOVIE: //영화관에 영화 삭제
			//영화관의 상영 영화 리스트 출력
			//영화 선택 후, 삭제
			//영화관의 상영 영화 리스트 출력
			mode = ADMIN;
			break;
		default:
			break;
		}
	}




	return 0;
}
