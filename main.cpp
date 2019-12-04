//
//  main.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright Â© 2019 minjyo. All rights reserved.
//

#include "Header.hpp"

using namespace std;

int main()
{
	char mode = USER;
	char* input = (char*)malloc(1);
	*input = '\0';

	int room_index = 0;
	int movie_index = 0;
	MovieInfo* movie = NULL;
	MoviePlay* play = NULL;
	Ticket* ticket = NULL;


	Admin admin;
	UI ui;
	//////////////////////////////////////////////////////////////			임시 play 나중에 함수로 바꿔주기
	play = admin.roomTable[0]->head->nextPlay;
	//////////////////////////////////////////////////////////////
	while (*input != 'Q')
	{
		*input = '\0';

		switch (mode)
		{
		case USER: //사용자 홈
			mode = ui.userHome();
			break;
		case CHOOSEMOVIE: //영화 선택
			mode = ui.chooseMovie(admin, &movie_index);
			break;
		case CHOOSEROOM:	//영화관 선택
			mode = ui.chooseRoom(admin, &room_index, movie_index, &movie);
			break;
		case CHOOSETIME:	//시간 선택
			mode = ui.chooseTime(admin, room_index, &movie_index, movie, &play);
			break;
		case CHOOSESEAT:	//좌석 선택
			mode = ui.chooseSeat(admin, play, &ticket);
			break;
		case CHECKINFO:		//영화 정보 확인
			mode = ui.checkInfo(ticket);
			break;
		case CHECKMONEY:	//결제 화면
			mode = ui.checkMoney(&admin, ticket);
			break;
		case CHECKTICKET:	//티켓 확인
			mode = ui.checkTicket(&admin);
			break;
		case ADMIN: //관리자 홈
			mode = ui.adminHome();
			break;
		case MANMOVIE: // 영화 관리
			mode = ui.manMovie();
			break;
		case MAKEMOVIE: //새로운 영화 만들어서 추가
			mode = ui.makeMovie(&admin);
			break;
		case DELETEALL: //영화 삭제 (모든 영화관에서 삭제)
			mode = ui.deleteAll(&admin);
			break;
		case MANROOM: //영화관 관리
			mode = ui.manRoom(&room_index);
			break;
		case ADDMOVIE: //영화관에 영화 추가
			mode = ui.addMovie(&admin, room_index);
			break;
		case DELETEMOVIE: //영화관에 영화 삭제
			mode = ui.deleteMovie(&admin, room_index);
			break;
		default:
			break;
		}
	}
	cout << "프로그램이 종료되었습니다." << endl;
	return 0;
}
