//
//  main.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include <iostream>
#include "utilities.h"
#include "Time.h"
#include "HaplotypeSet.h"
#include "exceptions.h"
#include "Individual.h"
#include "RelatednessEstimator.h"
#include "HaplotypePhase.h"
#include <array>
#include <tuple>

using namespace std;

//
// Test the Relatedness Estimator project.
//
class RelatednessEstimatorTester
{
public:
    static void main()
    {
        // File names and short descriptions
        const auto jptFile = make_tuple("hapmap3_r2_b36_fwd.consensus.qc.poly.chr1_jpt+chb.unr.phased", "JPT");
        const auto ceuFile = make_tuple("hapmap3_r2_b36_fwd.consensus.qc.poly.chr1_ceu.unr.phased", "CEU");
        const auto aswFile = make_tuple("hapmap3_r2_b36_fwd.consensus.qc.poly.chr1_asw.unr.phased", "ASW");
        const array<tuple<string, string>, 3> files = { jptFile, ceuFile, aswFile };
        
        // Test RelatednessEstimator on each file
        for (const auto file : files) {
            const string filename = get<0>(file);
            
            // Generate data
            utilities::println("Generating haplotype set from " + get<1>(file) + " set -- file \"" + filename + "\"...");
            Time startGenerationTime;
            HaplotypeSet set(filename);
            utilities::println("Generation complete (" + utilities::toString(startGenerationTime.secondsSince()) +" seconds).");
            set.reportBasicInfo();
            
            // Non-related individuals
            const int totalIndividuals = set.getNumIndividuals();
            int whichIndividual = utilities::randInt(0, totalIndividuals - 1);
            const int firstPick = whichIndividual;
            while ((whichIndividual = utilities::randInt(0, totalIndividuals - 1)) == firstPick) {
            }
            if (firstPick == whichIndividual) {
                throw LogicException("Shouldn't reach here.");
            }
            utilities::println("Picked individuals " + utilities::toString(firstPick) + " and " + utilities::toString(whichIndividual) + " out of " + utilities::toString(totalIndividuals) + " individuals.");
            
            utilities::println("Estimating relatedness (baseline method)...");
            HaplotypePhase* h1 = set.getIndividual(firstPick)->haplotypePhase;
            HaplotypePhase* h2 = set.getIndividual(whichIndividual)->haplotypePhase;
            Time startREBTime;
            const double relatedness = RelatednessEstimator::estimateBasline(*h1, *h2);
            utilities::println("Relatedness: " + utilities::toString(relatedness) + " (" + utilities::toString(startREBTime.secondsSince()) + " seconds)");
            utilities::println("Estimating relatedness (advanced method)...");
            Time startRETime;
            const double relatedness2 = RelatednessEstimator::estimate(*h1, *h2, set);
            utilities::println("Relatedness: " + utilities::toString(relatedness2) + " (" + utilities::toString(startRETime.secondsSince()) + " seconds)");
            utilities::println("Estimation complete.");
            
            // Siblings
            shared_ptr<HaplotypePhase> h3(HaplotypePhase::createFrom(*h1, *h2));
            shared_ptr<HaplotypePhase> h4(HaplotypePhase::createFrom(*h1, *h2));
            Time startRESBTime;
            utilities::println("Estimating relatedness of siblings (baseline).");
            const double relatedness3 = RelatednessEstimator::estimateBasline(*h3, *h4);
            utilities::println("Relatedness: " + utilities::toString(relatedness3) + " (" + utilities::toString(startRESBTime.secondsSince()) + " seconds)");
            utilities::println("Estimating relatedness of siblings (advanced).");
            Time startRESTime;
            const double relatedness4 = RelatednessEstimator::estimate(*h3, *h4, set);
            utilities::println("Relatedness: " + utilities::toString(relatedness4) + " (" + utilities::toString(startRESTime.secondsSince()) + " seconds)");
            utilities::println("Estimation complete.");
            
            // Same individual
            utilities::println("Estimating same individual relatedness (baseline): ");
            Time t31;
            const double relatedness5 = RelatednessEstimator::estimateBasline(*h4, *h4);
            utilities::println("Relatedness: " + utilities::toString(relatedness5) + " (" + utilities::toString(t31.secondsSince()) + " seconds).");
            Time t32;
            utilities::println("Estimating same individual relatedness (advanced): ");
            const double relatedness6 = RelatednessEstimator::estimate(*h4, *h4, set);
            utilities::println("Relatedness: " + utilities::toString(relatedness6) + " (" + utilities::toString(t32.secondsSince()) + " seconds).");
            utilities::println("Estimation complete.");
            
            utilities::println("");
        }
        
        utilities::println("Finished testing RelatednessEstimator.");
    }
};

int main(int argc, char* argv[])
{
    // Test the Relatedness Estimator
    RelatednessEstimatorTester::main();
}