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

void MovieRoom::printTimeTable() {

	MoviePlay* temp = head;
	for (int i = 0; i <= movieCount; i++) {
		temp = temp->nextNode;
	}

}