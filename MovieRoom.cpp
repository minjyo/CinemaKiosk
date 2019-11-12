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

//?í™”ê´€???í™” ?€???Œì´ë¸?ì¶œë ¥
void MovieRoom::printTimeTable(){
    MoviePlay* temp = head;
    
    cout << "------------------- " << roomNumber << "ê´€ -------------------" << endl;
    cout << "       ?í™” ?œëª©       ?í™” ê°ë…       ?¬ë‹?€??       " << endl;
    cout.fill(' ');
    cout.width(10);
    
    while(temp->nextPlay!=NULL){
        temp->info->printInfo();
        temp = temp->nextPlay;
    }
}
