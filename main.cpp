//
//  main.cpp
//  CinemaKiosk
//
//  Created by minjyo on 04/11/2019.
//  Copyright © 2019 minjyo. All rights reserved.
//

#include "Movie.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Movie movie("조커", "Jocker", 1350, 1000);
    
    Info info = movie.getInfo();
    cout << "제목: " << info.title << endl;
    
    return 0;
}
