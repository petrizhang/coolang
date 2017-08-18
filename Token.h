//===---- Token.h -  ---*- C++ -*-===//
//
//              Created by zeta on 17-7-28.
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

#ifndef COOL_TOKEN_H
#define COOL_TOKEN_H

#include <cstdint>
#include <cstring>
#include <cassert>
#include <vector>
#include <iostream>

#include "StringTable.h"

#define MAX_STR_LENGTH 1024


/// Token类型

typedef uint16_t TokenKind;

enum : TokenKind {
    TK_CLASS = 258,
    TK_ELSE = 259,
    TK_FI = 260,
    TK_IF = 261,
    TK_IN = 262,
    TK_INHERITS = 263,
    TK_LET = 264,
    TK_LOOP = 265,
    TK_POOL = 266,
    TK_THEN = 267,
    TK_WHILE = 268,
    TK_CASE = 269,
    TK_ESAC = 270,
    TK_OF = 271,
    TK_DARROW = 272,
    TK_NEW = 273,
    TK_ISVOID = 274,
    TK_STR_CONST = 275,
    TK_INT_CONST = 276,
    TK_BOOL_CONST = 277,
    TK_ID = 278,//TK_TYPEID = 278,TK_OBJECTID = 279,
    TK_ASSIGN = 280,
    TK_NOT = 281,
    TK_LE = 282,
    TK_ERROR = 283,
    TK_LET_STMT = 285
};

struct Pos {
    Pos() : row(0), col(0) {}

    Pos(size_t row, size_t col) : row(row), col(col) {}

    size_t row; /// 行
    size_t col; /// 列
};

class Token {
public:
    static Token makeBoolLiteral(bool boolValue, const Pos &start, const Pos &end);

    static Token makeIntLiteral(int64_t intValue, const Pos &start, const Pos &end);

    static Token makeStrLiteral(const Entry *symbol, const Pos &start, const Pos &end);

    static Token makeIdentifier(const Entry *symbol, const Pos &start, const Pos &end);

    static Token makeNormalToken(TokenKind tokenKind, const Pos &start, const Pos &end);

    static Token makeTokenNoPos(TokenKind tokenKind);

    TokenKind getTokenKind() const;

    const Pos &getStart() const;

    const Pos &getEnd() const;

    bool getBoolValue() const;

    int64_t getIntValue() const;

    const Entry *getSymbol() const;

    const char *kindStr() const;

    void setPos(const Pos &start, const Pos &end);

    void print(std::ostream &output) const;

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    Token() = delete;

    /// 布尔字面值
    Token(bool boolValue, const Pos &start, const Pos &end);

    /// 整型字面值
    Token(int64_t intValue, const Pos &start, const Pos &end);

    /// 字符串字面值/id
    Token(TokenKind tokenKind, const Entry *symbol, const Pos &start, const Pos &end);

    /// 其他词素(仅需要知道类型的)
    Token(TokenKind tokenKind, const Pos &start, const Pos &end);

    /// 没有位置
    Token(TokenKind tokenKind);

    TokenKind tokenKind;  /// token类型
    const Entry *symbol = nullptr;       /// 标识符/字符串常量
    union {
        bool boolValue;
        int64_t intValue;
    } value;        /// token的字面值
    Pos start;      /// 起始位置
    Pos end;        /// 结束位置
};

extern std::map<const char *, Token, StrCmp> tokenMap;
#endif //COOL_TOKEN_H
