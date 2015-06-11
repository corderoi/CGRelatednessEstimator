//
//  HaplotypeSet.cpp
//  CGRE
//
//  Created by Ian Cordero on 6/10/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "HaplotypeSet.h"
#include <fstream>
#include "Individual.h"
#include "exceptions.h"
#include "HaplotypePhase.h"
#include "utilities.h"
#include "stats.h"

using namespace std;

HaplotypeSet::HaplotypeSet(string filename, int snpCap, int individCap)
{
    char c;
    string word;
    int col = 0;
    int rows = 0;
    ifstream ifile(filename);
    bool schemaSetup = true;
    while ((c = ifile.get()) != EOF) {
        switch (c) {
            case '\n':
                rows++;
                if (snpCap > 0 && rows >= snpCap) {
                    goto end_count___;
                }
                if (schemaSetup) {
                    schemaSetup = false;
                    col++;
                }
                break;
            case ' ':
                if (schemaSetup) {
                    col++;
                }
                if (individCap > 0 && col >= individCap) {
                    goto end_count___;
                }
                break;
            default:
                break;
        }
    }
end_count___:
    schemaSetup = true;
    const int numRows = rows - 1;
    rows = 0;
    col = 0;
    ifile.clear();
    ifile.seekg(ios::beg);
    vector<char> designated;
    while ((c = ifile.get())) {
        switch (c) {
            case ' ':
                if (schemaSetup) {
                    switch (col) {
                        case 0:
                            break;
                        case 1:
                            setPosition = word;
                            break;
                        default:
                            if (col % 2 == 0) {
                                string individualID = word;
                                individualID.pop_back(); // remove last 2 chars of ID
                                individualID.pop_back();
                                individuals.push_back(new Individual(individualID, numRows));
                            }
                            break;
                    }
                } else {
                    switch (col) {
                        case 0:
                            rsIDs.push_back(word);
                            break;
                        case 1:
                            positionNums.push_back(word);
                            break;
                        case 2:
                            designated.push_back(word[0]);
                        default: // intentional fall-through
                            if (col % 2 == 0) {
                                const int val = (designated.at(rows) == word[0]) ? 0b1 : 0b0;
                                individuals.at((col-2) / 2)->haplotypePhase->setH1At(rows, val);
                            } else {
                                const int val = (designated.at(rows) == word[0]) ? 0b1 : 0b0;
                                individuals.at((col-2) / 2)->haplotypePhase->setH2At(rows, val);
                            }
                            break;
                    }
                }
                col++;
                word = "";
                break;
            case '\n':
                if (snpCap > 0 && rsIDs.size() >= snpCap) {
                    goto end_read___;
                }
                col = 0;
                if (schemaSetup) {
                    schemaSetup = false;
                } else {
                    rows++;
                }
                break;
            case EOF:
                if (schemaSetup) {
                    throw RuntimeException("Did not encounter data in file " + filename + ".");
                }
                goto end_read___;
            default:
                word += c;
                break;
        }
    }
end_read___:;
    
    if (rsIDs.size() != positionNums.size()) {
        throw LogicException("Error reading data: size of IDs and position numbers do not match.");
    }
    for (int i = 0; i < individuals.size(); i++) {
        if (individuals.at(i)->haplotypePhase->getLength() != rsIDs.size()) {
            throw LogicException("Error reading data: size of IDs and individual Haplotype lengths do not match.");
        }
    }
    
    for (int i = 0; i < rsIDs.size(); i++) {
        minorAlleles.push_back((getAlleleFreq(i) < 0.5));
    }
}

HaplotypeSet::HaplotypeSet(int numSNPs, int numIndividuals)
{
    setPosition = "synthetic";
    
    if (numSNPs <= 0 || numIndividuals <= 0) {
        throw LogicException("numSNPs and numIndividuals must be positive.");
    }
    
    for (int i = 0; i < numIndividuals; i++) {
        individuals.push_back(new Individual("SI" + utilities::toString(i + 1), numSNPs));
    }
    
    for (int i = 0; i < numSNPs; i++) {
        const double alleleFrequency = stats::rand(0.0, 1.0);
        
        rsIDs.push_back("synth_rs" + utilities::toString(i + 1));
        positionNums.push_back(utilities::toString(i + 1));
        minorAlleles.push_back((alleleFrequency < 0.5));
        
        for (const auto individual : individuals) {
            individual->haplotypePhase->setH1At(i, (stats::rand(1.0) < alleleFrequency) ? 0b1 : 0b0);
            individual->haplotypePhase->setH2At(i, (stats::rand(1.0) < alleleFrequency) ? 0b1 : 0b0);
        }
    }
    
    if (rsIDs.size() != positionNums.size()) {
        throw LogicException("Error: size of IDs and position numbers do not match.");
    }
    for (int i = 0; i < individuals.size(); i++) {
        if (individuals.at(i)->haplotypePhase->getLength() != rsIDs.size()) {
            throw LogicException("Error: size of IDs and individual Haplotype lengths do not match.");
        }
    }
}

