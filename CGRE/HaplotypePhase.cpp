//
//  HaplotypePhase.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "HaplotypePhase.h"
#include "exceptions.h"
#include "stats.h"
#include "utilities.h"
#include <array>
#include "bits.h"

using namespace std;

#define calcArraySize(numHaplotypes)\
(numHaplotypes - 1) / 32 + 1

HaplotypePhase::HaplotypePhase(int length)
: length(length)
{
    if (length <= 0) {
        throw LogicException("Haplotype length must be a positive value.");
    }
    const int arraySize = calcArraySize(length);
    haplotypes1 = new int[arraySize];
    haplotypes2 = new int[arraySize];
}

HaplotypePhase* HaplotypePhase::createFrom(const HaplotypePhase &h1, const HaplotypePhase &h2)
{
    const int length = h1.length;
    
    if (h1.length != h2.length) {
        throw LogicException("Haplotype lengths must be equal.");
    } else if (length <= 0) {
        throw LogicException("Haplotype length must be a positive value.");
    }
    
    HaplotypePhase* h3 = new HaplotypePhase(length);
    
    array<int, 2> whichHaplotype = { utilities::randInt(0, 1), utilities::randInt(0, 1) };
    
    for (int i = 0; i < length; i++) {
        // Cross over at rate 'crossOverRate'
        if (stats::rand(0.0, 1.0) < crossOverRate) {
            whichHaplotype.at(0) = !whichHaplotype.at(0);
        }
        if (stats::rand(0.0, 1.0) < crossOverRate) {
            whichHaplotype.at(1) = !whichHaplotype.at(1);
        }
        
        // Copy parent alleles
        if (whichHaplotype.at(0) == 0) {
            h3->setH1At(i, h1.getH1At(i));
        } else {
            h3->setH1At(i, h1.getH2At(i));
        }
        if (whichHaplotype.at(1) == 0) {
            h3->setH2At(i, h2.getH1At(i));
        } else {
            h3->setH2At(i, h2.getH2At(i));
        }
    }
    
    return h3;
}

HaplotypePhase::~HaplotypePhase()
{
    delete[] haplotypes1;
    delete[] haplotypes2;
}

int HaplotypePhase::getLength() const
{
    return length;
}

int HaplotypePhase::getH1At(int position) const
{
    if (position >= length || position < 0) {
        throw RuntimeException("Out of bounds access attempt for getH1At()");
    }
    
    return getBit(haplotypes1[position / 32], position % 32);
}

void HaplotypePhase::setH1At(int position, int value)
{
    if (position >= length || position < 0) {
        throw RuntimeException("Out of bounds access attempt for setH1At()");
    }
    
    setBit(haplotypes1[position / 32], position % 32, value);
}

int HaplotypePhase::getH2At(int position) const
{
    if (position >= length || position < 0) {
        throw RuntimeException("Out of bounds access attempt for getH2At()");
    }
    
    return getBit(haplotypes2[position / 32], position % 32);
}

void HaplotypePhase::setH2At(int position, int value)
{
    if (position >= length || position < 0) {
        throw RuntimeException("Out of bounds access attempt for setH2At()");
    }
    
    setBit(haplotypes2[position / 32], position % 32, value);
}

void HaplotypePhase::print() const
{
    // h1
    utilities::println("Haplotype 1:");
    for (int i = 0; i < calcArraySize(length); i++) {
        for (int j = 0; j < 32 && i * 32 + j < length; j++) {
            utilities::print(getBit(haplotypes1[i], j));
        }
    }
    utilities::println("");
    
    // h2
    utilities::println("Haplotype 2:");
    for (int i = 0; i < calcArraySize(length); i++) {
        for (int j = 0; j < 32 && i * 32 + j < length; j++) {
            utilities::print(getBit(haplotypes2[i], j));
        }
    }
    utilities::println("");
}

#undef calcArraySize