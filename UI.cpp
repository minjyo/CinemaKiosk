
#include "Header.hpp"

/* 사용자 홈 화면 */
int UI::userHome(void) {

	system("cls");

	//printf("사용자 홈 화면\n\n");


	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                 ##   ##  ##   ##       ###    ##  ######## ##    ## ####                   ■" << endl;
	cout << "■                ##  ##   ##   ##       ## ##  ##  ##       ###   ### ## ##                  ■" << endl;
	cout << "■               ## ##    ##   ## ##### ##  ## ##  ######## ## #  ## # ##  ##                 ■" << endl;
	cout << "■              ##   ##  ### ###       ##   ####  ##       ##  # ##  # #######                ■" << endl;
	cout << "■             ##     ##  ####        ##    ###  ######## ##   ##    # ##    ##               ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                           +──────────────────────────────────+                             ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■               ┌──────────────────────────────────────────────────────────┐                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │  1. 영화 선택                                            │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │  2. 티켓 정보 확인                                       │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               └──────────────────────────────────────────────────────────┘                 ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

	key = _getch();

	x = 21; y = 17;

	gotoxy(x, y);

	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 17)
				{
					y-=2;
					gotoxy(x, y);
				}
				break;
			case 80:
				if (y < 19)
				{
					y+=2;
					gotoxy(x, y);
				}
				break;
			default:
				break;
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			/* 영화 선택 화면 */
			if (y == 17)
				return CHOOSEMOVIE;
			/* 티켓 정보 확인 */
			if (y == 19)
				return CHECKTICKET;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109) {
			return ADMIN;
		}
	}
}

//영화 예매 선택 시 영화 리스트 출력하는 화면

int UI::chooseMovie(Admin admin, int* movie_index) {
	system("cls");

	int y_min;

	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "                                                                                              ■" << endl;
	cout << "      영화 선택                                                                               ■" << endl;
	cout << "     +──────────────────────────+" << endl;

	admin.printInfoTable();

	cout << "■                                                                                              " << endl;
	cout << "■    예매하실 영화를 선택해주세요                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	x = 1; y_min = 4; y = y_min;

	gotoxy(x, y);

	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > y_min)
				{
					y--;
					gotoxy(x, y);
				}
				break;
			case 80:
				if (y < y_min + admin.infoCount - 1)
				{
					y++;
					gotoxy(x, y);
				}
				break;
			default:
				break;
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			*movie_index = (y - y_min);
			return CHOOSEROOM;
		}
		/* u -> 사용자 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return USER;
		}
	}
}

//영화 선택 시 상영하는 영화 리스트 출력하고, 영화관과 시간을 선택해, 예매할 영화를 선택하는 화면
int UI::chooseRoom(Admin admin, int* room_index, int movie_index, MovieInfo** movie) {
	*movie = admin.infoTable[movie_index];
	int y_min;

	x = 1; y_min = 3; y = y_min;

	system("cls");
	(*movie)->printInfo();

	int array[5] = { 0, };

	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		array[i] = admin.roomTable[i]->printMovieInfo(*movie);
	}

	printf("숫자를 입력하여 영화관을 선택하세요.\n");

	while (1) {
		key = _getch();
		if (key > 48 && key < 54) {
			if (array[key - 49] == 0) {
				cout << "선택하신 영화관은 해당 영화를 상영하지 않습니다. 다시 선택해주세요\n";
			}
			else {
				*room_index = key - 48;
				return CHOOSETIME;
			}
		}
		else if (key == 117) {
			return USER;
		}
		else if (key == 8) {
			return CHOOSEMOVIE;
		}
	}

	/*
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
	*/
}

