#include "header.hpp"

Ticket::Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket) {
	number = n;
	ticketNumber = tNumber;
	seatNumber = sNumber;
	playInfo = pInfo;
	nextTicket = nTicket;
}

Ticket::~Ticket() {
	cout << "예매번호 : " << this->ticketNumber << endl;
	cout << "해당 예매가 정상 취소 되었습니다." << endl;
}

void Ticket::printTicket() {
	Info temp = playInfo->info->getInfo();
	cout << "예매정보 확인" << endl;
	cout << "예매번호 : " << ticketNumber << endl;
	/* 영화 시작, 종료 시간과 영화제목 출력 */
	/* 문제점 : 영화관 출력 불가 */
	cout << "예매영화 : " << playInfo->startTime / 100 << ":" << playInfo->startTime % 100;
	cout << "~" << playInfo->endTime / 100 << ":" << playInfo->endTime % 100 << "  " << temp.title << endl;
	cout << "예매인원 : " << number << endl;
	cout << "예매좌석 : ";
	int i;
	for (i = 0; i < number; i++) {

		printf("%c열 %d / ", seatNumber[i] / 10 + 64, seatNumber[i] % 10);

	}
	cout << endl;
}