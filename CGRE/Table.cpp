//
//  Table.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "Table.h"

using namespace std;

Table::Table(const array<double, 9> values)
: values(values)
{}

array<double, 3> Table::operator[](int row) const
{
    return { values.at(row * 3), values.at(row * 3 + 1), values.at(row * 3 + 2) };
}