int UI::chooseTime(Admin admin, int room, int* index, MovieInfo* movie, MoviePlay** play) {
	int y_min;
	x = 1; y_min = 3; y = y_min;

	system("cls");
	admin.roomTable[room - 1]->printMovieInfo(movie);
	//*play = admin.roomTable[room-1]->

	gotoxy(x, y);

	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > y_min)
				{
					y--;
					gotoxy(x, y);
				}
				break;
			case 80:
				if (y < y_min + admin.roomTable[room - 1]->movieCount - 1);
				{
					y++;
					gotoxy(x, y);
				}
				break;
			default:
				break;
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			*index = (y - y_min);
			return CHOOSESEAT;
		}
		/* u -> 사용자 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return CHOOSEROOM;
		}
	}


}


int UI::chooseSeat(Admin admin, MoviePlay* play, Ticket** newTicket) {
	short numberOfHead;                 //인원 수
	short restSeat = play->restSeat(); //잔여 좌석
	short i, temp;                      //반복문
	short count;                    //몇명 예매했는지
	bool check;
	int x_min, y_min;
	x_min = 7; y_min = 7;

	system("cls");
	gotoxy(2, y_min - 5);
	play->printSeat();

	//인원수 입력받기, 예외처리 : 0또는 음수거나 잔여좌석보다 크게 입력받을 때
	do
	{
		gotoxy(x_min + 6, y_min + SIZE_ROW + 3);
		cout << "인원 수를 입력하세요 : ";
		cin >> numberOfHead;
		check = (numberOfHead <= 0) || (numberOfHead > restSeat);
		if (check)
		{
			gotoxy(x_min + 6, y_min + SIZE_ROW + 4);
			cout << "잔여 좌석보다 많습니다." << endl;
		}
	} while (check);

	count = numberOfHead;

	//입력받은 인원수만큼 short 배열 만들기 & -1로 초기화
	short* seatArr = new short[numberOfHead];
	for (i = 0; i < numberOfHead; i++)
	{
		seatArr[i] = -1;
	}

	system("cls");
	gotoxy(2, y_min - 5);
	play->printSeat();
	gotoxy(x_min + 6, y_min + SIZE_ROW + 3);
	cout << "원하는 좌석을 선택하세요.";
	gotoxy(x_min + 6, y_min + SIZE_ROW + 4);
	printf("%2d명 남았습니다.", count);

	x = 1; y = 1;
	gotoxy(2 * (x_min + x), y_min + y);

	while (count != 0)
	{
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 1)
				{
					y--;
				}
				break;
			case 75:
				if (x > 1)
				{
					x--;
				}
				break;
			case 77:
				if (x < SIZE_COLUMN)
				{
					x++;
				}
				break;
			case 80:
				if (y < SIZE_ROW)
				{
					y++;
				}
				break;
			default:
				break;
			}
			gotoxy(2 * (x_min + x), y_min + y);
		}
		else if (key == 13) {
			/* 엔터가 눌렸을 때 */
			check = false;

			temp = y * 10 + x;

			for (i = 0; i < numberOfHead; i++)
			{
				if (seatArr[i] == temp)
				{
					seatArr[i] = -1;
					check = true;
				}
			}
			/* 이미 배열 내에 temp와 같은 값이 저장되어 있으면(기존 좌석 취소)  */
			if (check)
			{
				cout << "□";
				count++;
				gotoxy(x_min + 6, y_min + SIZE_COLUMN + 5);
				printf("%c열 %d 취소 성공!       ", 64 + y, x);
				gotoxy(x_min + 6, y_min + SIZE_ROW + 4);
				printf("%2d", count);
				gotoxy(2 * (x_min + x), y_min + y);
			}
			/* 배열 내에 temp와 같은 값이 저장되어 있지 않으면(신규 좌석 예매)  */
			else
			{
				/* 이미 예매된 좌석이면 (checkSeat가 true면 이미 예매된 좌석으로 일단 구현) */
				if (play->checkSeat(y, x))
				{
					gotoxy(x_min + 6, y_min + SIZE_ROW + 5);
					cout << "이미 예매된 좌석입니다.";
					gotoxy(2 * (x_min + x), y_min + y);
				}
				/* 예매된 좌석이 아니면 신규 예매 */
				else
				{
					i = 0;
					while (seatArr[i] != -1)
					{
						i++;
					}
					seatArr[i] = temp;
					cout << "■";
					count--;
					gotoxy(x_min + 6, y_min + SIZE_ROW + 5);
					printf("%c열 %d 예매 성공!       \n", 64 + y, x);
					gotoxy(x_min + 6, y_min + SIZE_ROW + 4);
					printf("%2d", count);
					gotoxy(2 * (x_min + x), y_min + y);
				}
			}
		}
		/* u -> 사용자 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return CHOOSETIME;
		}
	}
	/* 예매가 완료되면 tail다음에 티켓 추가해주기 */
	if (admin.ticketHead == NULL)                 //첫 티켓일 경우 tail과 head에 추가
	{
		(*newTicket) = new Ticket(numberOfHead, FIRST_TICKET, seatArr, play, 0x00);
	}
	else
	{
		(*newTicket) = new Ticket(numberOfHead, admin.ticketTail->ticketNumber + 1, seatArr, play, 0x00);
	}
	return CHECKINFO;
}
int UI::checkInfo(Ticket* newTicket) {
	system("cls");
	newTicket->printTicket();

	cout << "예매하신 정보가 맞습니까? (y/n)";
	while (1) {
		key = _getch();
		/* y -> CHECKMONEY */
		if (key == 121) {
			return CHECKMONEY;
		}
		/* n -> USER */
		else if (key == 110) {
			newTicket->~Ticket();
			return USER;
		}
	}
	return 0;
}
int UI::checkMoney(Admin* admin, Ticket* newTicket) {
	MovieInfo* minfo; short numberOfHead;
	//금액
	int i;
	int insertMoney = 0; //입력 금액
	int total; //총 금액
	int money = 0;	//입력 된 금액
	bool check = true;

	total = newTicket->playInfo->info->price * newTicket->number;
	system("cls");
	cout << "결제 금액 : " << total << endl;
	cout << "무엇으로 결제하시겠습니까 ? 1. 현금  2. 카드" << endl;
	while (check) {
		cin >> i;
		if (i == 1) {
			while (money < total) {
				if (insertMoney == -1) {
					cout << "예매가 취소되었습니다." << endl;

					newTicket->~Ticket();
					Sleep(2000);
					return USER;
				}
				else {
					cout << "총 금액 : " << total << endl;
					cout << "남은 금액 : " << total - money << endl;
					cout << "금액을 넣어주세요. (-1 : 취소)" << endl;
					cin >> insertMoney;
					money += insertMoney;
				}
			}
			cout << "결제 진행중..." << endl;
			Sleep(2000);

			cout << "거스름돈 : " << money - total << endl;

			cout << "결제가 완료되었습니다." << endl;

			check = false;
		}
		else if (i == 2) {
			cout << "카드를 넣어주세요." << endl;
			Sleep(2000);
			cout << "결제가 완료되었습니다." << endl;

			check = false;
		}
		else {
			cout << "잘못 입력하셨습니다. 다시 입력해주세요 : ";
		}
	}

	if ((*admin).ticketHead == NULL) {
		(*admin).ticketHead = newTicket;
		(*admin).ticketTail = newTicket;
	}
	else {
		(*admin).ticketTail->nextTicket = newTicket;
		(*admin).ticketTail = newTicket;
	}
	/* 좌석 상태 반영 */
	for (short i = 0; i < newTicket->number; i++) {
		newTicket->playInfo->changeSeat(newTicket->seatNumber[i] / 10, newTicket->seatNumber[i] % 10, true);
	}
	Sleep(2000);
	return USER;
}

