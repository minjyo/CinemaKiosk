//
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

/* 영화정보 객체 */
class MovieInfo {
public:
	string title;
	string pd;
	unsigned short runningTime;
	int price;
	int count;

	void printInfo(); //영화정보 출력 함수
	MovieInfo(string title, string pd, unsigned short runningTime, int price); // 생성자
};

/* 상영영화 객체 (Linked list) */
class MoviePlay {
private:
	bool seat[SIZE_ROW][SIZE_COLUMN] = { false, };
public:
	unsigned short startTime;			//시작 시간
	unsigned short endTime;				//종료 시간
	MovieInfo* info;					//영화 정보
	MoviePlay* nextPlay;				//현재 관 다음 상영 영화

	/* 생성자, 소멸자 */
	MoviePlay(short sTime, MovieInfo* mInfo, MoviePlay* nextP);
	MoviePlay();
	~MoviePlay();

	/* 클래스 함수 */
	void printSeat();								// 8 * 8 좌석 출력좌석 현황 출력.예매 가능하면 ▩, 안되면 ■
	unsigned short restSeat();						// 잔여좌석 개수 리턴
	void changeSeat(short x, short y, bool status); // 좌석 입력 받아서 예매
	bool checkSeat(short x, short y);				// 해당 좌석이 예매 가능한지
};

/* 상영관 객체 */
class MovieRoom {
private:
	unsigned short roomNumber;
public:
	MoviePlay* head = new MoviePlay;
	unsigned short movieCount;

	MovieRoom(unsigned short roomNumber);
	~MovieRoom();

	/* 출력 함수 */
	void printTimeTable();					// 영화관의 영화 타임 테이블 출력
	int printMovieInfo(MovieInfo* info);	// 해당 관 안에서 특정 영화만 출력

	unsigned short getEndTime(unsigned short startTime, unsigned short runningTime); // 시작시간, 러닝타임으로 종료시간 리턴

	/* 영화관에 영화 추가, 제거 */
	int canAddMovie(MovieInfo* info, unsigned short select);		// 영화관에 영화 추가 가능하면 추가할 곳의 앞 영화 인덱스, 불가능하면 -1 리턴
	bool addMovieToRoom(MovieInfo* info, unsigned short select);	// canAddMovie 값을 받아서 영화관에 영화 추가
	void deleteMovieInfo(MovieInfo* info);							// 해당 관 안에서 상영중인 영화중 일치하는 영화 모두 삭제
	int deleteMoviePlay(short starttime);							// 해당 관 안에서 상영중인 특정영화 하나 삭제

	MoviePlay* findMoviePlay(MovieInfo * minfo, int index);			// 영화관에서 몇번째 상영중인 특정 영화 객체 리턴 
};

/* 예매 정보 객체 */
class Ticket
{
public:
	short number;						//인원 수
	short* seatNumber;					//좌석 번호
	MoviePlay* playInfo;				//상영 영화 정보
	int ticketNumber;					//예매번호
	Ticket* nextTicket;					//다음 티켓 주소

	void printTicket();					//예매한 티켓 정보 출력

	/*티켓 생성자, 소멸자*/
	Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket);
	~Ticket();
};

/* 관리자 객체 */
class Admin
{
private:
public:
	Admin();
	~Admin();
	short infoCount = 0;
	short roomCount = 0;
	unsigned int total = 0;

	/* 영화관 정보, 영화 정보 가지고 있는 배열 */
	MovieInfo* infoTable[MOVIE_INFO_ARR_SIZE];
	MovieRoom* roomTable[MOVIE_ROOM_ARR_SIZE];

	Ticket* ticketHead;
	Ticket* ticketTail;
	void showStatistic();				//총액 출력

	/* 화면 출력 관련 함수 */
	void printInfoTable(void);			//영화 리스트 출력 화면 (for문)
	void printTimetable(short index);	//영화관 선택 시 시작시간 순으로 상영영화 출력(상영 영화 추가 제거 화면)
	void printAllMovies(string name);	//해당 영화를 선택했을 때 그 영화의 모든 관에서의 상영 정보 출력
	int printMoviefromRoom(unsigned short roomNumber, MovieInfo* minfo);

	/* 영화 정보 관련 함수 (추가, 삭제) */
	bool createMovieInfo();				//영화 정보 만들기
	void deleteMovieInfo(short index);	//영화 정보 삭제하면서 해당 상영영화 모두 삭제

	/* 영화관 관련 함수 (영화관&좌석 상태 관리, 상영 영화 추가, 삭제) */
	bool addMovie(MovieInfo* info, MovieRoom* room, short selectTime);		//영화관 내 상영영화 Linked List에 시간 검사 후 생성하기 (movie room의 canaddmovie + addmovie 호출)
	void deleteMoviePlay(unsigned short roomNumber, short startTime);		//시작시간 정보로 해당 영화관 내 상영영화 삭제하기
	MoviePlay* findMoviePlayfromRoom(unsigned short roomNumber, MovieInfo* minfo, int index);
	int deleteMoviePlayfromRoom(unsigned short roomNumber, unsigned short startTime);

	/* 유저 관련 함수 */
	Ticket* findTicket(int tNumber);		//유저 테이블에서 티켓번호로 User* 찾기
	void printTicket(int tNumber);			//예매 번호로 티켓 정보 출력 (예매확인 창)
	void deleteTicket(Ticket* select);		//예매 번호로 티켓 삭제 (예매취소)

	void gotoxy(short x, short y);
};

class UI {
public:
	int key;
	int x, y;
	/* 사용자 홈 화면 */
	int userHome(void);

	/* 영화 선택 */
	int chooseMovie(Admin admin, int* index);													//영화 예매 선택 시 영화 리스트 출력하는 화면
	int chooseRoom(Admin admin, int* room_index, int movie_index, MovieInfo** movie);			//영화 선택 시 상영하는 영화 리스트 출력하는 화면
	int chooseTime(Admin admin, int room_index, int* yy, MovieInfo* movie, MoviePlay** play);		// 상영하는 영화 리스트에서 특정 영화 선택
	int chooseSeat(Admin admin, MoviePlay* play, Ticket** newTicket);	// 좌석 선택

	/* 티켓 생성, 확인 */
	int checkTicket(Admin* admin, int movie_index);						//영화 예매 후 티켓 정보 확인(check == false) & 예매 정보 확인(check == true)
	int checkInfo(Ticket* newTicket);					//예매정보 확인
	int checkMoney(Admin* admin, Ticket* newTicket, MovieInfo* movie);	// 결제

	/* 관리자 홈 화면 */
	int adminHome(void);

	/* 영화 관리 함수 */
	int manMovie(void);						//영화 관리 화면
	int makeMovie(Admin* admin);			//영화관리 - 영화 추가
	int deleteAll(Admin* admin);			//영화관리 - 영화 삭제

	/* 영화관 관리 함수 */
	int manRoom(int* room_index);						//영화관 관리 메인 화면
	int addMovie(Admin* admin, int room_index);			//영화관 관리 - 상영 영화 추가
	int deleteMovie(Admin* admin, int room_index);		//영화관 관리 - 상영 영화 삭제
	int showStatistics(Admin* admin);

	void gotoxy(short x, short y);
	void printBorder(void);
};