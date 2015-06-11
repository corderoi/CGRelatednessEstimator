//
//  Time.h
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____Time__
#define ____Time__

#include <chrono>

#define chrono std::chrono

//
// Documents a time in microseconds.
//
class Time
{
public:
    static const chrono::time_point<chrono::system_clock> START_TIME;
    
    Time();
    
    //
    // Returns microseconds elapsed since the object was created.
    //
    double since() const;
    
    //
    // Returns milliseconds since object creation.
    //
    double millisecondsSince() const;
    
    //
    // Returns seconds since object creation.
    //
    double secondsSince() const;
    
    //
    // Returns microseconds elapsed since program start.
    //
    static double sinceStart();
    
private:
    const chrono::time_point<chrono::system_clock> val;
};

#undef chrono

#endif /* defined(____Time__) */
