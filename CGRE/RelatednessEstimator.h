//
//  RelatednessEstimator.h
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____RelatednessEstimator__
#define ____RelatednessEstimator__

class HaplotypePhase;
class HaplotypeSet;

//
// The core of the project. Estimates relatedness between two individuals.
//
class RelatednessEstimator
{
public:
    //
    // Estimates the relatedness between individuals h1 and h2 using the basic method.
    // Returns a coefficient describing the level of relatedness between the two.
    //
    static double estimateBasline(const HaplotypePhase& h1, const HaplotypePhase& h2);
    
    //
    // Estimates the relatedness between individuals h1 and h2 using an advanced method.
    // Returns a coefficient describing the level of relatedness between the two.
    //
    static double estimate(const HaplotypePhase& h1, const HaplotypePhase& h2, const HaplotypeSet& set);
};

#endif /* defined(____RelatednessEstimator__) */
