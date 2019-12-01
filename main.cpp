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
	int room_index;

	//기본 객체 생성(admin, movie, movieroom)
	Admin admin;

	//영화관 기본 셋팅

	MovieRoom r1(1);
	admin.roomCount++;

	MovieInfo mov1("Frozen2", "director1", 146, 8000);
	MovieInfo mov2("Jocker", "director2", 120, 9000);
	r1.addMovieToRoom(&mov1, 900);
	r1.addMovieToRoom(&mov2, 1000);
	r1.addMovieToRoom(&mov2, 1100);
	r1.addMovieToRoom(&mov1, 1500);
	r1.addMovieToRoom(&mov1, 1700);
	r1.addMovieToRoom(&mov2, 1900);

	admin.infoTable[0] = &mov1;
	admin.infoCount++;
	admin.infoTable[1] = &mov2;
	admin.infoCount++;

	admin.roomTable[0] = &r1;

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

		switch (mode)
		{
		case HOME:
			cout << "사용자는 U, 관리자는 M 입력" << endl;
			cin >> input;
			break;
		case USER: //사용자 홈
			cout << "사용자 홈" << endl;
			cout << "1. 영화선택 2. 티켓 정보 확인" << endl;
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
			system("cls");
			//선택한 영화가 상영되는 영화관의 좌석 상태 출력하고 좌석 선택
			MoviePlay* temp = admin.roomTable[room - 1]->head;
			while (temp != NULL) {
				if (temp->info == movie) {
					time_index++;
					if (time == time_index) {
						//예매
						ticket = admin.addTicket(temp);
						//TODO: 인욱오빠가 고치기~~
					}
				}
				temp = temp->nextPlay;

			}


			//예매 결과 출력
			cout << "dsaf";
			ticket->printTicket();

			//티켓에 예매 정보 추가


			mode = USER;
		}
		break;
		case TICKET: //티켓 정보 확인
			int number;
			cout << "티켓 정보 확인" << endl;
			//티켓 번호 입력
			cout << "티켓 번호 입력: ";
			cin >> number;
			//티켓 정보 출력
			admin.findTicket(number)->printTicket();
			mode = USER;
			break;

		case ADMIN: //관리자 홈
			cout << "관리자 홈" << endl;
			cout << "1. 영화관리 2. 영화관 관리" << endl;
			cin >> input;
			if (input[0] == '1') {
				mode = MANMOVIE;
			}
			else if (input[0] == '2') {
				mode = MANROOM;
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

			break;
		case MAKEMOVIE: //새로운 영화 만들어서 추가
			admin.createMovieInfo();
			//admin.infoTable[admin.allCount];
			cout << "영화 추가가 완료 되었습니다." << endl;
			admin.printInfoTable();
			mode = ADMIN;
			break;
		case DELETEALL: //영화 삭제 (모든 영화관에서 삭제)
			admin.printInfoTable();

			cout << "삭제할 영화: ";
			cin >> room_index;
			admin.deleteMovieInfo(room_index - 1);
			cout << "삭제가 완료되었습니다." << endl;
			admin.printInfoTable();
			mode = ADMIN;
			break;
		case MANROOM: //영화관 관리
			//영화관 선택

			cout << "관리할 영화관 번호를 입력해주세요: ";
			cin >> room_index;
			cout << room_index << "관 관리" << endl;
			cout << "1. 영화관의 상태변경          2.영화관에 영화 추가               3.영화관에서 영화 삭제" << endl;
			int num;
			cin >> num;

			switch (num) {
			case 1:
				mode = ROOMSTATUS;
				break;
			case 2:
				mode = ADDMOVIE;
				break;
			case 3:
				mode = DELETEMOVIE;
				break;
			default:
				mode = MANROOM;
				break;
			}
			break;
		case ROOMSTATUS: //영화관 상태 변경 
			cout << "1. 영화관 열기        2.영화관 닫기" << endl;
			admin.roomTable[room_index - 1]->setStatus(TRUE);
			mode = MANROOM;
			break;
		case ADDMOVIE: //영화관에 영화 추가
			//영화관의 상영 영화 리스트 출력
			admin.roomTable[room_index - 1]->printTimeTable();
			//전체 영화 리스트 출력
			admin.printInfoTable();
			//영화 선택 후, 영화관에 추가 가능한지 검사하고 영화관에 추가
			cout << "추가할 영화를 입력하세요: ";
			int index;
			cin >> index;
			cout << "추가할 영화 시간을 입력하세요: ";
			short time;
			cin >> time;

			if (admin.roomTable[room_index - 1]->addMovieToRoom(admin.infoTable[index - 1], time)) {
				admin.roomTable[room_index - 1]->printTimeTable();
				mode = ADMIN;
			}
			else {
				mode = ADDMOVIE;
			}
			break;
		case DELETEMOVIE: //영화관에 영화 삭제
			short index1;
			cout << room_index << endl;
			//영화관의 상영 영화 리스트 출력
			admin.roomTable[room_index - 1]->printTimeTable();
			//영화 선택 후, 삭제
			cout << "1. 지금 영화관에서 선택한 영화를 모두 삭제         2. 특정 시간의 영화만 삭제" << endl;
			cin >> index1;
			if (index1 == 1) {
				cout << "삭제할 영화를 입력해주세요: ";
				cin >> index1;
				MoviePlay* temp = admin.roomTable[room_index - 1]->head;
				for (int i = 0; i < index1; i++) {
					temp = temp->nextPlay;
				}
				admin.roomTable[room_index - 1]->deleteMovieInfo(temp->info);
				admin.roomTable[room_index - 1]->printTimeTable();
			}
			else if (index1 == 2) {
				cout << "삭제할 영화의 시간 시작을 입력해주세요: ";
				cin >> index1;
				admin.roomTable[room_index - 1]->deleteMoviePlay(index1);
				admin.roomTable[room_index - 1]->printTimeTable();
			}
			mode = ADMIN;
			break;
		default:
			break;
		}
	}
	cout << "프로그램이 종료되었습니다." << endl;
	return 0;
}
