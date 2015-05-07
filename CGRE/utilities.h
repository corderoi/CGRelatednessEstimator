//
//  utilities.h
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __CGRE__utilities__
#define __CGRE__utilities__

#include <cstdlib> // exit()
#include <iostream>
#include <sstream> // ostringstream
#include <vector>
#include <functional>
#include <algorithm>

#define vector std::vector
#define function std::function
#define string std::string

//
// utilities
// A collection of handy functions that I use often. A mix of syntactic sugar
// and actual utility.
//
namespace utilities
{
    // Random Number Generation
    
    //
    // randInt()
    /// Get a random integer between \c 0 and \c range-1, inclusive.
    //
    int randInt(int range);
    
    //
    // randInt()
    /// Get a random integer between lowest and highest, inclusive.
    //
    int randInt(int lowest, int highest);
    
    // Casts
    
    //
    // toInt()
    /// Returns an \c int representation of \c number.
    //
    template <typename T>
    int toInt(T number)
    {
        return static_cast<int>(number);
    }
    
    //
    // toDouble()
    /// Returns a \c double representation of \c number.
    //
    template <typename T>
    double toDouble(T number)
    {
        return static_cast<double>(number);
    }
    
    //
    // toString()
    /// Returns a \c string representation of \c item.
    //
    template <typename T>
    string toString(T item)
    {
        return (std::ostringstream() << item).str();
    }
    
    //
    // toBool()
    /// Returns C++'s \c bool representation of \c item.
    //
    template <typename T>
    bool toBool(T item)
    {
        return static_cast<bool>(item);
    }
    
    //
    // toFunction()
    /// Slightly nicer syntax for passing known-type lambdas to the below implementations
    /// of \c forEach/map/reduce
    //
    #define toFunction(functionType, arg) \
    static_cast<function<functionType>>(arg)
    
    // Pointer Manipulation
    
    //
    // nullify()
    /// Deletes an object and sets its pointer to \c null
    //
    template <typename T>
    void nullify(T& pointer)
    {
        delete pointer;
        pointer = nullptr;
    }
    
    //
    // replace()
    /// Deletes an object and replaces it with the new \c object.
    //
    template <typename T>
    void replace(T& pointer, T object)
    {
        delete pointer;
        pointer = object;
    }
    
    // Collection Manipulation
    
    //
    // forEach()
    /// Executes \c action function on all elements of \c elements.
    //
    template <typename T>
    void forEach(vector<T>& elements, function<void(T)> action)
    {
        std::for_each(elements.begin(), elements.end(), action);
    }
    
    //
    // map()
    /// Maps function \c action onto vector \c elements, returning a vector
    /// containing the results of the mapping.
    //
    template <typename T, typename R>
    vector<R> map(const vector<T>& elements, function<R(T)> transform)
    {
        vector<R> results;
        results.resize(elements.size());
        std::transform(elements.begin(), elements.end(), results.begin(), transform);
        return results;
    }
    
    template <typename T, typename R>
    static R reduceHelper(typename vector<T>::const_iterator p, typename vector<T>::const_iterator end, function<R(R, T)> reduction, R startingValue)
    {
        if (p != end) {
            return reduction(reduceHelper(p+1, end, reduction, startingValue), *p);
        } else {
            return startingValue;
        }
    }
    
    //
    // reduce()
    /// Reduces the set of \c elements using function \c reduction on \c startingValue
    /// and the last element, then on the result of that computation and the second-to-last
    /// element, and so on.
    //
    // Depends on reduceHelper (above).
    //
    template <typename T, typename R>
    R reduce(const vector<T>& elements, function<R(R, T)> reduction, R startingValue)
    {
        return reduceHelper(elements.begin(), elements.end(), reduction, startingValue);
    }
    
    //
    // filter()
    /// Returns a vector with elements that do not satisfy the \c condition function
    /// removed. Not necessarily an efficient implementation (for the moment..! [todo]).
    //
    template <typename T>
    vector<T> filter(const vector<T>& elements, function<bool(T)> condition)
    {
        vector<T> results;
        
        for (T element : elements) {
            if (condition(element)) {
                results.push_back(element);
            }
        }
        
        return results;
    }
    
    // Command Line I/O
    
    //
    // print()
    /// Prints to console without a newline.
    //
    template <typename T>
    void print(T item)
    {
        std::cout << item;
    }
    
    //
    // println()
    /// Prints \c item to console, followed by a newline.
    //
    template <typename T>
    void println(T item)
    {
        std::cout << item << std::endl;
    }
    
    //
    // error()
    /// Prints error \c message to console, then exits.
    //
    template <typename T>
    void error(T message)
    {
        std::cerr << message << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //
    // debug()
    /// Wrapper for \c println() that can be toggled using the \c DEBUG_MODE macro below.
    //
    template <typename T>
    void debug(T message)
    {
        #define DEBUG_MODE true
        if (DEBUG_MODE) {
            println(message);
        }
        #undef DEBUG_MODE
    }
}

#undef vector
#undef function
#undef string

#endif /* defined(__CGRE__utilities__) */