#include "Header.hpp"

Ticket::Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket) {
	number = n;
	ticketNumber = tNumber;
	seatNumber = sNumber;
	playInfo = pInfo;
	nextTicket = nTicket;
}

Ticket::~Ticket() {
	cout << "■                             예매번호 : " << this->ticketNumber << endl<<endl;
	cout << "■                             해당 예매가 정상 취소 되었습니다." << endl;

}


void Ticket::printTicket() {
	cout << "■                          -- 예매정보 확인 --" << endl << endl;
	cout << "■                          예매번호 : " << ticketNumber << endl;
	/* 영화 시작, 종료 시간과 영화제목 출력 */
	/* 문제점 : 영화관 출력 불가 */
	// 출력 형태 변경 gy
	cout << "■                          예매영화 : " << playInfo->info->title << endl;
	cout << "■                          상영시간 : " << to_string(playInfo->startTime / 100) + "시 " + to_string(playInfo->startTime % 100) + "분" +
		" ~ " << to_string(playInfo->endTime / 100) + "시 " + to_string(playInfo->endTime % 100) + "분" << endl;
	cout << "■                          예매인원 : " << number << "명" << endl;
	cout << "■                          예매좌석 : ";
	int i;
	for (i = 0; i < number; i++) {
		printf("%c열 %d", seatNumber[i] / 10 + 64, seatNumber[i] % 10);
		if (i != number - 1) {
			cout << " / ";
		}
		if (i % 3 == 2)
			cout << endl << "■                                     ";
	}
	cout << endl;


}