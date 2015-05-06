//
//  Sequence.h
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __CGRE__Sequence__
#define __CGRE__Sequence__

#include "Base.h"

//
// Sequence
// Representation of a DNA sequence. Uses efficient bit-level encoding of bases.
//
class Sequence
{
public:
    Sequence(int numBases);
    
    ~Sequence();
    
    void setBase(Base::ID baseID, int position);
    
    Base::ID getBase(int position) const;
    
    void printBases() const;
    
private:
    int* baseStorage; // size is ceil(toDouble(numBases) / 16.0) ints
    int numBases;
};

#endif /* defined(__CGRE__Sequence__) */
