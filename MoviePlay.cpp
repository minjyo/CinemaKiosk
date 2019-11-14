#include "header.hpp"

void MoviePlay::printSeat(){
    short i, j;
    for(i=0 ; i < SIZE_ROW ; i++){
        for(j=0 ; j < SIZE_COLUMN ; j++){
                if(seat[i][j] == false){
                    cout << "□" ;
                }
                else{
                    cout << "▩" ;
                }
        }
        cout << endl;
    }
}