#include "header.hpp"

void MovieRoom::deleteMovieInfo(MovieInfo* deleteInfo){
    MoviePlay* temp = head;
    MoviePlay* tempNext;

    while(temp->nextPlay != 0x00){
        tempNext = temp->nextPlay;

        if(tempNext->info == deleteInfo){
            temp->nextPlay = temp->nextPlay->nextPlay;
            tempNext->~MoviePlay();
        }

        temp = temp->nextPlay;
    }
}