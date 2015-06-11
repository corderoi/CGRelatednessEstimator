//
//  stats.cpp
//  CGRE
//
//  Created by Ian Cordero on 5/6/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#include "stats.h"
#include "utilities.h"
#include <random>
#include <cmath> // M_PI, abs(), sin(), pow(), exp(), sqrt()

using namespace std;

static random_device generator;

double stats::mean(double numbers[], int size)
{
    return stats::sum(numbers, size);
}

int stats::randInt(int range)
{
    return utilities::randInt(range);
}

int stats::randInt(int lowest, int highest)
{
    return utilities::randInt(lowest, highest);
}

double stats::rand(double range)
{
    return rand(0, range);
}

double stats::rand(double lowest, double highest)
{
    uniform_real_distribution<double> distribution(lowest, highest);
    return distribution(generator);
}

double stats::rnorm(double mean, double stdDev)
{
    normal_distribution<double> distribution(mean, stdDev);
    return distribution(generator);
}

double stats::dnorm(double x, double mean, double stdDev)
{
    return (1.0 / sqrt(2.0 * M_PI * pow(stdDev, 2.0))) * exp(-pow(x - mean, 2.0) / (2.0 * pow(stdDev, 2.0)));
}

double stats::pnorm(double x)
{
    // Optimized for the standard normal CDF
    const double a = 0.31938153;
    const double b = -0.356563782;
    const double c = 1.781477937;
    const double d = -1.821255978;
    const double e = 1.330274429;
    const double f = 0.39894228040143267793994605993438;
    double g = 1.0 / (1.0 + 0.2316419 * fabs(x));
    double h = f * exp(- 0.5 * x * x) *
    (g * (a + g * (b + g * (c + g * (d + g * e)))));
    if (x > 0) {
        h = 1.0 - h;
    }
    return h;
}

