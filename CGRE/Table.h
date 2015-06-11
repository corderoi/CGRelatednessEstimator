//
//  Table.h
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____Table__
#define ____Table__

#include <array>

#define array std::array

class Table
{
public:
    Table(const array<double, 9> values);
    
    array<double, 3> operator[](int row) const;
    
private:
    const array<double, 9> values;
};

#undef array

#endif /* defined(____Table__) */
