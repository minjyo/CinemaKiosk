
#include "Header.hpp"

/* 사용자 홈 화면 */
int UI::userHome(void) {

	system("cls");

	printf("사용자 홈 화면\n\n");

	printf("┌─────────────────────────────────┐\n");
	printf("│  1. 영화 선택                    │\n");
	printf("│  2. 티켓 정보 확인               │\n");
	printf("└─────────────────────────────────┘\n");


	key = _getch();

	x = 4; y = 4;
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
				if (y > 4)
				{
					y--;
					gotoxy(x, y);
				}
				break;
			case 80:
				if (y < 5)
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
			/* 영화 선택 화면 */
			if (y == 4)
				return CHOOSEMOVIE;
			/* 티켓 정보 확인 */
			if (y == 5)
				return TICKET;
		}
		/* m -> 관리자 홈 화면 */
		else if (key == 109) {
			return ADMIN;
		}
	}
}

//영화 예매 선택 시 영화 리스트 출력하는 화면
int UI::chooseMovie(Admin admin, int *index) {
	int y_min;
	cout << "영화 선택" << endl;
	//전체 영화 리스트 출력
	admin.printInfoTable();

	cout << "예매하실 영화를 선택해주세요";
	x = 1; y_min = 3; y = y_min;

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
			*index = (y - y_min);
			return CHOOSEROOM;
		}
		/* u -> 사용자 홈 화면 */
		else if (key == 117){
			return USER;
		}
		/* backspace -> 뒤로가기 */
		else if (key == 8) {
			return USER;
		}
	}
}

//영화 선택 시 상영하는 영화 리스트 출력하고, 영화관과 시간을 선택해 예매할, 영화를 선택하는 화면
int UI::chooseRoom(Admin admin, int* room_index) {
	MovieInfo* movie = admin.infoTable[*room_index];
	int y_min;
	char* input = (char*)malloc(1);

	*input = '\0';
	x = 1; y_min = 3; y = y_min;

	system("cls");
	movie->printInfo();

	int array[5] = { 0, };

	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		array[i] = admin.roomTable[i]->printMovieInfo(movie);
	}

	int room;
	*input = _getch();
	room = atoi(input);
	while (array[room - 1] == 0) {
		cout << "선택하신 영화관은 해당 영화를 상영하지 않습니다. 다시 선택해주세요: ";
		*input = _getch();
		room = atoi(input);
	}

	if (*input == 117) {
		return USER;
	}
	else if (*input == 8) {
		return CHOOSEMOVIE;

	}
	else {
		return CHOOSETIME;
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

int UI::chooseTime(Admin admin, int room, int* index) {
	int y_min;
	x = 1; y_min = 3; y = y_min;

	system("cls");
	cout << room << "관" << endl;
	admin.roomTable[room - 1]->printTimeTable();

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
			return TICKET;
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
//영화 예매 후 티켓 정보 확인(check == false) & 예매 정보 확인(check == true)
int UI::checkTicket(bool check) {
	return 0;
}
//관리자 홈 화면
int UI::adminHome(void) {
	return 0;
}
//영화 관리 화면
int UI::movieSetting(void) {
	return 0;
}
//영화관 관리 화면
int UI::roomSetting(void) {
	return 0;
}

void UI::gotoxy(short x, short y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
