#include "Header.hpp"

Ticket::Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket) {
	number = n;
	ticketNumber = tNumber;
	seatNumber = sNumber;
	playInfo = pInfo;
	nextTicket = nTicket;
}

/* 소멸자, 취소된 예매번호 출력 */
Ticket::~Ticket() {
	cout << "■                             예매번호 : " << this->ticketNumber << endl << endl;
	cout << "■                             해당 예매가 정상 취소 되었습니다." << endl;
}


/* 티켓 정보 출력 */
void Ticket::printTicket() {
	cout << "■                          -- 예매정보 확인 --" << endl << endl;
	cout << "■                          예매번호 : " << ticketNumber << endl;
	cout << "■                          예매영화 : " << playInfo->info->title << endl;
	cout << "■                          상영시간 : " << to_string(playInfo->startTime / 100) + "시 " + to_string(playInfo->startTime % 100) + "분 ~ " << to_string(playInfo->endTime / 100) + "시 " + to_string(playInfo->endTime % 100) + "분" << endl;
	cout << "■                          예매인원 : " << number << "명" << endl;
	cout << "■                          예매좌석 : ";
	for (int i = 0; i < number; i++) {
		printf("%c열 %d", seatNumber[i] / 10 + 64, seatNumber[i] % 10);
		if (i != number - 1) {
			cout << " / ";
		}
		if (i % 3 == 2)
			cout << endl << "■                                     ";
	}
	cout << endl;
	cout << "■                          총 금액  : " << number * (playInfo->info->price) << "원" << endl;
	cout << endl;
}