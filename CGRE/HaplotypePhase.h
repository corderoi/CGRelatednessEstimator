//
//  HaplotypePhase.h
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef ____HaplotypePhase__
#define ____HaplotypePhase__

class HaplotypePhase
{
public:
    static constexpr double crossOverRate = 1.0 / 1000.0;
    
    //
    // Generates an uninitialized haplotype of length 'length' haplotypes
    //
    HaplotypePhase(int length);
    
    //
    // Create a new haplotype sequence from two existing ones.
    //
    static HaplotypePhase* createFrom(const HaplotypePhase& h1, const HaplotypePhase& h2);
    
    ~HaplotypePhase();
    
    int getLength() const;
    
    int getH1At(int position) const;
    
    void setH1At(int position, int value);
    
    int getH2At(int position) const;
    
    void setH2At(int position, int value);
    
    void print() const;
    
private:
    int* haplotypes1;
    int* haplotypes2;
    const int length;
};

#endif /* defined(____HaplotypePhase__) */
