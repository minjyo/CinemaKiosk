//
//  Header.hpp
//  CinemaKiosk
//
//  Created by minjyo on 12/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//
#pragma once
#define SIZE_COLUMN 5
#define SIZE_ROW 5
#define MOVIE_INFO_ARR_SIZE 10
#define MOVIE_ROOM_ARR_SIZE 10

#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Info {
	string title;
	string pd;
	short runningTime;
	int price;
};

class MovieInfo {
public:
	MovieInfo();
	MovieInfo(string title, string pd, short runningTime, int price);
	Info getInfo();
	void printInfo();
	MovieInfo* nextInfo;

private:
	string title;
	string pd;
	short runningTime;
	int price;
};

/* 상영영화 객체 (Linked list) */
class MoviePlay {

private:
	bool seat[SIZE_ROW][SIZE_COLUMN] = { false, };
public:
	MoviePlay();
	MovieInfo* info;                   //영화 정보
	MoviePlay* nextPlay;               //현재 관 다음 상영 영화
	MoviePlay(short sTime, MovieInfo* mInfo, MoviePlay* nextP);          //생성자
	void changeSeat(short x, short y, bool status); //좌석 입력 받아서 예매
	bool checkSeat(short x, short y); //해당 좌석이 예매 가능한지
	~MoviePlay();
	void printSeat();
	unsigned short restSeat();
	unsigned short startTime;           //시작 시간
	unsigned short endTime;             //종료 시간
};


class MovieRoom {
private:
	char roomNumber;
	bool status;
	MoviePlay* head = new MoviePlay;

public:
	list<MoviePlay> movielist;
	unsigned short movieCount;
	MovieRoom();
	MovieRoom(char roomNumber);
	~MovieRoom();
	void deleteMovieInfo(MovieInfo* info);  //영화 정보 삭제하면서 해당 관 내 상영영화 모두 삭제
	void setStatus(bool status);
	MoviePlay* canAddMovie(MovieInfo* info, short select); //영화관에 영화 추가 가능한지
	void addMovieToRoom(MovieInfo* info, short select); // 영화관에 영화 추가
	void addMovieToRoom(MoviePlay& movie); // 영화관에 영화 추가
	void printTimeTable(); //영화관의 영화 타임 테이블 출력s
};

/* 예매 정보 객체 */
class Ticket
{
private:
	short number;
	short* seatNumber; //좌석 번호
	MoviePlay* playInfo;               //상영 영화 정보
public:
	int ticketNumber;
	Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket);
	~Ticket();
	Ticket* nextTicket;
	void printTicket();            //예매 관련 정보 출력
};


/* 관리자 객체 */
class Admin
{
private:
	short maxIndex = 0;
	MovieInfo* infoTable[MOVIE_INFO_ARR_SIZE];
	MovieRoom* roomTable[MOVIE_ROOM_ARR_SIZE];
	Ticket* ticketHead;
	Ticket* ticketTail;
public:
	Admin();
	~Admin();

	/* 화면 출력 관련 함수 */
	void printInfoTable(void);               //영화 리스트 출력 화면 (for문)
	void printTimetable(short index);  //영화관 선택 시 시작시간 순으로 상영영화 출력(상영 영화 추가 제거 화면)

	/* 영화 정보 관련 함수 (추가, 삭제) */
	void createMovieInfo();   //영화 정보 만들기
	void deleteMovieInfo(short index);   //영화 정보 삭제하면서 해당 상영영화 모두 삭제

	/* 영화관 관련 함수 (영화관&좌석 상태 관리, 상영 영화 추가, 삭제) */
	void setMovieRoomStatus(MovieRoom& room, bool status);            //영화관 사용 가능, 불가능
	void addMovie(MovieInfo* info, MovieRoom& room, short selectTime);       //영화관 내 상영영화 Linked List에 시간 검사 후 생성하기 (movie room의 canaddmovie + addmovie 호출)
	void deleteMoviePlay(short index, short selectTime);  //시작시간 정보로 해당 영화관 내 상영영화 삭제하기

	/* 유저 관련 함수 */
	Ticket* findTicket(int tNumber);     //유저 테이블에서 티켓번호로 User* 찾기
	void printTicket(int tNumber);                        //예매 번호로 티켓 정보 출력 (예매확인 창)
	void deleteTicket(int tNumber);    //예매 번호로 티켓 삭제 (예매취소)
	void addTicket(MoviePlay* movie); //예매

	void gotoxy(short x, short y);
};
