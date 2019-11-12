//
//  System.h
//  CinemaKiosk
//
//  Created by minjyo on 12/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include <stdio.h>
#include <iostream>

using namespace std;

/* 유저 객체 */
class User
{
private:
    /* 영화 좌석 정보 저장할 구조체 */
    struct seatNumber{
        short x, y;
    };
    
    short number_of_head;               //인원 수
    int ticketNumber;                   //예매 번호
    seatNumber sn[MAX_HEAD];            //구조체 배열 (나중에 malloc으로 바꾸기)
    Movie_Play* playInfo;               //상영 영화 정보
    
public:
    User();
    ~User();
    
    User* Ticketing(void);                  //예매 기능
    void print_Ticket(void);                //예매 관련 정보 출력
};


/* 관리자 객체 */
class Admin
{
private:
    Movie_Info* infoTable[MOVIE_INFO_ARR_SIZE];
    Movie_Room* roomTable[MOVIE_ROOM_ARR_SIZE];
    User* userTable;            //동적할당으로 추가
public:
    Admin();
    ~Admin();
    
    /* 화면 출력 관련 함수 */
    void print_infoTable(void);                                       //영화 리스트 출력 화면 (for문)
    void print_sTime_in_Room(Movie_Room* room);                       //영화관 선택 시 시작시간 순으로 상영영화 출력(상영 영화 추가 제거 화면)
    
    /* 영화 정보 관련 함수 (추가, 삭제) */
    void create_Movie_Info(string movie_name, string pd, short rTime, int price);             //영화 정보 만들기
    void delete_Movie_Info(Movie_Info* info);                                                 //영화 정보 삭제하면서 해당 상영영화 모두 삭제
    
    /* 영화관 관련 함수 (영화관&좌석 상태 관리, 상영 영화 추가, 삭제) */
    void set_Movie_Room_status(Movie_Room& room, bool stat);                                //영화관 사용 가능, 불가능
    void set_Movie_Room_seat_status(Movie_Room* room, short x, short y, bool stat);         //영화관 내 좌석 사용 가능, 불가능
    void add_Movie_Play(Movie_Info& info, Movie_Room& room, short sTime);               //영화관 내 상영영화 Linked List에 시간 검사 후 생성하기
    void delete_Movie_Play(Movie_Room* room, short sTime);                              //시작시간 정보로 해당 영화관 내 상영영화 삭제하기
    
    /* 유저 관련 함수 */
    User* find_Ticket(User* userTable, int tNumber);            //유저 테이블에서 티켓번호로 User* 찾기
    void print_User_Ticket(int tNumber);                        //예매 번호로 티켓 정보 출력 (예매확인 창)
    void delete_User_Ticket(int tNumber);                       //예매 번호로 티켓 삭제 (예매취소)
    
};
