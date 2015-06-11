//
//  RelatednessTable.h
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____RelatednessTable__
#define ____RelatednessTable__

#include "Table.h"

class UnrelatednessTable;

class RelatednessTable: public Table
{
public:
    RelatednessTable(const UnrelatednessTable& ut);
};

#endif /* defined(____RelatednessTable__) */
