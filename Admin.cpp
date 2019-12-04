#include "Header.hpp"

Admin::Admin() {
	ticketHead = NULL;
	ticketTail = NULL;

	//��ȭ�� �⺻ ����
	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		roomTable[i] = new MovieRoom(i);
	}

	infoTable[0] = new MovieInfo("Frozen2", "Jenniffer.L", 143, 8000);
	infoTable[1] = new MovieInfo("Jocker", "��Ʈ �ʸ���", 140, 9000);
	infoTable[2] = new MovieInfo("���� ã����", "���ȣ", 148, 10000);
	infoTable[3] = new MovieInfo("����� �������", "�ȼҴ� ���", 301, 15000);
	infoCount = 4;

	/* 1�� */
	roomTable[0]->addMovieToRoom(infoTable[0], 900);
	roomTable[0]->addMovieToRoom(infoTable[1], 1100);
	roomTable[0]->addMovieToRoom(infoTable[0], 1300);
	roomTable[0]->addMovieToRoom(infoTable[1], 1500);
	roomTable[0]->addMovieToRoom(infoTable[0], 1700);
	roomTable[0]->addMovieToRoom(infoTable[1], 1900);
	roomTable[0]->addMovieToRoom(infoTable[0], 2100);

	/* 2�� */
	roomTable[1]->addMovieToRoom(infoTable[2], 900);
	roomTable[1]->addMovieToRoom(infoTable[3], 1130);
	roomTable[1]->addMovieToRoom(infoTable[2], 1500);
	roomTable[1]->addMovieToRoom(infoTable[3], 1730);
	roomTable[1]->addMovieToRoom(infoTable[2], 2100);
	roomTable[1]->addMovieToRoom(infoTable[3], 2330);

	/* 4�� */
	roomTable[3]->addMovieToRoom(infoTable[2], 900);
	roomTable[3]->addMovieToRoom(infoTable[3], 1130);
	roomTable[3]->addMovieToRoom(infoTable[2], 1500);
	roomTable[3]->addMovieToRoom(infoTable[3], 1730);
	roomTable[3]->addMovieToRoom(infoTable[2], 2100);
	roomTable[3]->addMovieToRoom(infoTable[3], 2330);
}

//��ü ��ȭ ����Ʈ ���
void Admin::printInfoTable(void) {
	cout << setw(6) << "   ";
	cout.setf(ios::left);
	cout << setw(20) << "��ȭ �̸�";
	cout << setw(20) << "��ȭ ����";
	cout << setw(20) << "��ȭ ����";
	cout << setw(20) << "���� Ÿ��" << endl;
	cout << setw(6) << "   ";
	cout << "-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < infoCount; i++) {
		cout << setw(6) << to_string(i + 1) + ".";
		infoTable[i]->printInfo();
	}
}
//��ȭ�� ���� �� ���۽ð� ������ �󿵿�ȭ ���
void Admin::printTimetable(short index) {
	roomTable[index]->printTimeTable();
}

//��ȭ ���� �����
void Admin::createMovieInfo() {
	string title;
	string pd;
	short runningTime;
	int price;

	/* �ּ� ��ȭ ������ 10000��, ����Ÿ�� �ּ� 30�� */
	cout << "��ȭ ������ �Է����ּ���." << endl;
	cout << "��ȭ ����: ";
	cin >> title;
	cout << "��ȭ ����: ";
	cin >> pd;
	cout << "����Ÿ��: ";
	cin >> runningTime;
	while (runningTime < 30) {
		cout << "�Է°� �����Դϴ�. �ٽ� �Է����ּ��� : ";
		cin >> runningTime;
	}
	cout << "��ȭ ����: ";
	cin >> price;
	while (price < 1000) {
		cout << "�Է°� �����Դϴ�. �ٽ� �Է����ּ��� : ";
		cin >> price;
	}

	MovieInfo* movie = new MovieInfo(title, pd, runningTime, price);
	if (this->infoCount + 1 >= MOVIE_INFO_ARR_SIZE) {
		cout << "�ִ� ��ȭ ������ �Ѿ����ϴ�." << endl;
		return;
	}
	else {
		infoTable[this->infoCount] = movie;
		infoCount++;
	}
}

void Admin::printAllMovies(string name) {
	for (int i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		cout << i + 1 << "��" << endl;

		MoviePlay* movie = roomTable[i]->head;
		for (int j = 0; j < roomTable[i]->movieCount; j++) {
			if (movie->info->title == name) {
				movie->info->printInfo();
				cout << "�ܿ��¼�: " << movie->restSeat() << endl;
			}
		}
	}
}

