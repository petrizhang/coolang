//===---- Error.cpp -  ---*- C++ -*-===//
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

#include "Error.h"

void Error::print(std::ostream &output) const {
    output << start.row << '.' << start.col
           << '-'
           << end.row << '.' << end.col
           << ": " << msg << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Error &error) {
    error.print(os);
    return os;
}

Error Error::tokenTooLong(const Pos &start, const Pos &end) {
    Error error;
    error.start = start;
    error.end = end;
    error.msg = TOKEN_TOO_LONG;
    return error;
}

Error Error::eofInStrConst(const Pos &start, const Pos &end) {
    Error error;
    error.start = start;
    error.end = end;
    error.msg = EOF_IN_STR_CONST;
    return error;
}

Error Error::unclosedComment(const Pos &start, const Pos &end) {
    Error error;
    error.start = start;
    error.end = end;
    error.msg = UNCLOSED_COMMENT;
    return error;
}