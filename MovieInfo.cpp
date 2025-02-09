﻿//  Movie.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Header.hpp"

MovieInfo::MovieInfo(string title, string pd, unsigned short runningTime, int price) {
	this->title = title;
	this->pd = pd;
	this->runningTime = runningTime;
	this->price = price;
	this->count = 0;
}

void MovieInfo::printInfo() {
	cout.setf(ios::left);
	cout << setw(20) << title;
	cout << setw(20) << to_string(price) + "원";
	cout << setw(20) << pd;
	cout << runningTime / 100 << "시간 " << runningTime % 100 << "분" << endl;
}