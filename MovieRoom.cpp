#include "Header.hpp"

MovieRoom::MovieRoom(char roomNumber) {
    head = NULL;
    this->roomNumber = roomNumber;
    this->status = false;
    this->movieCount = 0;
}

void MovieRoom::setStatus(bool status) {
    this->status = status;
}

MovieRoom::~MovieRoom() {
    
}

//영화관의 영화 타임 테이블 출력
void MovieRoom::printTimeTable(){
    MoviePlay* temp = head;
    
    cout << "------------------- " << roomNumber << "관 -------------------" << endl;
    cout << "       영화 제목       영화 감독       러닝타임        " << endl;
    cout.fill(' ');
    cout.width(10);
    
    while(temp->nextPlay!=NULL){
        temp->info->printInfo();
        temp = temp->nextPlay;
    }
}

