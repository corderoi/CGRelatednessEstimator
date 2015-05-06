//
//  exceptions.h
//  CGRE
//
//  Created by Ian Cordero on 5/5/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef CGRE_exceptions_h
#define CGRE_exceptions_h

#include <stdexcept>
#include <string> 

#define string std::string
#define logic_error std::logic_error
#define runtime_error std::runtime_error

class LogicException: public logic_error
{
public:
    LogicException() : logic_error("LogicException") {}
    LogicException(string message) : logic_error(message) {}
};

class RuntimeException: public runtime_error
{
public:
    RuntimeException() : runtime_error("RuntimeException") {}
    RuntimeException(string message) : runtime_error(message) {}
};

#undef string
#undef logic_error
#undef runtime_error

#endif
