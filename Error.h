//===---- Error.h -  ---*- C++ -*-===//
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

#ifndef COOL_ERROR_H
#define COOL_ERROR_H

#include <iostream>
#include "Token.h"

struct Error {
    const char *msg = nullptr;
    Pos start;
    Pos end;

    void print(std::ostream &output) const;

    friend std::ostream &operator<<(std::ostream &os, const Error &error);

    static Error tokenTooLong(const Pos &start, const Pos &end);

    static Error eofInStrConst(const Pos &start, const Pos &end);

    static Error unclosedComment(const Pos &start, const Pos &end);

    /// all used error message
    constexpr static const char *TOKEN_TOO_LONG = "the token is too long";
    constexpr static const char *EOF_IN_STR_CONST = "EOF in string constant";
    constexpr static const char *UNCLOSED_COMMENT = "unmatched *)";
};


#endif //COOL_ERROR_H
