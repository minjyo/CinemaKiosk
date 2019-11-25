#include "header.hpp"

Admin::Admin() {
	ticketHead = NULL;
	ticketTail = NULL;
}

//전체 영화 리스트 출력
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

void Admin::printAllMovies(string name){
    for(int i=0; i<MOVIE_ROOM_ARR_SIZE; i++){
        cout<< i+1 << "관" << endl;
        
        MoviePlay* movie = roomTable[i]->head;
        for(int j=0; j<roomTable[i]->movieCount; j++){
            if(movie->info->title==name){
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

//예매 번호로 티켓 삭제 (예매취소)
void Admin::deleteTicket(int tNumber) {
	//예매 정보 없을 경우
	if(ticketTail->ticketNumber < tNumber){
		cout << "해당 번호로 예매된 예매 정보가 없습니다." << endl;
	}
	else{
		Ticket* temp = ticketHead;
		while(temp->nextTicket->ticketNumber < tNumber){
			temp = temp->nextTicket;
		}
		//삭제
		if(temp->nextTicket->ticketNumber == tNumber){
			Ticket* temp2 = temp->nextTicket;			//삭제될 티켓
			temp->nextTicket = temp2->nextTicket;
			temp2->~Ticket();
		}
		else{
			cout << "해당 번호로 예매된 예매 정보가 없습니다." << endl;
		}
	}


}
void Admin::deleteMovieInfo(short index)
{
	short i;

	//모든 영화관에서 영화정보로 영화 삭제
	for (i = 0; i < MOVIE_ROOM_ARR_SIZE; i++)
	{
		roomTable[i]->deleteMovieInfo(infoTable[index]);
	}

	//배열에서 줄여주기
	for (i = index; i < maxIndex; i++)
	{
		infoTable[i] = infoTable[i + 1];
	}
	infoTable[maxIndex] = 0x00;
	maxIndex--;
}

void Admin::addTicket(MoviePlay* movie)
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
	cout << "원하는 좌석을 선택하세요." << endl;
	cout << "  명 남았습니다." << endl;
	x=1; y=1;

	while (count != 0)
	{

		while (_kbhit())
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
			}
			else
			{
				/* 엔터가 눌렸을 때 */
				if (key == 13)
				{
					check = false;
					temp = (x-1) * 10 + (y-1);

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
						gotoxy(0, SIZE_ROW + 1);
						printf("%2d", count);
					}
					/* 배열 내에 temp와 같은 값이 저장되어 있지 않으면(신규 좌석 예매)  */
					else
					{
						/* 이미 예매된 좌석이면 (checkSeat가 true면 이미 예매된 좌석으로 일단 구현) */
						if (movie->checkSeat(x, y))
						{
							gotoxy(0, SIZE_ROW + 2);
							cout << "이미 예매된 좌석입니다.";
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
							gotoxy(0, SIZE_ROW + 1);
							printf("%2d", count);
						}
					}
				}
				/* 후에 뒤로가기 키 구현 */
			}
		}

		gotoxy(2 * x, y);
	}

	/* 예매가 완료되면 tail다음에 티켓 추가해주기 */
	if (ticketHead == 0x00)                 //첫 티켓일 경우 tail과 head에 추가
	{
		Ticket newTicket(numberOfHead, 100001, seatArr, movie, 0x00);
		ticketHead = &newTicket;
		ticketTail = &newTicket;
	}
	else
	{
		Ticket newTicket(numberOfHead, ticketTail->ticketNumber + 1, seatArr, movie, 0x00);
		ticketTail->nextTicket = &newTicket;
		ticketTail = &newTicket;
	}

	/* MoviePlay에 좌석 정보 반영 */
	for (i = 0; i < numberOfHead; i++) {
		movie->changeSeat(seatArr[i] / 10, seatArr[i] % 10, true);
	}
}

void Admin::gotoxy(short x, short y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
