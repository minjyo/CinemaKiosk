//
//  main.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright Â© 2019 minjyo. All rights reserved.
//

#include "Header.hpp"
#include <iostream>
#include <list>

using namespace std;

int main()
{
    char mode = USER;
    char *input;

    while (input[0] != 'Q')
    {
        //관리자, 사용자 권한 변경
        if (input[0] == 'M')
        {
            mode = ADMIN;
            continue;
        }
        if (input[0] == 'H')
        {
            mode = USER;
            continue;
        }

        switch (mode)
        {
        case USER: //사용자 홈
            break;
        case CHOOSEMOVIE: //영화 선택
            //전체 영화 리스트 출력

            //선택한 영화의 상영 리스트 (영화관별 시간, 잔여 좌석)

            //선택한 영화의 좌석 상태 출력

            //좌석 선택

            //예매 결과 출력

            //티켓에 예매 정보 추가
            break;
        case TICKET: //티켓 정보 확인
            //티켓 번호 입력

            //티켓 정보 출력
            break;

        case ADMIN: //관리자 홈
            break;
        case MANMOVIE: // 영화 관리
            //전체 영화 리스트 출력
            break;
        case MAKEMOVIE: //새로운 영화 만들어서 추가
            break;
        case DELETEALL: //영화 삭제 (모든 영화관에서 삭제)
            break;
        case MANROOM: //영화관 관리
            //영화관 선택
            break;
        case ROOMSTATUS: //영화관 상태 변경
            break;
        case ADDMOVIE: //영화관에 영화 추가
            //영화관의 상영 영화 리스트 출력
            //전체 영화 리스트 출력
            //영화 선택 후, 영화관에 추가 가능한지 검사
            //영화관
            break;
        case DELETEMOVIE: //영화관에 영화 삭제
            //영화관의 상영 영화 리스트 출력
            //영화 선택 후, 삭제
            //영화관의 상영 영화 리스트 출력
            break;
        default:
            break;
        }
    }
    return 0;
}
