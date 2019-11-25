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
			cout << "영화 선택" << endl;
			//전체 영화 리스트 출력
            admin.printInfoTable();
        
            int index;
            cout << "예매하실 영화를 선택해주세요 : ";
            cin >> index;
            
			//선택한 영화의 상영 리스트 (영화관별 시간, 잔여 좌석)
            string title = admin.infoTable[index]->title;
            admin.printAllMovies(title);
            
            cout << "원하시는 영화관을 선택해주세요 : ";
            cin >> index;
                
			//선택한 영화가 상영되는 영화관의 좌석 상태 출력하고 좌석 선택
            MoviePlay* temp = admin.roomTable[index+1]->head;
            while(temp!=NULL){
                if(temp->info->title==title){
                    temp->printSeat();
                    int x,y;
                    
                    while(1){
                        cout << "원하시는 좌석을 입력해주세요(x) : ";
                        cin >> x;
                        cout << "원하시는 좌석을 입력해주세요(y) : ";
                        cin >> y;
                        if(temp->checkSeat(x, y)){
                            temp->changeSeat(x, y, false); //false가 예매 완료
                            break;
                        }else{
                            cout << "해당 좌석은 예매할 수 없습니다. 다시 선택해주세요." << endl;
                        }
                    }
                    break;
                }
                temp = temp->nextPlay;
            }

			//예매 결과 출력
            Ticket ticket(/*TODO*/);
            ticket.printTicket();
			//티켓에 예매 정보 추가
            admin.ticketHead->nextTicket=ticket;
            ticket->nextTicket=admin.ticketTail;
                
			mode = USER;
			break;
		case TICKET: //티켓 정보 확인
			cout << "티켓 정보 확인" << endl;
			//티켓 번호 입력

			//티켓 정보 출력
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
