#include "header.hpp"

Admin::Admin() {
	ticketHead = NULL;
	ticketTail = NULL;
}

//전체 영화 리스트 출력
void Admin::printInfoTable(void) {
	system("cls");
	cout << "   영화 제목\t\t\t영화 감독\t\t러닝타임" << endl;
	cout << "----------------------------------------------------------------" << endl;

	for (int i = 0; i < infoCount; i++) {
		cout << i+1 << ". ";
		infoTable[i]->printInfo();
	}
	
}

//영화관 선택 시 시작시간 순으로 상영영화 출력
void Admin::printTimetable(short index) {
	roomTable[index]->printTimeTable();
}

//영화 정보 만들기
void Admin::createMovieInfo() {
	string title;
	string pd;
	short runningTime;
	int price;

	cout << "영화 정보를 입력해주세요." << endl;
	cout << "영화 제목: ";
	cin >> title;
	cout << "영화 감독: ";
	cin >> pd;
	cout << "러닝타임: ";
	cin >> runningTime;
	cout << "영화 가격: ";
	cin >> price;

	//MovieInfo movie(title, pd, runningTime, price);
	MovieInfo* movie = new MovieInfo(title, pd, runningTime, price);
	if (this->infoCount + 1 >= MOVIE_INFO_ARR_SIZE) {
		cout << "최대 영화 개수를 넘었습니다." << endl;
		return;
	}
	else {
		infoTable[this->infoCount] = movie;
		infoCount++;
	}
}