//��ȭ�� ��� ����, �Ұ���
void Admin::setMovieRoomStatus(MovieRoom& room, bool status) {
	room.setStatus(status);
	cout << "�ش� ��ȭ�� ����� " << (status ? "����" : "�Ұ���") << "���� ����Ǿ����ϴ�." << endl;
}

//��ȭ�� �� �󿵿�ȭ Linked List�� �ð� �˻� �� �����ϱ� (movie room�� canaddmovie + addmovie ȣ��)
void Admin::addMovie(MovieInfo* info, MovieRoom& room, short selectTime) {
	if (room.canAddMovie(info, selectTime)) {
		room.addMovieToRoom(info, selectTime);
		cout << "��ȭ�� �߰��Ǿ����ϴ�." << endl;
		room.printTimeTable();
		return;
	}
	cout << "�ش� �ð��� ��ȭ�� �߰��� �� �����ϴ�. �ٽ� �������ּ���." << endl;
}

//Ƽ�� ���̺��� Ƽ�Ϲ�ȣ�� Ƽ�� ���� ã��
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

//���� ��ȣ�� Ƽ�� ���� ���
void Admin::printTicket(int tNumber) {
	Ticket* temp = findTicket(tNumber);

	if (temp != NULL) {
		temp->printTicket();
		return;
	}
	cout << "�ش� ��ȣ�� ���ŵ� ���� ������ �����ϴ�." << endl;
}

//���� ��ȣ�� Ƽ�� ���� (�������)

void Admin::deleteTicket(Ticket* select) {
	/* �¼� ���� �ݿ� */
	for (short i = 0; i < select->number; i++) {
		select->playInfo->changeSeat(select->seatNumber[i] / 10, select->seatNumber[i] % 10, false);
	}
	/* �����Ϸ��� Ƽ���� Head�϶� && Tail�϶� */
	if (select == ticketHead && select == ticketTail) {
		select->~Ticket();
		ticketHead = NULL;
		ticketTail = NULL;
	}
	/* �����Ϸ��� Ƽ���� Head�϶� */
	else if (select == ticketHead) {
		ticketHead = select->nextTicket;
		select->~Ticket();
	}
	/* �����Ϸ��� Ƽ���� Tail�϶� */
	else if (select == ticketTail) {
		Ticket* temp = ticketHead;

		while (temp->nextTicket != ticketTail) {
			temp = temp->nextTicket;
		}

		ticketTail = temp;
		temp->nextTicket = NULL;
		select->~Ticket();
	}
	/* �� �� (�߰��� ���� ��) */
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

	//��� ��ȭ������ ��ȭ������ ��ȭ ����
	for (i = 0; i < MOVIE_ROOM_ARR_SIZE; i++)
	{
		roomTable[i]->deleteMovieInfo(infoTable[index]);
	}

	//�迭���� �ٿ��ֱ�
	for (i = index; i < infoCount; i++)
	{
		infoTable[i] = infoTable[i + 1];
	}
	infoTable[infoCount] = 0x00;
	infoCount--;
}

void Admin::deleteMoviePlay(short roomNumber, short startTime) {
	roomTable[roomNumber]->deleteMoviePlay(startTime);
}