int UI::checkTicket(Admin* admin) {
	int tNumber;
	Ticket* ticket = NULL;
	system("cls");
	cout << "예매하신 티켓 번호를 입력하세요 : ";
	cin >> tNumber;
	ticket = (*admin).findTicket(tNumber);

	if (ticket == NULL) {
		cout << "해당 예매 번호가 없습니다.\n";
		Sleep(1000);
		return USER;
	}
	else {
		ticket->printTicket();
		cout << endl << "예매를 취소하시겠습니까? (y/n)\n";
		while (1) {
			key = _getch();
			/* y -> 예매취소 */
			if (key == 121) {
				(*admin).deleteTicket(ticket);
				Sleep(3000);
				return USER;
			}
			/* n, u, backspace -> 유저홈 */
			else if (key == 110 || key == 117 || key == 8) {
				return USER;
			}
		}
	}
}
//관리자 홈 화면
int UI::adminHome(void) {
	system("cls");
	cout << "관리자 홈" << endl << endl;
	cout << "◎ 영화 관리" << endl;
	cout << "◎ 영화관 관리" << endl;

	int y_min = 3;
	x = 1;  y = 0;
	gotoxy(x, y_min);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 0) {
					y--;
					gotoxy(x, y + y_min);
				}
				break;
			case 80:
				if (y < 1)
				{
					y++;
					gotoxy(x, y + y_min);
				}
				break;
			default:
				break;
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			/* 영화 관리 */
			if (y == 0)
				return MANMOVIE;
			/* 영화관 관리 */
			if (y == 1)
				return MANROOM;
		}
		/* u -> 유저 홈 화면 */
		else if (key == 117) {
			return USER;
		}
	}
}

////////////////////////////////////// 109 m    117 u   ////

//영화 관리 화면
int UI::manMovie(void) {
	system("cls");
	cout << "영화 관리" << endl << endl;
	cout << "◎ 영화 추가" << endl;
	cout << "◎ 영화 삭제" << endl;

	int y_min = 3;
	x = 1;  y = 0;
	gotoxy(x, y_min);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 0)
				{
					y--;
					gotoxy(x, y + y_min);
				}
				break;
			case 80:
				if (y < 1)
				{
					y++;
					gotoxy(x, y + y_min);
				}
				break;
			default:
				break;
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			/* 영화 관리 - 영화 추가 */
			if (y == 0)
				return MAKEMOVIE;
			/* 영화 관리 - 영화 삭제 */
			if (y == 1)
				return DELETEALL;
		}
		/* u -> 유저 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109 || key == 8) {
			return ADMIN;
		}
	}
}
//영화관리 - 영화 추가
int UI::makeMovie(Admin* admin) {
	system("cls");
	(*admin).createMovieInfo();
	//admin.infoTable[admin.allCount];
	cout << "영화 추가가 완료 되었습니다." << endl;
	(*admin).printInfoTable();
	return ADMIN;
}

//영화관리 - 영화 삭제
int UI::deleteAll(Admin* admin) {
	system("cls");
	int y_min;

	x = 1; y_min = 3; y = 0;

	(*admin).printInfoTable();
	cout << "삭제할 영화를 선택하세요";

	gotoxy(1, y_min);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key) {
			case 72:
				if (y > 0) {
					y--;
				}
				break;
			case 80:
				if (y < (*admin).infoCount - 1) {
					y++;
				}
				break;
			default:
				break;
			}
			gotoxy(1, y_min + y);
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			(*admin).deleteMovieInfo(y);
			gotoxy(1, y_min + (*admin).infoCount + 2);
			cout << "정상 삭제 되었습니다.";
			Sleep(2000);

			return ADMIN;
		}
		/* u -> 유저 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109) {
			return ADMIN;
		}
		/* backspace -> 영화 관리 화면 */
		else if (key == 8) {
			return MANMOVIE;
		}

	}
}

