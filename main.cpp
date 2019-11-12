
//
//  main.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Header.hpp"
#include <iostream>

using namespace std;

int main()
{
   // MoviePlay test;
//    test.chooseSeat();
//    test.add(10);
//    test.add(20);
//    test.add(30);
//    test.add(3, 40);
//    test.remove(0);
//    test.set(0, 100);

//    for (int i = 0; i < test.size(); i++)
//    {
//        cout << "data : " << test.get(i) << endl;
//    }
//    cout << "size : " << test.size() << endl;
//    cout << "isEmpty : " << test.isEmpty() << endl;
//
//    test.remove(10);
    
    MovieInfo movie("조커", "Jocker", 1350, 1000);
    
    Info info = movie.getInfo();
    cout << "제목: " << info.title << endl;
    cout << "감독: " << info.pd << endl;
    cout << "러닝타임: " << info.runningTime/100 <<"시간 " << info.runningTime%100 << "분"  << endl;
    cout << "가격: " << info.price << endl;
    

	return 0;
}

