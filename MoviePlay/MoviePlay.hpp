#pragma once
#define SIZE_COLUMN 5
#define SIZE_ROW 5

/* 상영영화 객체 (Linked list) */
class MoviePlay{
    
private:
    bool seat[SIZE_COLUMN][SIZE_ROW];
    unsigned short startTime;           //시작 시간
    unsigned short endTime;             //종료 시간
    MovieInfo* info;                   //영화 정보
    MoviePlay* nextPlay;               //현재 관 다음 상영 영화
    
public:
    Movie_Play(bool seat[SEAT_SIZE_ROW][SEAT_SIZE_COLUMN], short sTime, Movie_Info* mInfo, Movie_Play* nextP);          //생성자
    ~Movie_Play();
};