void HaplotypeSet::print() const
{
    utilities::print("rsID " + setPosition + " ");
    for (int i = 0; i < individuals.size(); i++) {
        if (i != 0) {
            utilities::print(" ");
        }
        utilities::print(individuals.at(i)->iD);
        utilities::print("_A ");
        utilities::print(individuals.at(i)->iD);
        utilities::print("_B");
    }
    utilities::println("");
    
    for (int i = 0; i < rsIDs.size(); i++) {
        utilities::print(rsIDs.at(i) + " " + positionNums.at(i) + " ");
        for (int j = 0; j < individuals.size(); j++) {
            if (j != 0) {
                utilities::print(" ");
            }
            utilities::print(individuals.at(j)->haplotypePhase->getH1At(i));
            utilities::print(" ");
            utilities::print(individuals.at(j)->haplotypePhase->getH2At(i));
        }
        utilities::println("");
    }
}

HaplotypeSet::~HaplotypeSet()
{
    for (auto individual : individuals) {
        delete individual;
    }
}

void HaplotypeSet::reportBasicInfo() const
{
    utilities::println("Basic Info:");
    utilities::println(utilities::toString(rsIDs.size()) + " SNPs, " + utilities::toString(individuals.size()) + " individuals.");
}

double HaplotypeSet::getAlleleFreq(int whichSNP) const
{
    if (whichSNP < 0 || whichSNP >= rsIDs.size()) {
        throw RuntimeException("Attempted to access out of bounds index.");
    }
    
    const int snpTotal = utilities::reduce(individuals, toFunction(int(int, Individual*), [&] (int chainSum, Individual* i) { return chainSum + i->haplotypePhase->getH1At(whichSNP) + i->haplotypePhase->getH2At(whichSNP); }), 0);
    const int numAlleles = getNumAlleles();
    const double alleleFreq = utilities::toDouble(snpTotal) / utilities::toDouble(numAlleles);
    return alleleFreq;
}

double HaplotypeSet::getMinorAlleleFreq(int whichSNP) const
{
    const double alleleFreq = getAlleleFreq(whichSNP);
    if (minorAlleles.at(whichSNP)) {
        return alleleFreq;
    } else {
        return 1.0 - alleleFreq;
    }
}

bool HaplotypeSet::isMinorAllele(int whichSNP) const
{
    return minorAlleles.at(whichSNP);
}

int HaplotypeSet::getAlleleSNPValue(int whichAllele, int whichSNP) const
{
    if (whichSNP < 0 || whichSNP >= rsIDs.size() || whichAllele < 0 || whichAllele >= individuals.size() * 2) {
        throw RuntimeException("Attempted to access out of bounds index.");
    }
    
    return (whichAllele % 2 == 0) ? individuals.at(whichAllele / 2)->haplotypePhase->getH1At(whichSNP) : individuals.at(whichAllele / 2)->haplotypePhase->getH2At(whichSNP);
}

int HaplotypeSet::getNumSNPs() const
{
    return utilities::toInt(rsIDs.size());
}

int HaplotypeSet::getNumIndividuals() const
{
    return utilities::toInt(individuals.size());
}

int HaplotypeSet::getNumAlleles() const
{
    return getNumIndividuals() * 2;
}

Individual* HaplotypeSet::getIndividual(int whichIndividual) const
{
    return individuals.at(whichIndividual);
}


int HaplotypeSet::getNumMinorAllelesAt(int position, const HaplotypePhase &haplotypes) const
{
    const int targetVal = (minorAlleles.at(position)) ? 1 : 0;
    int numMinorAlleles = 0;
    if (haplotypes.getH1At(position) == targetVal) {
        numMinorAlleles++;
    }
    if (haplotypes.getH2At(position) == targetVal) {
        numMinorAlleles++;
    }
    return numMinorAlleles;
}