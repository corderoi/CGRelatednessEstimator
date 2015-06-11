//
//  UnrelatednessTable.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "UnrelatednessTable.h"
#include "Table.h"
#include <cmath>

using namespace std;

UnrelatednessTable::UnrelatednessTable(double maf)
: Table({ pow(1.0 - maf, 4.0), 2.0 * pow(1.0 - maf, 3.0) * maf, pow(1.0 - maf, 2.0) * pow(maf, 2.0),
    2.0 * pow(1.0 - maf, 3.0) * maf, 4.0 * pow(1.0 - maf, 2.0) * pow(maf, 2.0), 2.0 * (1.0 - maf) * pow(maf, 3.0),
    pow(1.0 - maf, 2.0) * pow(maf, 2.0), 2.0 * (1.0 - maf) * pow(maf, 3.0), pow(maf, 3.0) })
{}