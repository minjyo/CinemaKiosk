
#include "Header.hpp"

/* 사용자 홈 화면 */
int UI::userHome(void) {

	system("cls");

	cout << endl << endl << endl << endl << endl << endl << endl << endl;
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
	cout << "■               │                   ☞ 영화 선택                           │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │                   ☞ 티켓 정보 확인                      │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               └──────────────────────────────────────────────────────────┘                 ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;

	printBorder();

	x = 38; y = 24;

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
				if (y == 26)
				{
					y-=2;
					gotoxy(x, y);
				}
				break;
			case 80:
				if (y == 24)
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
			if (y == 24)
				return CHOOSEMOVIE;
			/* 티켓 정보 확인 */
			if (y == 26)
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

	cout << endl;
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

	cout << endl << endl << "      영화 선택" << endl;
	cout << "     +──────────────────────────+" << endl;

	admin.printInfoTable();

	cout << endl;
	cout << "      예매하실 영화를 선택해주세요" << endl;
	printBorder();
	x = 4; y_min = 16; y = y_min;

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

	//x = 4; y_min = 16; y = y_min;

	system("cls");
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl;
	
	cout << setw(6) << "   ";
	cout.setf(ios::left);
	cout << setw(20) << "영화 이름";
	cout << setw(20) << "영화 가격";
	cout << setw(20) << "영화 감독";
	cout << setw(20) << "런닝 타임" << endl << endl;
	cout << setw(6) << "   ";
	(*movie)->printInfo();
	cout << endl;

	int array[5] = { 0, };

	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		array[i] = admin.roomTable[i]->printMovieInfo(*movie);
	}
	printBorder();
	gotoxy(30, 35);
	printf("숫자를 입력하여 영화관을 선택하세요.\n");

	while (1) {
		key = _getch();
		if (key > 48 && key < 54) {
			if (array[key - 49] == 0) {
				gotoxy(16, 33);
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
}

int UI::chooseTime(Admin admin, int room, int* index, MovieInfo* movie, MoviePlay** play) {
	int y_min;
	system("cls");

	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl;
	
	cout << setw(6) << "   ";
	cout.setf(ios::left);
	cout << setw(20) << "영화 이름";
	cout << setw(20) << "영화 가격";
	cout << setw(20) << "영화 감독";
	cout << setw(20) << "런닝 타임" << endl << endl;
	cout << setw(6) << "   ";
	movie->printInfo();
	cout << endl;

	int n_movie = admin.roomTable[room - 1]->printMovieInfo(movie);

	printBorder();

	gotoxy(32, 35);
	cout << "키보드를 움직여 영화를 선택해주세요\n";

	x = 4; y = 1; y_min = 16;
	gotoxy(x, y_min + 1);
	while (1) {
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 1) {
					y--;
				}
				break;
			case 80:

				if (y < n_movie - 1) {
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

			//cout << y-y_min << endl;
			*index = y;
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
	bool check = true;
	int x_min, y_min;
	x_min = 18; y_min = 18;

	system("cls");
	cout << endl;
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■           ####      #####     ###     ######           ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■         ##    #    ##       ##  ##     ##              ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■           ##      ####     ######     ##               ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■        #    ##   ##       ##  ##     ##                ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ####    #####    ##  ##     ##                 ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	gotoxy(1, y_min - 5);
	play->printSeat();
	printBorder();
	//인원수 입력받기, 예외처리 : 0또는 음수거나 잔여좌석보다 크게 입력받을 때
	do
	{
		gotoxy(x_min + 17, y_min + SIZE_ROW + 3);
		cout << "인원 수를 입력하세요 : ";
		cin >> numberOfHead;
		if ((numberOfHead > 0) && (numberOfHead <= restSeat)) {
			check = false;
		}
		else if (numberOfHead > restSeat) {
			gotoxy(x_min + 17, y_min + SIZE_ROW + 4);
			cout << "잔여 좌석보다 많습니다.      " << endl;
			gotoxy(x_min + 30, y_min + SIZE_ROW + 3);
			cout << "           ";

		}

		else if (!cin) {
			gotoxy(x_min + 17, y_min + SIZE_ROW + 4);
			cout << "잘못된 입력입니다.      " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			gotoxy(x_min + 30, y_min + SIZE_ROW + 3);
			cout << "           ";
		}

		else {
			gotoxy(x_min + 17, y_min + SIZE_ROW + 4);
			cout << "잘못된 입력입니다.      " << endl;
			gotoxy(x_min + 30, y_min + SIZE_ROW + 3);
			cout << "           ";
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
	cout << endl;
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■           ####      #####     ###     ######           ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■         ##    #    ##       ##  ##     ##              ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■           ##      ####     ######     ##               ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■        #    ##   ##       ##  ##     ##                ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ####    #####    ##  ##     ##                 ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	gotoxy(1, y_min - 5);
	play->printSeat();
	gotoxy(x_min + 17, y_min + SIZE_ROW + 3);
	cout << "원하는 좌석을 선택하세요.";
	gotoxy(x_min + 21, y_min + SIZE_ROW + 4);
	printf("%2d명 남았습니다.", count);
	printBorder();
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
				if (y > 1) {
					y--;
				}
				break;
			case 75:
				if (x > 1) {
					x--;
				}
				break;
			case 77:
				if (x < SIZE_COLUMN) {
					x++;
				}
				break;
			case 80:
				if (y < SIZE_ROW) {
					y++;
				}
				break;
			default:
				break;
			}
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
				gotoxy(x_min + 18, y_min + SIZE_ROW + 5);
				printf("   %c열 %d 취소 성공!          ", 64 + y, x);
				gotoxy(x_min + 21, y_min + SIZE_ROW + 4);
				printf("%2d", count);
			}
			/* 배열 내에 temp와 같은 값이 저장되어 있지 않으면(신규 좌석 예매)  */
			else
			{
				/* 이미 예매된 좌석이면 (checkSeat가 true면 이미 예매된 좌석으로 일단 구현) */
				if (play->checkSeat(y, x))
				{
					gotoxy(x_min + 18, y_min + SIZE_ROW + 5);
					cout << "이미 예매된 좌석입니다.     ";
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
					gotoxy(x_min + 18, y_min + SIZE_ROW + 5);
					printf("   %c열 %d 예매 성공!          \n", 64 + y, x);
					gotoxy(x_min + 21, y_min + SIZE_ROW + 4);
					printf("%2d", count);
					
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
		if (x< (SIZE_COLUMN/2 +1)) {
			gotoxy(2 * (x_min + x), y_min + y);
		}
		else {
			gotoxy(2 * (x_min + x + 2), y_min + y);
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
	printBorder();
	gotoxy(1,2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■     ######  ######    ###   ##   ##  #####  ######     ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ##      ##    ##   #  ## ##    ##       ##       ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ##      ##    ##      ###      ####     ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##      ##    ##   #  ## ##    ##       ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##    ######    ###   ##   ##  #####    ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;
	newTicket->printTicket();
	gotoxy(30, 32);
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
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return CHOOSESEAT;
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
	printBorder();
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■         #####            ###            ##  ##         ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■         ##   #         ##  ##           ##  ##         ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■         #####          ######            ####          ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ##             ##  ##             ##           ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ##             ##  ##             ##           ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;
	gotoxy(38, 17);
	cout << "결제 금액 : " << total;
	gotoxy(26, 19);
	cout << "무엇으로 결제하시겠습니까 ? 1. 현금  2. 카드" << endl;

	while (check) {
		gotoxy(71, 19);
		key = _getch();
		
		if (key == 49) { /* 숫자 1*/
			while (money < total) {
				if (insertMoney == -1) {
					gotoxy(26, 27);
					cout << "예매가 취소되었습니다." << endl;

					newTicket->~Ticket();
					Sleep(2000);
					return USER;
				}
				else {
					gotoxy(38, 21);
					cout << "총 금액 : " << total;
					gotoxy(38, 23);
					cout << "남은 금액 : " << total - money;
					gotoxy(32, 25);
					cout << "금액을 넣어주세요. (-1 : 취소)";
					gotoxy(65, 25);
					cin >> insertMoney;
					money += insertMoney;
					gotoxy(65, 25);
					cout << "           ";
					gotoxy(65, 25);
				}
			}
			gotoxy(38, 27);
			cout << "결제 진행중입니다";
			for (int i = 0; i < 6; i++) {
				cout << ".";
				Sleep(300);
			}
			cout << endl;

			gotoxy(38, 29);
			cout << "거스름돈 : " << money - total;
			gotoxy(38, 31);
			cout << "결제가 완료되었습니다.";

			check = false;
		}
		else if (key == 50) { /* 숫자 1*/
			gotoxy(38, 24);
			cout << "카드를 넣어주세요!" << endl;
			Sleep(2000);
			gotoxy(38, 26);
			cout << "결제 진행중입니다";
			for (int i = 0; i < 6; i++) {
				cout << ".";
				Sleep(300);
			}
			cout << endl;
			gotoxy(38, 28);
			cout << "결제가 완료되었습니다.";

			check = false;
		}
		/* n -> USER */
		else if (key == 110) {
			newTicket->~Ticket();
			return USER;
		}
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return CHECKINFO;
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
	cout << endl;
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■     ######  ######    ###   ##   ##  #####  ######     ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ##      ##    ##   #  ## ##    ##       ##       ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ##      ##    ##      ###      ####     ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##      ##    ##   #  ## ##    ##       ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##    ######    ###   ##   ##  #####    ##       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl;
	cout << "■                          예매하신 티켓 번호를 입력하세요 : ";
	printBorder();
	gotoxy(63,13);
	key = _getch();
	if (key == 8) {
		return USER;
	}
	cin >> tNumber;

	cout << endl << endl;
	ticket = (*admin).findTicket(tNumber);

	if (ticket == NULL) {
		gotoxy(32, 15);
		cout << "해당 예매 번호가 없습니다.\n";
		Sleep(2000);
		return USER;
	}
	else {
		ticket->printTicket();
		gotoxy(32, 30);
		cout << "예매를 취소하시겠습니까? (y/n)";
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
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
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
	cout << "■                                      관리자 홈                                             ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■               ┌──────────────────────────────────────────────────────────┐                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │                      ☞ 영화 관리                        │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │                      ☞ 영화관 관리                      │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               └──────────────────────────────────────────────────────────┘                 ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	printBorder();

	int y_min = 24;
	x = 41;  y = 0;
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
				if (y == 2) {
					y-=2;
					gotoxy(x, y + y_min);
				}
				break;
			case 80:
				if (y == 0)
				{
					y+=2;
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
			if (y == 2)
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
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
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
	cout << "■                                      영화 관리                                             ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■               ┌──────────────────────────────────────────────────────────┐                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │                      ☞ 영화 추가                        │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │                      ☞ 영화 삭제                        │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               └──────────────────────────────────────────────────────────┘                 ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	printBorder();

	int y_min = 24;
	x = 41;  y = 0;
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
				if (y == 2)
				{
					y-=2;
					gotoxy(x, y + y_min);
				}
				break;
			case 80:
				if (y == 0)
				{
					y+=2;
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
			if (y == 2)
				return DELETEALL;
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
	printBorder();
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;


	bool result = (*admin).createMovieInfo();
	if (!result) {
		return MANMOVIE;
	}
	cout << endl;
	cout << "■    영화 추가가 완료 되었습니다." << endl<<endl;
	(*admin).printInfoTable();
	printBorder();
	Sleep(3000);
	return MAKEMOVIE;
}

//영화관리 - 영화 삭제
int UI::deleteAll(Admin* admin) {
	system("cls");
	printBorder();
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■       ##       ##    ###    ##   #  ####   ####        ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■       ###     ###   ##  #   ##   #   ##   #            ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■       ## #   ## #   ##  #   ##   #   ##   ####         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##  # ##  #   ##  #    ## #    ##   #            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■       ##   ##   #    ###      ##    ####  #####        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;
	int y_min;

	//x = 1; y_min = 3; y = 0;
	x = 4; y_min = 14; y = 0;

	gotoxy(1, 12);
	(*admin).printInfoTable();
	cout << endl << "      삭제할 영화를 선택하세요";
	
	printBorder();

	gotoxy(x, y_min);
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
			gotoxy(4, y_min + y);
		}
		/* 엔터가 눌렸을 때 */
		else if (key == 13) {
			(*admin).deleteMovieInfo(y);
			gotoxy(7, y_min + (*admin).infoCount + 8);
			cout << "정상 삭제 되었습니다.";
			Sleep(2000);

			return ADMIN;
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
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
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
	cout << "■                                        영화관 관리                                         ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■               ┌──────────────────────────────────────────────────────────┐                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               │           ※ 1관 ※    ☞ 추가    ☞ 삭제                │                 ■" << endl;
	cout << "■               │           ※ 2관 ※    ☞ 추가    ☞ 삭제                │                 ■" << endl;
	cout << "■               │           ※ 3관 ※    ☞ 추가    ☞ 삭제                │                 ■" << endl;
	cout << "■               │           ※ 4관 ※    ☞ 추가    ☞ 삭제                │                 ■" << endl;
	cout << "■               │           ※ 5관 ※    ☞ 추가    ☞ 삭제                │                 ■" << endl;
	cout << "■               │                                                          │                 ■" << endl;
	cout << "■               └──────────────────────────────────────────────────────────┘                 ■" << endl;
	cout << "■                                                                                            ■" << endl;
	cout << "■                                                                                            ■" << endl;
	printBorder();
	int x_min, y_min;
	x_min = 43; y_min = 23;
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
		/* m -> 관리자 홈 화면 */
		else if (key == 109 || key == 8) {
			return ADMIN;
		}
	}
}


//영화관 관리 - 상영 영화 추가
int UI::addMovie(Admin* admin, int room_index) {
	system("cls");
	printBorder();
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■           ###          #####          #####            ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■         ##  ##         ##   #         ##   #           ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■         ######         ##   #         ##   #           ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ##  ##         ##   #         ##   #           ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■         ##  ##         #####          #####            ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;
	//전체 영화 리스트 출력
	(*admin).printInfoTable();
	cout << endl;

	(*admin).roomTable[room_index]->printTimeTable();
	printBorder();
	gotoxy(30, 35);
	cout<< "추가할 영화를 선택하세요 ";

	int y_min = 16;
	x = 4; y = 0;
	gotoxy(4, y_min);
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

			key = _getch();
			if (key == 8) {
				return ADDMOVIE;
			}
			cin >> time;

			//해당 시간으로 입력 가능한지 검사한 후 입력
			if ((*admin).roomTable[room_index]->addMovieToRoom((*admin).infoTable[y], time)) {
				(*admin).roomTable[room_index]->printTimeTable();
				cout << "      영화가 추가되었습니다.";
				printBorder();
				Sleep(2000);
				return ADDMOVIE;
			}
			else {
				gotoxy(x, 21);
				cout << "영화를 넣을 수 있는 시간이 없습니다.\n";
				Sleep(2000);
				return ADDMOVIE;
			}
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
	printBorder();
	gotoxy(1, 2);
	cout << "■                                                        ■■■■■■■■■  ■  ■■  ■■  ■" << endl;
	cout << "■     #####   ######  ##      ######  ######  ######     ■■■■■■■■■    ■■■  ■■  ■" << endl;
	cout << "■     ##   #  ##      ##      ##        ##    ##         ■■■■■■■■■  ■  ■■■    ■■" << endl;
	cout << "■     ##   #  ####    ##      ####      ##    ####       ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■     ##   #  ##      ##      ##        ##    ##         ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■     #####   ######  ######  ######    ##    ######     ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                                                        ■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl << endl << endl << endl;

	short sTime;
	//cout << room_index << endl;
	//영화관의 상영 영화 리스트 출력
	(*admin).roomTable[room_index]->printTimeTable();
	printBorder();

	//영화 선택 후, 삭제
	gotoxy(30, 30);
	cout << "삭제할 영화의 시간 시작을 입력해주세요: ";
	key = _getch();
	if (key == 8) {
		return MANROOM;
	}
	cin >> sTime;

		int check = (*admin).roomTable[room_index]->deleteMoviePlay(sTime);
		if (check == 0) {
			gotoxy(58, 32);
			cout << "올바르지 않은 입력시간입니다. \n";
			Sleep(3000);
			return DELETEMOVIE;
		}
		else {
			//(*admin).roomTable[room_index]->printTimeTable();
			gotoxy(66, 32);
			cout << "정상 삭제되었습니다.\n";
			Sleep(3000);
			return DELETEMOVIE;
		}
}

void UI::gotoxy(short x, short y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void UI::printBorder(void) {
	int i;
	gotoxy(1, 1);
	for (i = 0; i < 48;i++) {
		cout << "■";
	}
	cout << endl;
	for (i = 0; i < 35; i++) {
		cout << "■" << endl;
	}
	for (i = 0; i < 48; i++) {
		cout << "■";
	}
	for (i = 1; i < 37; i++) {
		gotoxy(95, i);
		cout << "■";
	}
}