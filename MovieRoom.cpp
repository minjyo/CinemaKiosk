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

//?νκ΄???ν ????μ΄λΈ?μΆλ ₯
void MovieRoom::printTimeTable(){
    MoviePlay* temp = head;
    
    cout << "------------------- " << roomNumber << "κ΄ -------------------" << endl;
    cout << "       ?ν ?λͺ©       ?ν κ°λ       ?¬λ???       " << endl;
    cout.fill(' ');
    cout.width(10);
    
    while(temp->nextPlay!=NULL){
        temp->info->printInfo();
        temp = temp->nextPlay;
    }
}
