//===---- Logger.cpp -  ---*- C++ -*-===//
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

#include "Logger.h"

Logger::Logger()
        : isWarningAsError(false),
          level(WARNING) {
    streams.push_back(&std::cerr);
}

Logger::Logger(bool isWarningAsError, Level level)
        : isWarningAsError(isWarningAsError),
          level(level) {
    streams.push_back(&std::cerr);
}

void Logger::appendStream(std::ostream *output) {
    streams.push_back(output);
}

void Logger::warning(const Error &error) {
    // firstly we output the prefix
    if (isWarningAsError) {
        for (auto pstream:streams) {
            *pstream << "error in " << error;;
        }
    } else {
        // don't report warnings if the output level is higher than WARNING
        if (this->level > WARNING) {
            return;
        }
        for (auto pstream:streams) {
            *pstream << "waring in " << error;;
        }
    }
}

void Logger::error(const Error &error) {
    for (auto pstream:streams) {
        *pstream << "error in " << error;
    }
}




