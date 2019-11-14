#include "header.hpp"

void Admin::deleteMovieInfo(short index)
{
    short i;

    //모든 영화관에서 영화정보로 영화 삭제
    for (i = 0; i < MOVIE_ROOM_ARR_SIZE; i++)
    {
        roomTable[i]->deleteMovieInfo(infoTable[index]);
    }

    //배열에서 줄여주기
    for (i = index; i < maxIndex; i++)
    {
        infoTable[i] = infoTable[i + 1];
    }
    infoTable[maxIndex] = 0x00;
    maxIndex--;
}

void Admin::addTicket(MoviePlay *movie)
{
    short numberOfHead;                 //인원 수
    short x, y;                         //좌표 변수
    short restSeat = movie->restSeat(); //잔여 좌석
    short i, temp;                      //반복문
    short count;                    //몇명 예매했는지
    bool check;
    int key; //입력된 키보드 값

    system("cls");
    movie->printSeat();

    //인원수 입력받기, 예외처리 : 음수거나 잔여좌석보다 크게 입력받을 때
    do
    {
        gotoxy(0, SIZE_ROW);
        cout << "인원 수를 입력하세요 : ";
        gotoxy(0, SIZE_ROW + 1);
        cin >> numberOfHead;
        check = (numberOfHead <= 0) || (numberOfHead > restSeat);
        if (check)
        {
            gotoxy(0, SIZE_ROW + 2);
            cout << "잔여 좌석보다 많습니다." << endl;
        }
    } while (check);

    //입력받은 인원수만큼 short 배열 만들기 & -1로 초기화
    short *seatArr = new short[numberOfHead];
    for (i = 0; i < numberOfHead; i++)
    {
        seatArr[i] = -1;
    }

    system("cls");
    movie->printSeat();
    gotoxy(0, SIZE_ROW);
    cout << "원하는 좌석을 선택하세요." << endl;
    cout << "  명 남았습니다." << endl;

    while (count != 0)
    {

        while (_kbhit())
        {
            key = _getch();
            /* 방향키 눌렸을 때 */
            if (key == 224 || key == 0)
            {
                key = _getch();
                switch (key)
                {
                case 72:
                    if (y > 0)
                    {
                        y--;
                    }
                    break;
                case 75:
                    if (x > 0)
                    {
                        x--;
                    }
                    break;
                case 77:
                    if (x < SIZE_COLUMN - 1)
                    {
                        x++;
                    }
                    break;
                case 80:
                    if (y < SIZE_ROW - 1)
                    {
                        y++;
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                /* 엔터가 눌렸을 때 */
                if (key == 13)
                {
                    check = false;
                    temp = x * 10 + y;

                    for (i = 0; i < numberOfHead; i++)
                    {
                        if (seatArr[i] == temp)
                        {
                            seatArr[i] = -1;
                            check = true;
                        }
                    }
                    /* 이미 배열 내에 temp와 같은 값이 저장되어 있으면(기존 좌석 취소)  */
                    if (check)
                    {
                        cout << "□";
                        count++;
                        gotoxy(0, SIZE_ROW + 1);
                        printf("%2d", count);
                    }
                    /* 배열 내에 temp와 같은 값이 저장되어 있지 않으면(신규 좌석 예매)  */
                    else
                    {
                        /* 이미 예매된 좌석이면 (checkSeat가 true면 이미 예매된 좌석으로 일단 구현) */
                        if (movie->checkSeat(x, y))
                        {
                            gotoxy(0, SIZE_ROW + 2);
                            cout << "이미 예매된 좌석입니다.";
                        }
                        /* 예매된 좌석이 아니면 신규 예매 */
                        else
                        {
                            i = 0;
                            while (seatArr[i] != -1)
                            {
                                i++;
                            }
                            seatArr[i] = temp;
                            cout << "■";
                            count--;
                            gotoxy(0, SIZE_ROW + 1);
                            printf("%2d", count);
                        }
                    }
                }
                /* 후에 뒤로가기 키 구현 */
            }
        }

        gotoxy(2 * x, y);
    }

    /* 예매가 완료되면 tail다음에 티켓 추가해주기 */
    if (ticketHead == 0x00)                 //첫 티켓일 경우 tail과 head에 추가
    {
        Ticket newTicket(numberOfHead, 100001, seatArr, movie, 0x00);
        ticketHead = &newTicket;
        ticketTail = &newTicket;
    }
    else
    {
        Ticket newTicket(numberOfHead, ticketTail->ticketNumber + 1, seatArr, movie, 0x00);
        ticketTail->nextTicket = &newTicket;
        ticketTail = &newTicket;
    }
}

void gotoxy(short x, short y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}