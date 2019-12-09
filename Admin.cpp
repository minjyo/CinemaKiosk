#include "Header.hpp"

Admin::Admin() {
	ticketHead = NULL;
	ticketTail = NULL;

	//영화관 기본 셋팅
	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		roomTable[i] = new MovieRoom(i);
	}

	infoTable[0] = new MovieInfo("Frozen2", "Jenniffer.L", 143, 8000);
	infoTable[1] = new MovieInfo("Jocker", "토트 필립스", 140, 9000);
	infoTable[2] = new MovieInfo("나를 찾아줘", "김승호", 148, 10000);
	infoTable[3] = new MovieInfo("어벤저스 엔드게임", "안소니 루소", 301, 15000);
	infoTable[4] = new MovieInfo("김정식", "jungsheek", 100, 3000);
	infoCount = 5;

	/* 1관 */
	roomTable[0]->addMovieToRoom(infoTable[1], 1100);
	roomTable[0]->addMovieToRoom(infoTable[0], 1300);
	roomTable[0]->addMovieToRoom(infoTable[1], 1500);
	roomTable[0]->addMovieToRoom(infoTable[0], 1700);
	roomTable[0]->addMovieToRoom(infoTable[1], 1900);
	roomTable[0]->addMovieToRoom(infoTable[0], 2100);

	/* 2관 */
	roomTable[1]->addMovieToRoom(infoTable[2], 900);
	roomTable[1]->addMovieToRoom(infoTable[3], 1130);
	roomTable[1]->addMovieToRoom(infoTable[2], 1500);
	roomTable[1]->addMovieToRoom(infoTable[3], 1730);
	roomTable[1]->addMovieToRoom(infoTable[2], 2100);
	roomTable[1]->addMovieToRoom(infoTable[3], 2330);


	/* 3관 */
	roomTable[2]->addMovieToRoom(infoTable[2], 700);
	roomTable[2]->addMovieToRoom(infoTable[3], 1130);
	roomTable[2]->addMovieToRoom(infoTable[2], 1300);
	roomTable[2]->addMovieToRoom(infoTable[2], 1630);
	roomTable[2]->addMovieToRoom(infoTable[2], 2000);


	/* 4관 */
	roomTable[3]->addMovieToRoom(infoTable[2], 900);
	roomTable[3]->addMovieToRoom(infoTable[1], 1130);
	roomTable[3]->addMovieToRoom(infoTable[0], 1500);
	roomTable[3]->addMovieToRoom(infoTable[3], 1730);
	roomTable[3]->addMovieToRoom(infoTable[1], 2100);
	roomTable[3]->addMovieToRoom(infoTable[3], 2330);


	/* 5관 */
	roomTable[4]->addMovieToRoom(infoTable[2], 900);
	roomTable[4]->addMovieToRoom(infoTable[1], 1130);
	roomTable[4]->addMovieToRoom(infoTable[3], 1500);
	roomTable[4]->addMovieToRoom(infoTable[0], 1730);
	roomTable[4]->addMovieToRoom(infoTable[2], 2100);
	roomTable[4]->addMovieToRoom(infoTable[4], 2330);
}


void Admin::showStatistic() {
	cout << "영화 누적 통계" << endl << endl;
	cout.setf(ios::left);
	Ticket* temp = ticketHead;
	total = 0;

	for (int i = 0; i < infoCount; i++) {
		cout << "■    " << setw(20) << infoTable[i]->title << " : 총 관객 수 " << infoTable[i]->count << " / 총 수입: " << infoTable[i]->count * infoTable[i]->price << endl;
		total += infoTable[i]->count * infoTable[i]->price;
	}
	cout << endl << "■    " << setw(20) << "최종 수입 : " << total << endl;
}

//전체 영화 리스트 출력
void Admin::printInfoTable(void) {

	cout.setf(ios::left);
	cout << setw(6) << "■";
	cout << setw(20) << "영화 이름";
	cout << setw(20) << "영화 가격";
	cout << setw(20) << "영화 감독";
	cout << setw(20) << "런닝 타임" << endl;
	cout << setw(6) << "■";
	cout << "-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < infoCount; i++) {
		cout << setw(3) << "■";
		cout << setw(3) << to_string(i + 1) + ".";
		infoTable[i]->printInfo();
	}
}
//영화관 선택 시 시작시간 순으로 상영영화 출력
void Admin::printTimetable(short index) {
	roomTable[index]->printTimeTable();
}

