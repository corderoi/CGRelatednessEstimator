//
//  RelatednessTable.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "RelatednessTable.h"
#include "UnrelatednessTable.h"

RelatednessTable::RelatednessTable(const UnrelatednessTable& ut)
: Table({ ut[0][0] + 0.25 * ut[0][1] + 0.25 * ut[1][0] + 0.0625 * ut[1][1],
    ut[0][1] * 0.25 + ut[1][0] * 0.25 + ut[1][1] * 0.125,
    ut[1][1] * 0.0625,
    ut[0][1] * 0.25 + ut[1][0] * 0.25 + ut[1][1] * 0.125,
    ut[1][1] * 0.25 + ut[1][2] * 0.25 + ut[2][1] * 0.25 + ut[0][1] * 0.25 + ut[1][0] * 0.25 + ut[0][2] + ut[2][0],
    ut[1][2] * 0.25 + ut[2][1] * 0.25 + ut[1][1] * 0.125,
    ut[1][1] * 0.0625,
    ut[1][2] * 0.25 + ut[2][1] * 0.25 + ut[1][1] * 0.125,
    ut[1][1] * 0.0625 + ut[2][2] + ut[1][2] * 0.25 + ut[2][1] * 0.25 })
{}