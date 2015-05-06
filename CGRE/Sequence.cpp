//
//  Sequence.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Sequence.h"
#include <cmath>
#include "utilities.h"
#include "exceptions.h"

Sequence::Sequence(int numBases)
{
    if (numBases < 0) {
        throw LogicException("Cannot create a DNA sequence of negative length.");
    }
    
    this->numBases = numBases;

    // Initialize storage
    const int storageSize = ceil(utilities::toDouble(numBases) / 16.0);
    baseStorage = new int[storageSize];
    
    // Randomize bases
    for (int i = 0; i < numBases; i++) {
        setBase(static_cast<Base::ID>(utilities::randInt(4)), i);
    }
}

Sequence::~Sequence()
{
    delete[] baseStorage;
}

void Sequence::setBase(Base::ID baseID, int position)
{
    const int bucket = position / 16;
    const int baseInBucket = position % 16;
    baseStorage[bucket] = ((baseStorage[bucket] & (~(0b11 << (baseInBucket * 2))) ) | (static_cast<int>(baseID) << (baseInBucket * 2)));
}

Base::ID Sequence::getBase(int position) const
{
    const int bucket = position / 16;
    const int baseInBucket = position % 16;
    return static_cast<Base::ID>((baseStorage[bucket] >> (baseInBucket * 2)) & 0b11);
}

void Sequence::printBases() const
{
    for (int i = 0; i < numBases; i++) {
        utilities::print(Base::toChar(getBase(i)));
    }
}