//영화관 관리 화면
int UI::manRoom(int* room_index) {
	system("cls");
	cout << "영화관 관리" << endl << endl;
	cout << "※ 1관 ※    ◎ 추가    ◎ 삭제" << endl;
	cout << "※ 2관 ※    ◎ 추가    ◎ 삭제" << endl;
	cout << "※ 3관 ※    ◎ 추가    ◎ 삭제" << endl;
	cout << "※ 4관 ※    ◎ 추가    ◎ 삭제" << endl;
	cout << "※ 5관 ※    ◎ 추가    ◎ 삭제" << endl;

	int x_min, y_min;
	x_min = 14; y_min = 3;
	x = 0; y = 0;
	gotoxy(x_min, y_min);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 0) {
					y--;
				}
				break;
			case 75:
				if (x > 0) {
					x--;
				}
				break;
			case 77:
				if (x < 1) {
					x++;
				}
				break;
			case 80:
				if (y < 4) {
					y++;
				}
				break;
			default:
				break;
			}
			if (x == 1) {
				gotoxy(x_min + 11 * x, y_min + y);
			}
			else {
				gotoxy(x_min, y_min + y);
			}
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			*room_index = y;
			if (x == 1) {
				return DELETEMOVIE;
			}
			else {
				return ADDMOVIE;
			}
		}
		/* u -> 유저 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109 || key == 8) {
			return ADMIN;
		}
	}
}


//영화관 관리 - 상영 영화 추가
int UI::addMovie(Admin* admin, int room_index) {
	system("cls");

	//전체 영화 리스트 출력
	(*admin).printInfoTable();
	cout << endl;

	(*admin).roomTable[room_index]->printTimeTable();
	cout << endl << "추가할 영화를 선택하세요 ";

	int y_min = 3;
	x = 1; y = 0;
	gotoxy(1, y_min);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 0) {
					y--;
				}
				break;
			case 80:
				if (y < (*admin).infoCount - 1) {
					y++;
				}
				break;
			default:
				break;
			}
			gotoxy(x, y + y_min);
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			short time;
			gotoxy(x, 20);
			cout << "추가할 영화의 시작 시간을 입력하세요 : ";
			cin >> time;

			//해당 시간으로 입력 가능한지 검사한 후 입력
			if ((*admin).roomTable[room_index]->addMovieToRoom((*admin).infoTable[y], time)) {
				(*admin).roomTable[room_index]->printTimeTable();
				cout << "영화가 추가되었습니다.";
				Sleep(2000);
				return ADMIN;
			}
			else {
				gotoxy(x, 21);
				cout << "영화를 넣을 수 있는 시간이 없습니다.\n";
				Sleep(2000);
				return ADMIN;
			}
		}
		/* u -> 유저 홈 화면 */
		else if (key == 117) {
			return USER;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109) {
			return ADMIN;
		}
		/* backspace -> 영화 관리 화면 */
		else if (key == 8) {
			return MANROOM;
		}
	}



}

//영화관 관리 - 상영 영화 삭제
int UI::deleteMovie(Admin* admin, int room_index) {
	system("cls");

	short sTime;
	cout << room_index << endl;
	//영화관의 상영 영화 리스트 출력
	(*admin).roomTable[room_index]->printTimeTable();

	//영화 선택 후, 삭제
	cout << "삭제할 영화의 시간 시작을 입력해주세요(취소 : -1) : ";
	cin >> sTime;

	if (sTime == -1) {
		return MANROOM;
	}
	/* sTime 값 예외처리 부탁해 */////////////////////////////////////////////////////////////////////////////////////////////////////////
	else {
		(*admin).roomTable[room_index]->deleteMoviePlay(sTime);
		(*admin).roomTable[room_index]->printTimeTable();
		cout << "정상 삭제되었습니다.\n";
		Sleep(2000);
		return ADMIN;
	}
}

void UI::gotoxy(short x, short y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
