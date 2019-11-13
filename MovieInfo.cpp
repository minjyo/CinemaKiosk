//  Movie.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Header.hpp"

MovieInfo::MovieInfo(string title, string pd, short runningTime, int price){
    this->title = title;
    this->pd = pd;
    this->runningTime = runningTime;
    this->price = price;
    cout<<"movie 객체 생성"<<endl;
}

Info MovieInfo::getInfo(){
        Info cur;
        
        cur.title = this->title;
        cur.pd = this->pd;
        cur.runningTime = this->runningTime;
        cur.price = this->price;
        
        return cur;
}

void MovieInfo::printInfo(){
    cout << "       영화 제목       영화 감독       러닝타임        " << endl;
    
    cout.fill(' ');
    cout.width(10);
    
    cout << title;
    cout << pd;
    cout << runningTime;
}
