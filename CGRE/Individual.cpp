//
//  Individual.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Individual.h"
#include "HaplotypePhase.h"
#include "utilities.h"

using namespace std;

Individual::Individual(string iD, int numSNPs)
: iD(iD), haplotypePhase(new HaplotypePhase(numSNPs))
{}

Individual::~Individual()
{
    delete haplotypePhase;
}

void Individual::print() const
{
    utilities::println(iD + ":");
    haplotypePhase->print();
}