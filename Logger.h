//===---- Logger.h -  ---*- C++ -*-===//
//
//              Created by zeta on 17-8-1.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// 
// 
//
//===----------------------------------------------------------------------===//

#ifndef COOL_LOGGER_H
#define COOL_LOGGER_H

#include <cstdint>
#include <iostream>
#include <vector>

#include "Error.h"

class Logger {

public:
    /// error levels
    typedef int32_t Level;
    static const Level WARNING = 1;
    static const Level ERROR = 2;

    Logger();

    Logger(bool isWarningAsError, Level level);

    void appendStream(std::ostream *output);

    void warning(const Error &error);

    void error(const Error &error);

private:
    bool isWarningAsError = false;        /// if we treat warnings as errors
    Level level;                           /// the logging level
    std::vector<std::ostream *> streams;
};


#endif //COOL_LOGGER_H
