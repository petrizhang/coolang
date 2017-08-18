//===---- test_token.cpp -  ---*- C++ -*-===//
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


#include <gtest/gtest.h>
#include "Token.h"

TEST(scanner, token) {
    StringTable table;
    Pos start(1, 1);
    Pos end(2, 2);

    // test for bool literal token
    auto boolToken = Token::makeBoolLiteral(true, start, end);
    EXPECT_EQ(true, boolToken.getBoolValue());
    EXPECT_EQ(TK_BOOL_CONST, boolToken.getTokenKind());

    // test for string literal token
    auto symbol = table.addString("zhang");
    auto stringLiteralToken = Token::makeStrLiteral(symbol, start, end);
    EXPECT_EQ(TK_STR_CONST, stringLiteralToken.getTokenKind());
    EXPECT_TRUE(stringLiteralToken.getSymbol()->equalString("zhang"));

    // test for identifier token
    auto idToken = Token::makeIdentifier(symbol, start, end);
    EXPECT_EQ(TK_ID, idToken.getTokenKind());
    EXPECT_TRUE(idToken.getSymbol()->equalString("zhang"));
}