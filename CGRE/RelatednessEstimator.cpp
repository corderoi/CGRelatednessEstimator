//
//  RelatednessEstimator.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/11/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "RelatednessEstimator.h"
#include "HaplotypePhase.h"
#include "HaplotypeSet.h"
#include "utilities.h"
#include "RelatednessTable.h"
#include "UnrelatednessTable.h"

double RelatednessEstimator::estimateBaseline(const HaplotypePhase& h1, const HaplotypePhase& h2)
{
    int numMatches = 0;
    const int length = h1.getLength();
    
    for (int i = 0; i < length; i++) {
        if (h1.getH1At(i) == h2.getH1At(i) && h1.getH2At(i) == h2.getH2At(i)) {
            numMatches++;
        }
    }
    return utilities::toDouble(numMatches) / utilities::toDouble(length);
}

double RelatednessEstimator::estimate(const HaplotypePhase& h1, const HaplotypePhase& h2, const HaplotypeSet& set)
{
    const int length = h1.getLength();
    int numRelated = 0;
    int longestSubstring = 0;
    int currentSubstring = 0;
    
    for (int i = 0; i < length; i++) {
        const int numMinorAlleles1 = set.getNumMinorAllelesAt(i, h1);
        const int numMinorAlleles2 = set.getNumMinorAllelesAt(i, h2);
        const double minorAlleleFreq = set.getMinorAlleleFreq(i);
        
        // Substring analysis (sibling/horizontal relation analysis)
        if (numMinorAlleles1 == numMinorAlleles2) {
            currentSubstring++;
        } else {
            currentSubstring = 0;
        }
        if (currentSubstring > longestSubstring) {
            longestSubstring = currentSubstring;
        }
        
        // Likelihood analysis
        UnrelatednessTable uTable(minorAlleleFreq);
        RelatednessTable rTable(uTable);
        
        const double unrelatedProb = uTable[numMinorAlleles1][numMinorAlleles2];
        const double relatedProb = rTable[numMinorAlleles1][numMinorAlleles2];
        
        if (relatedProb >= unrelatedProb) {
            numRelated++;
        }
    }
    
    const double likelihoodScore = utilities::toDouble(numRelated) / utilities::toDouble(length);
    const double substringScore = utilities::min(utilities::toDouble(longestSubstring) * HaplotypePhase::crossOverRate, 1.0);
    
    return likelihoodScore * substringScore;
}