//
//  Movie.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Movie.h"

Movie::Movie(string title, string pd, short runningTime, int price){
    this->title = title;
    this->pd = pd;
    this->runningTime = runningTime;
    this->price = price;
}

Info Movie::getInfo(){
        Info cur;
        
        cur.title = this->title;
        cur.pd = this->pd;
        cur.runningTime = this->runningTime;
        cur.price = this->price;
        
        return cur;
}

