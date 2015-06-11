//
//  Time.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Time.h"

using namespace std;

const chrono::time_point<chrono::system_clock> Time::START_TIME = chrono::system_clock::now();

Time::Time()
: val(chrono::system_clock::now())
{}

double Time::since() const
{
    return (chrono::system_clock::now() - val).count();
}

double Time::millisecondsSince() const
{
    return since() / 1000.0;
}

double Time::secondsSince() const
{
    return millisecondsSince() / 1000.0;
}

double Time::sinceStart()
{
    return (chrono::system_clock::now() - START_TIME).count();
}