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
	char mode = USER;
	char* input = (char *)malloc(1);
	*input = '\0';
	int room_index;

	Admin admin;

	while (*input != 'Q')
	{
		*input = '\0';

		switch (mode)
		{
		case USER: //사용자 홈
			system("cls");
			cout << "1. 영화선택\t2. 티켓 정보 확인" << endl;
			*input = _getch();
		
			if (*input == '1') {
				mode = CHOOSEMOVIE;
			}
			else if (*input == '2') {
				mode = TICKET;
			}
			else if (*input == 'M')
			{
				mode = ADMIN;
				cout << "관리자 모드 전환" << endl;
			}
			break;

		case CHOOSEMOVIE: //영화 선택
		{
			system("cls");

			cout << "영화 선택" << endl;
			//전체 영화 리스트 출력
			admin.printInfoTable();

			cout << "예매하실 영화를 선택해주세요 : ";
			*input = _getch();
			int index = 0;
			index = atoi(input);

			if (*input == '\b') {
				mode = USER;
			}
			else {
				cout << "\n   ";
				cout.setf(ios::left);
				cout << setw(20) << "영화 이름";
				cout << setw(20) << "영화 가격";
				cout << setw(20) << "영화 감독";
				cout << setw(20) << "런닝 타임";
				cout << "-----------------------------------------------------------------------" << endl;

				cout << "   ";
				admin.infoTable[index - 1]->printInfo();

				//선택한 영화의 상영 리스트 (영화관별 시간, 잔여 좌석)
				MovieInfo* movie = admin.infoTable[index - 1];

				int array[5] = {0, };
				for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
					array[i] = admin.roomTable[i]->printMovieInfo(movie);
				}
				cout << endl;

				int room, time;
				cout << "원하시는 영화관을 선택해주세요 : ";
				cin >> room;
				cout << "원하시는 번호를 선택해주세요 : ";
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
				if (ticket != NULL) {
					ticket->printTicket();
				}

				mode = USER;
			}
			break;
		}


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
				char flag;
				temp->printTicket();
				cout << "\n예매를 취소하시겠습니까? (취소하려면 Y)" << endl;
				cin >> flag;
				if (flag == 'Y') {
					admin.deleteTicket(temp);
				}
			}
			mode = USER;
			break;

		case ADMIN: //관리자 홈
			cout << "관리자 홈" << endl;
			cout << "1. 영화관리 2. 영화관 관리" << endl;
			*input = _getch();
			if (*input == '1') {
				mode = MANMOVIE;
			}
			else if (*input == '2') {
				mode = MANROOM;
			} else if (*input == 'U')
			{
				mode = USER;
				cout << "사용자 모드 전환" << endl;
			}
			break;
		case MANMOVIE: // 영화 관리
			cout << "영화 관리" << endl;
			cout << "1. 영화 추가 2. 영화 삭제" << endl;
			*input = _getch();
			if (*input == '1') {
				mode = MAKEMOVIE;
			}
			else if (*input == '2') {
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
			cout << "1.영화관에 영화 추가               2.영화관에서 영화 삭제" << endl;

			int num;
			cin >> num;

			switch (num) {
			case 1:
				mode = ADDMOVIE;
				break;
			case 2:
				mode = DELETEMOVIE;
				break;
			default:
				mode = MANROOM;
				break;
			}
			break;
		case ADDMOVIE: //영화관에 영화 추가
			//영화관의 상영 영화 리스트 출력
			admin.roomTable[room_index - 1]->printTimeTable();
			//전체 영화 리스트 출력
			admin.printInfoTable();
			//영화 선택 후, 영화관에 추가 가능한지 검사하고 영화관에 추가
			cout << "추가할 영화를 입력하세요: ";
			int input;
			cin >> input;
			cout << "추가할 영화 시간을 입력하세요: ";
			short time;
			cin >> time;

			if (admin.roomTable[room_index - 1]->addMovieToRoom(admin.infoTable[input - 1], time)) {
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
