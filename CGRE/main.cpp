//
//  main.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <iostream>
#include "utilities.h"
#include "Sequence.h"
#include "stats.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Handle CL arguments
    if (argc != 1) {
        utilities::error("No command-line arguments are permitted at this time.");
    }
    
    // Test random data
    Sequence testSequence(1000);
    testSequence.printBases();
    
    // Test stats library
}