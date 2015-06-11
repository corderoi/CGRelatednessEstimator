//
//  HaplotypeSet.h
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____HaplotypeSet__
#define ____HaplotypeSet__

#include <vector>
#include <string>

#define string std::string
#define vector std::vector

class Individual;
class HaplotypePhase;

//
// Represents the haplotypes of multiple individuals. Also keeps track of the SNP
// rsIDs and position numbers.
//
class HaplotypeSet
{
public:
    //
    // Reads from 'filename' a specifically-formatted set of haplotype data and
    // stores a vector of individuals with their respective SNPs.
    //
    HaplotypeSet(string filename, int snpCap = -1, int individCap = -1);
    
    void print() const;
    
    ~HaplotypeSet();
    
    void reportBasicInfo() const;
    
    double getAlleleFreq(int whichSNP) const;
    
    double getMinorAlleleFreq(int whichSNP) const;
    
    bool isMinorAllele(int whichSNP) const;
    
    int getAlleleSNPValue(int whichAllele, int whichSNP) const;
    
    int getNumSNPs() const;
    
    int getNumIndividuals() const;
    
    int getNumAlleles() const;
    
    Individual* getIndividual(int whichIndividual) const;
    
    int getNumMinorAllelesAt(int position, const HaplotypePhase& haplotypes) const;
    
private:
    string setPosition;
    vector<string> rsIDs;
    vector<string> positionNums;
    vector<Individual*> individuals;
    vector<bool> minorAlleles;
};

#undef string
#undef vector

#endif /* defined(____HaplotypeSet__) */
