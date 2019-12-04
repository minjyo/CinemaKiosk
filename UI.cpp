#include "Header.hpp"

/* ����� Ȩ ȭ�� */
int UI::userHome(void) {

	system("cls");

	printf("����� Ȩ ȭ��\n\n");

	printf("����������������������������������������������������������������������\n");
	printf("��  1. ��ȭ ����                   ��\n");
	printf("��  2. Ƽ�� ���� Ȯ��              ��\n");
	printf("����������������������������������������������������������������������\n");


	key = _getch();

	x = 4; y = 4;
	gotoxy(x, y);

	while (1) {
		key = _getch();
		/* ����Ű ������ �� */
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
		/* ���Ͱ� ������ �� */
		else if (key == 13) {
			/* ��ȭ ���� ȭ�� */
			if (y == 4)
				return CHOOSEMOVIE;
			/* Ƽ�� ���� Ȯ�� */
			if (y == 5)
				return TICKET;
		}
	}
}

//��ȭ ���� ���� �� ��ȭ ����Ʈ ����ϴ� ȭ��
int UI::movieList(Admin admin) {
	int y_min;
	cout << "��ȭ ����" << endl;
	//��ü ��ȭ ����Ʈ ���
	admin.printInfoTable();

	cout << "�����Ͻ� ��ȭ�� �������ּ���";
	x = 1; y_min = 3; y = y_min;

	gotoxy(x, y);

	while (1) {
		key = _getch();
		/* ����Ű ������ �� */
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
		/* ���Ͱ� ������ �� */
		else if (key == 13) {
				return (y - y_min);
		}
		else if (key == 104){
			return USER;
		}
		else if (key == 8) {
			return USER;
		}
	}
}
//��ȭ ���� �� ���ϴ� ��ȭ ����Ʈ ����ϴ� ȭ��
int UI::moviePlayList(Admin admin, int index) {
	MovieInfo* movie = admin.infoTable[index];

	system("cls");
	movie->printInfo();
	for (short i = 0; i < MOVIE_ROOM_ARR_SIZE; i++) {
		admin.roomTable[i]->printMovieInfo(movie);
	}

	int room, time;
	cout << "���Ͻô� ��ȭ���� �������ּ��� : ";
	cin >> room;
	cout << "���Ͻô� �ð��� �������ּ��� : ";
	cin >> time;

	int time_index = 0;
	Ticket* ticket = NULL;

	//������ ��ȭ�� �󿵵Ǵ� ��ȭ���� �¼� ���� ����ϰ� �¼� ����
	MoviePlay* temp = admin.roomTable[room - 1]->head;
	while (temp != NULL) {
		if (temp->info == movie) {
			time_index++;
			if (time == time_index) {
				//����
				ticket = admin.addTicket(temp);
			}
		}
		temp = temp->nextPlay;
	}

	//���� ��� ���
	if (ticket != NULL) {
		ticket->printTicket();
	}

	//Ƽ�Ͽ� ���� ���� �߰�
	return USER;
}

//��ȭ ���� �� Ƽ�� ���� Ȯ��(check == false) & ���� ���� Ȯ��(check == true)
int UI::checkTicket(bool check) {
	return 0;
}
//������ Ȩ ȭ��
int UI::adminHome(void) {
	return 0;
}
//��ȭ ���� ȭ��
int UI::movieSetting(void) {
	return 0;
}
//��ȭ�� ���� ȭ��
int UI::roomSetting(void) {
	return 0;
}

void UI::gotoxy(short x, short y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}