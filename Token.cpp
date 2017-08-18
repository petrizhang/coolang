//===---- Token.cpp -  ---*- C++ -*-===//
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

#include "Token.h"

Token Token::makeBoolLiteral(bool boolValue, const Pos &start, const Pos &end) {
    return Token(boolValue, start, end);
}

Token Token::makeIntLiteral(int64_t intValue, const Pos &start, const Pos &end) {
    return Token(intValue, start, end);
}

Token Token::makeStrLiteral(const Entry *symbol, const Pos &start, const Pos &end) {
    return Token(TK_STR_CONST, symbol, start, end);
}

Token Token::makeIdentifier(const Entry *symbol, const Pos &start, const Pos &end) {
    return Token(TK_ID, symbol, start, end);
}

Token Token::makeNormalToken(TokenKind tokenKind, const Pos &start, const Pos &end) {
    return Token(tokenKind, start, end);
}

Token Token::makeTokenNoPos(TokenKind tokenKind) {
    return Token(tokenKind);
}

Token::Token(bool boolValue, const Pos &start, const Pos &end)
        : tokenKind(TK_BOOL_CONST),
          start(start),
          end(end) {
    value.boolValue = boolValue;
}

Token::Token(int64_t intValue, const Pos &start, const Pos &end)
        : tokenKind(TK_INT_CONST),
          start(start),
          end(end) {
    value.intValue = intValue;
}

Token::Token(TokenKind tokenKind, const Entry *symbol, const Pos &start, const Pos &end)
        : tokenKind(tokenKind),
          symbol(symbol),
          start(start),
          end(end) {
}

Token::Token(TokenKind tokenKind, const Pos &start, const Pos &end)
        : tokenKind(tokenKind),
          start(start),
          end(end) {
}

Token::Token(TokenKind tokenKind)
        : tokenKind(tokenKind) {
}

TokenKind Token::getTokenKind() const {
    return tokenKind;
}

const Pos &Token::getStart() const {
    return start;
}

const Pos &Token::getEnd() const {
    return end;
}

bool Token::getBoolValue() const {
    return value.boolValue;
}

int64_t Token::getIntValue() const {
    return value.intValue;
}

const Entry *Token::getSymbol() const {
    return symbol;
}

const char *Token::kindRepr() const {
    auto end = tokenReprMap.end();
    auto it = tokenReprMap.find(this->tokenKind);
    if (it != end) {
        return it->second;
    }
    return "<Invalid Token>";
}

void Token::setPos(const Pos &start, const Pos &end) {
    this->start = start;
    this->end = end;
}

void Token::print(std::ostream &output) const {
    output << '{'
           << kindRepr() << ", "
           << start.row << '.' << start.col
           << '-'
           << end.row << '.' << end.col
           << ", ";
    switch (tokenKind) {
        case TK_ID:
        case TK_STR_CONST:
            output << '"' << symbol->getString() << '"';
            break;
        case TK_BOOL_CONST:
            if (value.boolValue) {
                output << "true";
            } else {
                output << "false";
            }
            break;
        case TK_INT_CONST:
            output << value.intValue;
            break;
        default:
            output << "<novalue>";
    }
    output << '}';
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    token.print(os);
}

std::map<TokenKind, const char *> tokenReprMap = {
        {TK_CLASS,      "CLASS"},
        {TK_ELSE,       "ELSE"},
        {TK_FI,         "FI"},
        {TK_IF,         "IF"},
        {TK_IN,         "IN"},
        {TK_INHERITS,   "INHERITS"},
        {TK_LET,        "LET"},
        {TK_LOOP,       "LOOP"},
        {TK_POOL,       "POOL"},
        {TK_THEN,       "THEN"},
        {TK_WHILE,      "WHILE"},
        {TK_CASE,       "CASE"},
        {TK_ESAC,       "ESAC"},
        {TK_OF,         "OF"},
        {TK_DARROW,     "DARROW"},
        {TK_NEW,        "NEW"},
        {TK_ISVOID,     "ISVOID"},
        {TK_STR_CONST,  "STR_CONST"},
        {TK_INT_CONST,  "INT_CONST"},
        {TK_BOOL_CONST, "BOOL_CONST"},
        {TK_ID,         "ID"},
        {TK_ASSIGN,     "ASSIGN"},
        {TK_NOT,        "NOT"},
        {TK_AND,        "AND"},
        {TK_OR,         "OR"},
        {TK_XOR,        "XOR"},
        {TK_LE,         "LE"},
        {TK_ERROR,      "ERROR"},
        {'+',           "'+'"},
        {'/',           "'/'"},
        {'-',           "'-'"},
        {'*',           "'*'"},
        {'=',           "'='"},
        {'<',           "'<'"},
        {'.',           "'.'"},
        {'~',           "'~'"},
        {',',           "','"},
        {';',           "';'"},
        {':',           "':'"},
        {'(',           "'('"},
        {')',           "')'"},
        {'@',           "'@'"},
        {'{',           "'{'"},
        {'}',           "'}'"},

};

std::map<const char *, Token, StrCmp> tokenMap = {
        {"class",    Token::makeTokenNoPos(TK_CLASS)},
        {"else",     Token::makeTokenNoPos(TK_ELSE)},
        {"fi",       Token::makeTokenNoPos(TK_FI)},
        {"if",       Token::makeTokenNoPos(TK_IF)},
        {"in",       Token::makeTokenNoPos(TK_IN)},
        {"inherits", Token::makeTokenNoPos(TK_INHERITS)},
        {"let",      Token::makeTokenNoPos(TK_LET)},
        {"loop",     Token::makeTokenNoPos(TK_LOOP)},
        {"pool",     Token::makeTokenNoPos(TK_POOL)},
        {"then",     Token::makeTokenNoPos(TK_THEN)},
        {"while",    Token::makeTokenNoPos(TK_WHILE)},
        {"case",     Token::makeTokenNoPos(TK_CASE)},
        {"esac",     Token::makeTokenNoPos(TK_ESAC)},
        {"new",      Token::makeTokenNoPos(TK_NEW)},
        {"isvoid",   Token::makeTokenNoPos(TK_ISVOID)},
        {"not",      Token::makeTokenNoPos(TK_NOT)},
        {"and",      Token::makeTokenNoPos(TK_AND)},
        {"or",       Token::makeTokenNoPos(TK_OR)},
        {"xor",      Token::makeTokenNoPos(TK_XOR)},
        {"true",     Token::makeBoolLiteral(true, Pos(0, 0), Pos(0, 0))},
        {"false",    Token::makeBoolLiteral(false, Pos(0, 0), Pos(0, 0))},
};















