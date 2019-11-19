#include "header.hpp"

Ticket::Ticket(short n, int tNumber, short* sNumber, MoviePlay* pInfo, Ticket* nTicket) {
	number = n;
	ticketNumber = tNumber;
	seatNumber = sNumber;
	playInfo = pInfo;
	nextTicket = nTicket;
}

Ticket::~Ticket() {

}

void Ticket::printTicket() {

}