//
//  Individual.h
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____Individual__
#define ____Individual__

#include <string>

#define string std::string

class HaplotypePhase;

//
// Represents an individual identified by ID and haplotypes.
//
struct Individual
{
public:
    Individual(string iD, int numSNPs);
    
    ~Individual();
    
    void print() const;
    
    string iD;
    HaplotypePhase* haplotypePhase;
};

#undef string

#endif /* defined(____Individual__) */
