//
//  stats.h
//  CGRE
//
//  Created by Ian Cordero on 5/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __CGRE__stats__
#define __CGRE__stats__

namespace stats
{
    // General
    
    template <typename T>
    T sum(T numbers[], int size)
    {
        T total = T();
        for (int i = 0; i < size; i++) {
            total += numbers[i];
        }
        return total;
    }
    
    double mean(double numbers[], int size);
    
    // Uniform Dist.
    
    // Reused from 'utilities'
    int randInt(int range);
    
    int randInt(int lowest, int highest);
    
    //
    // rand()
    // Draws random real numbers from a uniform distribution.
    //
    double rand(double range);
    
    double rand(double lowest, double highest);
    
    // Normal Dist.
    
    //
    // rnorm()
    // Draws random numbers from the normal dist. with mean 'mean' and std. dev. 'stdDev'.
    //
    double rnorm(double mean = 0.0, double stdDev = 1.0);
    
    //
    // dnorm()
    // The probability density (or mass) function.
    // Returns the probability of 'x' according to the normal prob. dist.
    //
    double dnorm(double x, double mean = 0.0, double stdDev = 1.0);
    
    //
    // pnorm()
    // The normal cumulative density function.
    // Returns the density of the normal dist. contained from (inf., x].
    //
    double pnorm(double x);
    
    double pnorm(double x, double mean, double stdDev = 1.0);
    
    //
    // qnorm()
    // The inverse normal cumulative density function.
    // Returns the x s.t. (-inf., x] has density 'a'.
    //
    double qnorm(double a);
    
    double qnorm(double a, double mean, double stdDev = 1.0);
    
    // Association Statistics
    
    double calcSA();
    
    double calcNCP();
    
    double calcPower();
}

#endif /* defined(__CGRE__stats__) */
