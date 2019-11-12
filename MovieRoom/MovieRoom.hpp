//
//  MovieRoom.h
//  CinemaKiosk
//
//  Created by minjyo on 12/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

class MovieRoom{

private:
    char room_number;
    bool status;
    bool seat[SEAT_SIZE_ROW][SEAT_SIZE_COLUMN];     // True : 사용 불가능한 좌석
    Movie_Play* head;
public:
    Movie_Room();
    ~Movie_Room();
    void deleteMovieInfo(MovieInfo* info);  //영화 정보 삭제하면서 해당 관 내 상영영화 모두 삭제
    void setMovieRoomStatus(MovieRoom* room, bool status); //영화관 사용 가능, 불가능
    void setMovieRoomSeatstatus(Movie_Room* room, short x, short y, bool status); //영화관 내 좌석 사용 가능, 불가능
    void addMoviePlay(MovieInfo* info, MovieRoom* room, short sTime);//영화관 내 상영영화 Linked List에 시간 검사 후 생성하기
    void printTimeTable(Movie_Room* room); //해당 영화관의 영화 타임 테이블

};