Ticket* Admin::addTicket(MoviePlay* movie)
{
	short numberOfHead;                 //�ο� ��
	short x, y;                         //��ǥ ����
	short restSeat = movie->restSeat(); //�ܿ� �¼�
	short i, temp;                      //�ݺ���
	short count;                    //��� �����ߴ���
	bool check;
	int key; //�Էµ� Ű���� ��

	system("cls");
	movie->printSeat();

	//�ο��� �Է¹ޱ�, ����ó�� : 0�Ǵ� �����ų� �ܿ��¼����� ũ�� �Է¹��� ��
	do
	{
		gotoxy(0, SIZE_ROW + 1);
		cout << "�ο� ���� �Է��ϼ��� : ";
		gotoxy(0, SIZE_ROW + 2);
		cin >> numberOfHead;
		check = (numberOfHead <= 0) || (numberOfHead > restSeat);
		if (check)
		{
			gotoxy(0, SIZE_ROW + 3);
			cout << "�ܿ� �¼����� �����ϴ�." << endl;
		}
	} while (check);

	count = numberOfHead;

	//�Է¹��� �ο�����ŭ short �迭 ����� & -1�� �ʱ�ȭ
	short* seatArr = new short[numberOfHead];
	for (i = 0; i < numberOfHead; i++)
	{
		seatArr[i] = -1;
	}
	system("cls");
	movie->printSeat();
	gotoxy(0, SIZE_ROW + 1);

	cout << "���ϴ� �¼��� �����ϼ���." << endl << endl;
	printf("%d", count);
	cout << "�� ���ҽ��ϴ�." << endl;
	x = 2; y = 2;
	gotoxy(2 * x, y);

	while (count != 0)
	{
		//while (_kbhit())
		//{
		key = _getch();
		/* ����Ű ������ �� */
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
			/* ���Ͱ� ������ �� */
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
				/* �̹� �迭 ���� temp�� ���� ���� ����Ǿ� ������(���� �¼� ���)  */
				if (check)
				{
					cout << "��";
					count++;
					gotoxy(1, SIZE_COLUMN + 3);
					printf("%c�� %d ��� ����!       \n", 63 + y, x - 1);
					printf("%2d", count);
					gotoxy(2 * x, y);
				}
				/* �迭 ���� temp�� ���� ���� ����Ǿ� ���� ������(�ű� �¼� ����)  */
				else
				{
					/* �̹� ���ŵ� �¼��̸� (checkSeat�� true�� �̹� ���ŵ� �¼����� �ϴ� ����) */
					if (movie->checkSeat(y - 1, x - 1))
					{
						gotoxy(1, SIZE_ROW + 3);
						cout << "�̹� ���ŵ� �¼��Դϴ�.";
						gotoxy(2 * x, y);
					}
					/* ���ŵ� �¼��� �ƴϸ� �ű� ���� */
					else
					{
						i = 0;
						while (seatArr[i] != -1)
						{
							i++;
						}
						seatArr[i] = temp;
						cout << "��";
						count--;
						gotoxy(1, SIZE_ROW + 3);
						printf("%c�� %d ���� ����!       \n", 63 + y, x - 1);
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
		cout << "���Ű� ��ҵǾ����ϴ�." << endl;
		return NULL;
	}

	Ticket* newTicket;
	/* ���Ű� �Ϸ�Ǹ� tail������ Ƽ�� �߰����ֱ� */
	if (ticketHead == 0x00)                 //ù Ƽ���� ��� tail�� head�� �߰�
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

	/* MoviePlay�� �¼� ���� �ݿ� */
	for (i = 0; i < numberOfHead; i++) {
		movie->changeSeat(seatArr[i] / 10, seatArr[i] % 10, true);
	}

	gotoxy(1, 1);

	return newTicket;
}

bool Admin::getMoney(MovieInfo* minfo, short numberOfHead)
{
	//�ݾ�
	int i;
	int insertMoney = 0; //�Է� �ݾ�
	int total; //�� �ݾ�
	int money = 0;	//�Է� �� �ݾ�

	total = minfo->getInfo().price * numberOfHead;

	cout << "�������� �����Ͻðڽ��ϱ� ? 1. ����  2. ī��" << endl;
	cin >> i;

	if (i == 1) {

		while (money < total) {
			if (insertMoney == -1) {
				return false;
			}
			else {
				cout << "�� �ݾ� : " << total << endl;
				cout << "���� �ݾ� : " << total - money << endl;
				cout << "�ݾ��� �־��ּ���. (-1 : ���)" << endl;
				cin >> insertMoney;
				while (insertMoney < 10) {
					cout << "�Է°� �����Դϴ�. �ٽ� �Է����ּ��� : ";
					cin >> insertMoney;
				}
				money += insertMoney;
			}
		}
		cout << "���� ������";
		for (int i = 0; i < 10; i++) {
			cout << ".";
			Sleep(300);
		}
		cout << endl;
		cout << "�Ž����� : " << money - total << endl;

		cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
		
		Sleep(2000);
		system("cls");
		return true;
	}


	else if (i == 2) {
		cout << "ī�带 �־��ּ���" << endl;
		Sleep(2000);
		cout << "���� �������Դϴ�";
		for (int i = 0; i < 10; i++) {
			cout << ".";
			Sleep(300);
		}
		cout << endl;
		cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
		Sleep(2000);
		system("cls");
		return true;
	}
	else {
		cout << "�߸� �Է��ϼ̽��ϴ�. " << endl;
	}
}

void Admin::gotoxy(short x, short y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

Admin::~Admin() {

}