//  Movie.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Header.hpp"

MovieInfo::MovieInfo(string title, string pd, short runningTime, int price) {
	this->title = title;
	this->pd = pd;
	this->runningTime = runningTime;
	this->price = price;
	//cout << "movie 객체 생성" << endl;
}

void MovieInfo::printInfo() {
	cout.setf(ios::left);
	cout << setw(20) << title;
	cout << setw(20) << price;
	cout << setw(20) << pd;
	cout << runningTime / 100 << "시간 " << runningTime % 100 << "분" << endl;
}