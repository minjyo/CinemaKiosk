﻿#include "Header.hpp"

MoviePlay::MoviePlay() {

}


MoviePlay::MoviePlay(short sTime, MovieInfo* minfo, MoviePlay* nextP) {
	//this->seat[SIZE_ROW][SIZE_COLUMN] = { false, };
	unsigned short running_time = minfo->runningTime;

	/* 분의 합이 60분이 넘으면 */
	if (((sTime % 100) + (running_time % 100)) > 60) {
		/* 60분 빼고 1시간 더하니까 40을 더함 */
		this->endTime += 40;
	}
	else {
		this->endTime = sTime + running_time;
	}
	this->info = minfo;
	//this->nextPlay = nextP;
	nextPlay = NULL;
	this->startTime = sTime;
}

MoviePlay::~MoviePlay() {
}

//좌석 현황 출력. 예매 가능하면 ▩, 안되면 ■
void MoviePlay::printSeat() {
	int i, j;
	printf("                        #############################################\n");
	printf("                        #                                           #\n");
	printf("                        #          ┌───────────────────┐            #\n");
	printf("                        #          │       screen      │            #\n");
	printf("                        #          └───────────────────┘            #\n");
	cout << "                        #           ";
	for (i = 1; i < SIZE_COLUMN/2 + 1; i++) {
		printf("%2d", i);
	}
	cout << "    ";
	for (i = SIZE_COLUMN/2 + 1; i < SIZE_COLUMN + 1; i++) {
		printf("%2d", i);
	}
	cout << "            #\n                        #         ";
	for (i = 0; i < SIZE_ROW; i++) {
		printf(" %c ", 65 + i);
		for (j = 0; j < SIZE_COLUMN/2 ; j++) {
			if (seat[i][j] == true)
				cout << "▩";
			else
				cout << "□";
		}
		cout << "    ";
		for (j = SIZE_COLUMN / 2; j < SIZE_COLUMN; j++) {
			if (seat[i][j] == true)
				cout << "▩";
			else
				cout << "□";
		}
		cout << "           #\n                        #         ";
	}
	printf("                                  #\n");
	printf("                        #                                           #\n");
	printf("                        #                                           #\n");
	printf("                        #                                           #\n");
	printf("                        #                                           #\n");
	printf("                        #                                           #\n");
	printf("                        #############################################\n");
}

//해당 좌표에 있는 좌석이 예매 가능한지 리턴. 자리가 이미 예약되어 있으면 True, 그렇지 않을 경우 False 리턴.
bool MoviePlay::checkSeat(short x, short y) {
	if (x > SIZE_COLUMN || y > SIZE_ROW || x < 1 || y < 1) {
		cout << "잘못된 입력입니다" << endl;
	}
	else {
		if (seat[x - 1][y - 1] == true) {
			return true;
		}
		else if (seat[x - 1][y - 1] == false) {
			return false;
		}
	}
	return false;
}

//예매할 때는 status True, 취소할때는 Status False.
void MoviePlay::changeSeat(short x, short y, bool status) {
	/*
	if (x > 5 || y > 5 || x < 1 || y < 1) {
		cout << "잘못된 입력입니다" << endl;
	}
	else {

		if (status == true) {
			if (checkSeat(x, y) == true) {
				cout << "좌석이 찼습니다." << endl;
			}
			else {
				seat[x - 1][y - 1] = true;
				cout << "좌석 예매 완료" << endl;
			}
		}
		else {
			if (checkSeat(x, y) == false) {
				cout << "좌석이 예약된 상태가 아닙니다." << endl;
			}
			else {
				seat[x - 1][y - 1] = false;
				cout << "좌석 취소 완료" << endl;
			}
		}
		printSeat();

	} */
	seat[x - 1][y - 1] = status;
}

//예매 가능한 빈자리 리턴.
unsigned short MoviePlay::restSeat() {
	unsigned short count = 0;
	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COLUMN; j++) {
			if (seat[i][j] == false) {
				count++;
			}
		}
	}
	return count;
}