void Admin::printAllMovies(string name) {
	for (int i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		cout << i + 1 << "관" << endl;

		MoviePlay* movie = roomTable[i]->head;
		for (int j = 0; j < roomTable[i]->movieCount; j++) {
			if (movie->info->title == name) {
				movie->info->printInfo();
				cout << "잔여좌석: " << movie->restSeat() << endl;
			}
		}
	}
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

void Admin::deleteMoviePlay(short index, short selectTime) {

}

//티켓 테이블에서 티켓번호로 티켓 정보 찾기
Ticket* Admin::findTicket(int tNumber) {
	Ticket* temp = ticketHead;

	if (ticketTail->ticketNumber < tNumber || tNumber < FIRST_TICKET) {
		return NULL;
	}

	if (ticketTail->ticketNumber == tNumber) {
		return ticketTail;
	}

	while (temp != ticketTail) {
		if (temp->ticketNumber == tNumber) {
			return temp;
		}
		temp = temp->nextTicket;
	}
	/*
	while (ticketHead->nextTicket != ticketTail) {
		if (temp->ticketNumber == tNumber) {
			return temp;
		}
		temp = temp->nextTicket;
	} */

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

//예매 번호로 티켓 삭제 (예매취소)

void Admin::deleteTicket(Ticket* select) {
	/* 좌석 상태 반영 */
	for (short i = 0; i < select->number; i++) {
		select->playInfo->changeSeat(select->seatNumber[i] / 10, select->seatNumber[i] % 10, false);
	}

	/* 삭제하려는 티켓이 Head일때 && Tail일때 */
	if (select == ticketHead && select == ticketTail) {
		select->~Ticket();
		ticketHead = NULL;
		ticketTail = NULL;
	}
	/* 삭제하려는 티켓이 Head일때 */
	else if (select == ticketHead) {
		ticketHead = select->nextTicket;
		select->~Ticket();
	}
	/* 삭제하려는 티켓이 Tail일때 */
	else if (select == ticketTail) {
		Ticket* temp = ticketHead;

		while (temp->nextTicket != ticketTail) {
			temp = temp->nextTicket;
		}

		ticketTail = temp;
		temp->nextTicket = NULL;
		select->~Ticket();
	}
	/* 그 외 (중간에 있을 때) */
	else {
		Ticket* temp = ticketHead;

		while (temp->nextTicket != select) {
			temp = temp->nextTicket;
		}
		temp->nextTicket = select->nextTicket;
		select->~Ticket();
	}
}
void Admin::deleteMovieInfo(short index)
{
	short i;

	//모든 영화관에서 영화정보로 영화 삭제
	for (i = 0; i < roomCount; i++)
	{
		roomTable[i]->deleteMovieInfo(infoTable[index]);
	}

	//배열에서 줄여주기
	for (i = index; i < infoCount; i++)
	{
		infoTable[i] = infoTable[i + 1];
	}
	infoTable[infoCount] = 0x00;
	infoCount--;
}

void Admin::deleteMoviePlay(short roomNumber, short startTime) {


}

Ticket* Admin::addTicket(MoviePlay* movie)
{
	short numberOfHead;                 //인원 수
	short x, y;                         //좌표 변수
	short restSeat = movie->restSeat(); //잔여 좌석
	short i, temp;                      //반복문
	short count;                    //몇명 예매했는지
	bool check;
	int key; //입력된 키보드 값

	system("cls");
	movie->printSeat();

	//인원수 입력받기, 예외처리 : 0또는 음수거나 잔여좌석보다 크게 입력받을 때
	do
	{
		gotoxy(0, SIZE_ROW + 1);
		cout << "인원 수를 입력하세요 : ";
		gotoxy(0, SIZE_ROW + 2);
		cin >> numberOfHead;
		check = (numberOfHead <= 0) || (numberOfHead > restSeat);
		if (check)
		{
			gotoxy(0, SIZE_ROW + 3);
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
	movie->printSeat();
	gotoxy(0, SIZE_ROW + 1);

	cout << "원하는 좌석을 선택하세요." << endl << endl;
	printf("%2d", count);
	cout << "명 남았습니다." << endl;
	x = 2; y = 2;
	gotoxy(2 * x, y);


	while (count != 0)
	{

		//while (_kbhit())
		//{
		key = _getch();
		/* 방향키 눌렸을 때 */
		if (key == 224 || key == 0)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y > 2)
				{
					y--;
					gotoxy(2 * x, y);
				}
				break;
			case 75:
				if (x > 2)
				{
					x--;
					gotoxy(2 * x, y);
				}
				break;
			case 77:
				if (x < SIZE_COLUMN + 1)
				{
					x++;
					gotoxy(2 * x, y);
				}
				break;
			case 80:
				if (y < SIZE_ROW + 1)
				{
					y++;
					gotoxy(2 * x, y);
				}
				break;
			default:
				break;
			}
		}
		else
		{
			/* 엔터가 눌렸을 때 */
			if (key == 13)
			{
				check = false;

				temp = (y - 1) * 10 + (x - 1);

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
					gotoxy(1, SIZE_COLUMN + 3);
					printf("%c열 %d 취소 성공!       \n", 63 + y, x - 1);
					printf("%2d", count);
					gotoxy(2 * x, y);
				}
				/* 배열 내에 temp와 같은 값이 저장되어 있지 않으면(신규 좌석 예매)  */
				else
				{
					/* 이미 예매된 좌석이면 (checkSeat가 true면 이미 예매된 좌석으로 일단 구현) */
					if (movie->checkSeat(y - 1, x - 1))
					{
						gotoxy(1, SIZE_ROW + 3);
						cout << "이미 예매된 좌석입니다.";
						gotoxy(2 * x, y);
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
						gotoxy(1, SIZE_ROW + 3);
						printf("%c열 %d 예매 성공!       \n", 63 + y, x - 1);
						printf("%2d", count);
						gotoxy(2 * x, y);
					}
				}
				//	}
			}
		}
	}

	gotoxy(1, SIZE_ROW + 5);
	if (getMoney(movie->info, numberOfHead) == false) {
		cout << "예매가 취소되었습니다." << endl;
		return NULL;
	}

	Ticket* newTicket;
	/* 예매가 완료되면 tail다음에 티켓 추가해주기 */
	if (ticketHead == 0x00)                 //첫 티켓일 경우 tail과 head에 추가
	{

		newTicket = new Ticket(numberOfHead, FIRST_TICKET, seatArr, movie, 0x00);

		ticketHead = newTicket;
		ticketTail = newTicket;
	}
	else
	{
		newTicket = new Ticket(numberOfHead, ticketTail->ticketNumber + 1, seatArr, movie, 0x00);
		ticketTail->nextTicket = newTicket;
		ticketTail = newTicket;
	}

	/* MoviePlay에 좌석 정보 반영 */
	for (i = 0; i < numberOfHead; i++) {
		movie->changeSeat(seatArr[i] / 10, seatArr[i] % 10, true);
	}

	gotoxy(1, 1);


	return newTicket;
}

bool Admin::getMoney(MovieInfo* minfo, short numberOfHead)
{
	//금액

	int i;
	int insertMoney = 0; //입력 금액
	int total; //총 금액
	int money = 0;	//입력 된 금액

	total = minfo->getInfo().price * numberOfHead;

	cout << "무엇으로 결제하시겠습니까 ? 1. 현금  2. 카드" << endl;
	cin >> i;

	if (i == 1) {

		while (money < total) {
			if (insertMoney == -1) {
				return false;
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
		Sleep(3000);

		cout << "거스름돈 : " << money - total << endl;

		cout << "결제가 완료되었습니다." << endl;

		Sleep(2000);
		system("cls");
		return true;
	}


	else if (i == 2) {
		cout << "카드를 넣어주세요." << endl;
		Sleep(3000);
		cout << "결제가 완료되었습니다." << endl;
		Sleep(2000);
		system("cls");
		return true;
	}

	else {
		cout << "잘못 입력하셨습니다. " << endl;
	}



}

void Admin::gotoxy(short x, short y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

Admin::~Admin() {

}