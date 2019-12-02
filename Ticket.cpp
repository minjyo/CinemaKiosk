#include "Header.hpp"

Ticket::Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket) {
	number = n;
	ticketNumber = tNumber;
	seatNumber = sNumber;
	playInfo = pInfo;
	nextTicket = nTicket;
}

Ticket::~Ticket() {
	cout << "���Ź�ȣ : " << this->ticketNumber << endl;
	cout << "�ش� ���Ű� ���� ��� �Ǿ����ϴ�." << endl;
}

void Ticket::printTicket() {
	Info temp = playInfo->info->getInfo();
	cout << "-- �������� Ȯ�� --" << endl << endl;
	cout << "���Ź�ȣ : " << ticketNumber << endl;
	/* ��ȭ ����, ���� �ð��� ��ȭ���� ��� */
	/* ������ : ��ȭ�� ��� �Ұ� */
	cout << "���ſ�ȭ : " << playInfo->startTime / 100 << ":" << playInfo->startTime % 100;
	cout << "~" << playInfo->endTime / 100 << ":" << playInfo->endTime % 100 << "  " << temp.title << endl;
	cout << "�����ο� : " << number << endl;
	cout << "�����¼� : ";
	int i;
	for (i = 0; i < number; i++) {
		printf("%c�� %d / ", seatNumber[i] / 10 + 64, seatNumber[i] % 10);
	}
	cout << endl;
}