//영화 정보 만들기
bool Admin::createMovieInfo() {
	string title;
	string pd;
	short runningTime;
	int price;

	cout << "■    영화 추가" << endl;
	cout << "■   +──────────────────────────+" << endl;
	/* 최소 영화 가격은 10000원, 러닝타임 최소 30분 */
	cout << "■    영화 정보를 입력해주세요." << endl;
	cout << "■    영화 제목: ";
	char key = _getch();

	if (key == 8) {
		return false;
	}
	cin >> title;
	cout << "■    영화 감독: ";
	cin >> pd;
	cout << "■    러닝타임: ";
	cin >> runningTime;

	if (!runningTime) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	while (runningTime < 30) {
		cout << "■    입력값 오류입니다. 다시 입력해주세요 : ";
		cin >> runningTime;
		if (!runningTime) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	cout << "■    영화 가격: ";
	cin >> price;
	if (!price) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	while (price < 1000) {
		cout << "■    입력값 오류입니다. 다시 입력해주세요 : ";
		cin >> price;
		if (!price) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	MovieInfo* movie = new MovieInfo(title, pd, runningTime, price);
	if (this->infoCount + 1 >= MOVIE_INFO_ARR_SIZE) {
		cout << "      최대 영화 개수를 넘었습니다." << endl;
		Sleep(3000);
		return false;
	}
	else {
		infoTable[this->infoCount] = movie;
		infoCount++;
	}
	return true;
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

//영화관 내 상영영화 Linked List에 시간 검사 후 생성하기 (movie room의 canaddmovie + addmovie 호출)
bool Admin::addMovie(MovieInfo* info, MovieRoom* room, short selectTime) {
	if (room->addMovieToRoom(info, selectTime) == true) {
		return true;
	}
	else
		return false;
}

//티켓 테이블에서 티켓번호로 티켓 정보 찾기
Ticket* Admin::findTicket(int tNumber) {
	Ticket* temp = ticketHead;
	if (temp == NULL) {
		return NULL;
	}
	if (ticketTail->ticketNumber < tNumber || tNumber < ticketHead->ticketNumber) {
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
	if ((select == ticketHead) && (select == ticketTail)) {
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
	deleteTicketByInfo(infoTable[index]);
	//모든 영화관에서 영화정보로 영화 삭제
	for (i = 0; i < MOVIE_ROOM_ARR_SIZE; i++)
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

void Admin::gotoxy(short x, short y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

Admin::~Admin() {

}

void Admin::deleteTicketByInfo(MovieInfo* info) {
	Ticket* temp = ticketHead;
	Ticket* temp2 = NULL;

	while(1) {
		if (temp == NULL) {
			return;
		}
		if (temp->playInfo->info == info) {
			temp2 = temp->nextTicket;
			deleteTicket(temp);
			temp = temp2;
		}
		else {
			temp = temp->nextTicket;
		}
	}
}
void Admin::deleteTicketByPlay(MoviePlay* play) {
	Ticket* temp = ticketHead;
	Ticket* temp2 = NULL;

	while (1) {
		if (temp == NULL) {
			return;
		}
		if (temp->playInfo == play) {
			temp2 = temp->nextTicket;
			deleteTicket(temp);
			temp = temp2;
		}
		else {
			temp = temp->nextTicket;
		}
	}
}

int Admin::printMoviefromRoom(unsigned short roomNumber, MovieInfo* minfo) {
	int n = roomTable[roomNumber]->printMovieInfo(minfo);
	return n;
}

MoviePlay* Admin::findMoviePlayfromRoom(unsigned short roomNumber, MovieInfo* minfo, int index) {
	MoviePlay* returnMoviePlay = roomTable[roomNumber]->findMoviePlay(minfo, index);
	return returnMoviePlay;
}

int Admin::deleteMoviePlayfromRoom(unsigned short roomNumber, unsigned short startTime) {

	MoviePlay* temp = roomTable[roomNumber]->deleteMoviePlay(startTime);
	if (temp == NULL) {
		return 0;
	}
	else {
		deleteTicketByPlay(temp);
		temp->~MoviePlay();
		return 1;
	}
}


