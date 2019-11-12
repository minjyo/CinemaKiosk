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

//?�화관???�화 ?�???�이�?출력
void MovieRoom::printTimeTable(){
    MoviePlay* temp = head;
    
    cout << "------------------- " << roomNumber << "관 -------------------" << endl;
    cout << "       ?�화 ?�목       ?�화 감독       ?�닝?�??       " << endl;
    cout.fill(' ');
    cout.width(10);
    
    while(temp->nextPlay!=NULL){
        temp->info->printInfo();
        temp = temp->nextPlay;
    }
}
