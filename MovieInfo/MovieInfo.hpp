//
//  Movie.h
//  CinemaKiosk
//
//  Created by minjyo on 08/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <memory.h>

using namespace std;

const int seatCol = 5;
const int seatRow = 5;

struct Info{
    string title;
    string pd;
    short runningTime;
    int price;
};

class MovieInfo{
    public:
        MovieInfo(string title, string pd, short runningTime, int price);
        Info getInfo();
    
    private:
        string title;
        string pd;
        short runningTime;
        int price;
    
};


