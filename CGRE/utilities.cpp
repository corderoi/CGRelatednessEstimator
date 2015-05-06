//
//  utilities.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "utilities.h"
#include <algorithm> // swap()
#include <random>

using namespace std;

int utilities::randInt(int lowest, int highest)
{
    static random_device generator;
    uniform_int_distribution<int> distribution(lowest, highest);
    return distribution(generator);
}

int utilities::randInt(int range)
{
    return randInt(0, range-1);
}