﻿//
//  Header.hpp
//  CinemaKiosk
//
//  Created by minjyo on 12/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <fstream>

#define SIZE_COLUMN 8
#define SIZE_ROW 8
#define MOVIE_INFO_ARR_SIZE 10
#define MOVIE_ROOM_ARR_SIZE 5
#define FIRST_TICKET 100001

#define USER 10
#define CHOOSEMOVIE 11
#define CHOOSEROOM 12
#define CHOOSETIME 13
#define CHECKTICKET 14
#define CHOOSESEAT 15
#define CHECKINFO 16
#define CHECKMONEY 17

#define ADMIN 20
#define MANMOVIE 21
#define MAKEMOVIE 22
#define DELETEALL 23
#define MANROOM 24
#define ADDMOVIE 25
#define DELETEMOVIE 26
#define STATISTICS 27

using namespace std;

class MovieInfo {
public:
	string title;
	string pd;
	short runningTime;
	int price;
	int count;

	MovieInfo(string title, string pd, short runningTime, int price);
	void printInfo();
};

/* 상영영화 객체 (Linked list) */
class MoviePlay {
private:
	bool seat[SIZE_ROW][SIZE_COLUMN] = { false, };
public:
	/* 생성자 & 소멸자 */
	MoviePlay();
	MoviePlay(short sTime, MovieInfo* mInfo, MoviePlay* nextP);
	~MoviePlay();

	/* 영화 정보*/
	MovieInfo* info;    
	/* 현재 관 다음 상영 영화 */
	MoviePlay* nextPlay;               

	void changeSeat(short x, short y, bool status); //좌석 입력 받아서 예매
	bool checkSeat(short x, short y); //해당 좌석이 예매 가능한지

	void printSeat();
	unsigned short restSeat();
	unsigned short startTime;           //시작 시간
	unsigned short endTime;             //종료 시간
};

class MovieRoom {
private:
	char roomNumber;
	bool status;
public:
	MoviePlay* head = new MoviePlay;
	unsigned short movieCount;
	MovieRoom(char roomNumber);
	~MovieRoom();
	unsigned short getEndTime(unsigned short startTime, unsigned short runningTime); //시작시간, 러닝타임으로 종료시간 리턴
	void deleteMovieInfo(MovieInfo* info);  //영화 정보 삭제하면서 해당 관 내 상영영화 모두 삭제
	int printMovieInfo(MovieInfo* info);  //영화 정보 삭제하면서 해당 관 내 상영영화 모두 삭제
	void setStatus(bool status);
	int canAddMovie(MovieInfo* info, unsigned short select); //영화관에 영화 추가 가능한지
	bool addMovieToRoom(MovieInfo* info, unsigned short select); // 영화관에 영화 추가
	void printTimeTable(); //영화관의 영화 타임 테이블 출력
	int deleteMoviePlay(short starttime); //반환타입은 삭제한 영화 개수
	MoviePlay* findMoviePlay(MovieInfo * minfo, int index);
};

/* 예매 정보 객체 */
class Ticket
{
public:
	short number;						//인원 수
	short* seatNumber;					//좌석 번호
	MoviePlay* playInfo;               //상영 영화 정보
	int ticketNumber;					//예매번호
	Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket);
	~Ticket();
	Ticket* nextTicket;
	void printTicket();            //예매 관련 정보 출력
};

/* 관리자 객체 */
class Admin
{
public:
	Admin();
	~Admin();
	short infoCount = 0;
	short roomCount = 0;
	short total = 0;

	MovieInfo* infoTable[MOVIE_INFO_ARR_SIZE];
	MovieRoom* roomTable[MOVIE_ROOM_ARR_SIZE];

	Ticket* ticketHead;
	Ticket* ticketTail;

	void showStatistic();

	/* 화면 출력 관련 함수 */
	void printInfoTable(void);               //영화 리스트 출력 화면 (for문)
	void printTimetable(short index);  //영화관 선택 시 시작시간 순으로 상영영화 출력(상영 영화 추가 제거 화면)

	void printAllMovies(string name); //해당 영화를 선택했을 때 그 영화의 모든 관에서의 상영 정보 출력

	/* 영화 정보 관련 함수 (추가, 삭제) */
	bool createMovieInfo();   //영화 정보 만들기
	void deleteMovieInfo(short index);   //영화 정보 삭제하면서 해당 상영영화 모두 삭제

	/* 영화관 관련 함수 (영화관&좌석 상태 관리, 상영 영화 추가, 삭제) */
	void setMovieRoomStatus(MovieRoom& room, bool status);            //영화관 사용 가능, 불가능
	void addMovie(MovieInfo* info, MovieRoom& room, short selectTime);       //영화관 내 상영영화 Linked List에 시간 검사 후 생성하기 (movie room의 canaddmovie + addmovie 호출)
	void deleteMoviePlay(short roomNumber, short startTime);  //시작시간 정보로 해당 영화관 내 상영영화 삭제하기

	/* 유저 관련 함수 */
	Ticket* findTicket(int tNumber);     //유저 테이블에서 티켓번호로 User* 찾기

	void printTicket(int tNumber);        //예매 번호로 티켓 정보 출력 (예매확인 창)
	void deleteTicket(Ticket* select);    //예매 번호로 티켓 삭제 (예매취소)

	void gotoxy(short x, short y);
};

class UI {
public:
	int key;
	int x, y;
	int userHome(void);					//사용자 홈 화면
	int chooseMovie(Admin admin, int* index);				//영화 예매 선택 시 영화 리스트 출력하는 화면

	int chooseRoom(Admin admin, int* room_index, int movie_index, MovieInfo** movie);			//영화 선택 시 상영하는 영화 리스트 출력하는 화면

	int chooseTime(Admin admin, int room_index, int* movie_index, MovieInfo* movie, MoviePlay** play);
	int checkTicket(Admin* admin);		//영화 예매 후 티켓 정보 확인(check == false) & 예매 정보 확인(check == true)

	int chooseSeat(Admin admin, MoviePlay* play, Ticket** newTicket);
	int checkInfo(Ticket* newTicket);
	int checkMoney(Admin* admin, Ticket* newTicket, MovieInfo* movie);

	int adminHome(void);					//관리자 홈 화면
	int manMovie(void);						//영화 관리 화면
	int makeMovie(Admin* admin);			//영화관리 - 영화 추가
	int deleteAll(Admin* admin);			//영화관리 - 영화 삭제

	int manRoom(int* room_index);						//영화관 관리 화면
	int addMovie(Admin* admin, int room_index);					//영화관 관리 - 상영 영화 추가
	int deleteMovie(Admin* admin, int room_index);						//영화관 관리 - 상영 영화 삭제
	int showStatistics(Admin* admin);

	void gotoxy(short x, short y);
	void printBorder(void);
};