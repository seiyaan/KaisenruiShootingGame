//
//  GMException.cpp
//  Game Framework
//
//  Created by numata on Jan 03, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMException.h"
#include <iostream>

#include <TargetConditionals.h>

#if (TARGET_OS_IPHONE || MAC_OS_X_VERSION_MAX_ALLOWED >= 1050)
#include <execinfo.h>
#endif


GMException::GMException() throw()
    : mMessage("Unknown Error")
{
    std::cerr << "<<GMException>> Karakuri2 Runtime Error: " << std::endl << std::endl;
    
    std::cerr << "==== Error Message ====" << std::endl;
    std::cerr << "    " << mMessage << std::endl;
    std::cerr << "===================" << std::endl << std::endl;

    std::cerr << "==== Backtrace ====" << std::endl;
#if (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
    std::cerr << "**** Backtrace is not available in Mac OS X 10.4." << std::endl;
#else
    void* trace[256];
    int n = backtrace(trace, sizeof(trace) / sizeof(trace[0]));
    backtrace_symbols_fd(trace, n, 2);
#endif
    std::cerr << "===================" << std::endl;
}

GMException::GMException(const char* format, ...) throw()
{
    static char buffer[1024];

    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    mMessage = buffer;

    std::cerr << "<<GMException>> Karakuri2 Runtime Error: " << std::endl << std::endl;
    
    std::cerr << "==== Error Message ====" << std::endl;
    std::cerr << "    " << mMessage << std::endl;
    std::cerr << "===================" << std::endl << std::endl;

    std::cerr << "==== Backtrace ====" << std::endl;
#if (MAC_OS_X_VERSION_MAX_ALLOWED < 1050)
    std::cerr << "**** Backtrace is not available in Mac OS X 10.4." << std::endl;
#else
    void* trace[256];
    int n = backtrace(trace, sizeof(trace) / sizeof(trace[0]));
    backtrace_symbols_fd(trace, n, 2);
#endif
    std::cerr << "===================" << std::endl;
}

GMException::GMException(const std::string& message) throw()
    : mMessage(message)
{
    // Do nothing
}

GMException::~GMException() throw()
{
    // Do noghing
}

std::string GMException::getExceptionClassName() const
{
    return "GMException";
}

const char* GMException::what() const throw()
{
    return mMessage.c_str();
}


GMArithmeticException::GMArithmeticException() throw()
{
    // Do nothing
}

GMArithmeticException::GMArithmeticException(const char* format, ...) throw()
{
    static char buffer[1024];
    
    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    mMessage = buffer;
}

GMArithmeticException::GMArithmeticException(const std::string& message) throw()
    : GMException(message)
{
    // Do nothing
}


GMInvalidOperationException::GMInvalidOperationException() throw()
{
    // Do nothing
}

GMInvalidOperationException::GMInvalidOperationException(const char* format, ...) throw()
{
    static char buffer[1024];
    
    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    mMessage = buffer;
}

GMInvalidOperationException::GMInvalidOperationException(const std::string& message) throw()
    : GMException(message)
{
    // Do nothing
}


GMOutOfMemoryException::GMOutOfMemoryException() throw()
{
    // Do nothing
}

GMOutOfMemoryException::GMOutOfMemoryException(const char* format, ...) throw()
{
    static char buffer[1024];
    
    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    mMessage = buffer;
}

GMOutOfMemoryException::GMOutOfMemoryException(const std::string& message) throw()
    : GMException(message)
{
    // Do nothing
}


