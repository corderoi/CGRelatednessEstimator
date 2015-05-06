//
//  Base.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Base.h"
#include "exceptions.h"
#include "utilities.h"

using namespace std;

Base::Base()
{
    this->iD = static_cast<ID>(utilities::randInt(3));
}

Base::Base(Base::ID iD)
{
    this->iD = iD;
}

Base::ID Base::getID() const
{
    return iD;
}

Base::ID Base::fromChar(char baseCharacter)
{
    switch (baseCharacter)
    {
        case 'A':
            return A;
        case 'G':
            return G;
        case 'T':
            return T;
        case 'C':
            return C;
        case 'N':
            return N;
        default:
            throw RuntimeException("Cannot convert given character to a base");
    }
}

char Base::toChar(Base::ID baseID)
{
    switch (baseID)
    {
        case A:
            return 'A';
        case G:
            return 'G';
        case T:
            return 'T';
        case C:
            return 'C';
        case N:
            return 'N';
        default:
            throw RuntimeException("Impossible to reach here.");
    }
}