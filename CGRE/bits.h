//
//  bits.h
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____bits__
#define ____bits__

//
// Bit manipulation
//

#define setBit(integer, pos, value)\
integer &= ~(0b1 << pos);\
integer |= value << pos

#define getBit(integer, pos)\
(integer >> pos) & 0b1

#endif /* defined(____bits__) */
