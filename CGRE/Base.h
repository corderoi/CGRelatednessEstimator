//
//  Base.h
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __CGRE__Base__
#define __CGRE__Base__

//
// Base
// Representation for a single base in a DNA sequence. If unknown bases (N) are not
// taken into account, there are 4 possibilities and bases can be encoded using
// 2 bits.
//
struct Base
{
public:
    enum ID
    {
        A = 0b00,
        G = 0b01,
        T = 0b10,
        C = 0b11,
        N = 0b100 // will not be used, in general
    };
    
    Base();
    
    Base(ID iD);
    
    ID getID() const;
    
    static ID fromChar(char baseCharacter);
    
    static char toChar(ID baseID);
    
private:
    ID iD;
};

#endif /* defined(__CGRE__Base__) */
