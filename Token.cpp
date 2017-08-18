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

const char *Token::kindStr() const {
    switch (tokenKind) {
        case 0:
            return ("EOF");
            break;
        case (TK_CLASS):
            return ("CLASS");
            break;
        case (TK_ELSE):
            return ("ELSE");
            break;
        case (TK_FI):
            return ("FI");
            break;
        case (TK_IF):
            return ("IF");
            break;
        case (TK_IN):
            return ("IN");
            break;
        case (TK_INHERITS):
            return ("INHERITS");
            break;
        case (TK_LET):
            return ("LET");
            break;
        case (TK_LOOP):
            return ("LOOP");
            break;
        case (TK_POOL):
            return ("POOL");
            break;
        case (TK_THEN):
            return ("THEN");
            break;
        case (TK_WHILE):
            return ("WHILE");
            break;
        case (TK_ASSIGN):
            return ("ASSIGN");
            break;
        case (TK_CASE):
            return ("CASE");
            break;
        case (TK_ESAC):
            return ("ESAC");
            break;
        case (TK_OF):
            return ("OF");
            break;
        case (TK_DARROW):
            return ("DARROW");
            break;
        case (TK_NEW):
            return ("NEW");
            break;
        case (TK_STR_CONST):
            return ("STR_CONST");
            break;
        case (TK_INT_CONST):
            return ("INT_CONST");
            break;
        case (TK_BOOL_CONST):
            return ("BOOL_CONST");
            break;
        case (TK_ID):
            return ("ID");
            break;
        case (TK_ERROR):
            return ("ERROR");
            break;
        case (TK_LE):
            return ("LE");
            break;
        case (TK_NOT):
            return ("NOT");
            break;
        case (TK_ISVOID):
            return ("ISVOID");
            break;
        case '+':
            return ("'+'");
            break;
        case '/':
            return ("'/'");
            break;
        case '-':
            return ("'-'");
            break;
        case '*':
            return ("'*'");
            break;
        case '=':
            return ("'='");
            break;
        case '<':
            return ("'<'");
            break;
        case '.':
            return ("'.'");
            break;
        case '~':
            return ("'~'");
            break;
        case ',':
            return ("','");
            break;
        case ';':
            return ("';'");
            break;
        case ':':
            return ("':'");
            break;
        case '(':
            return ("'('");
            break;
        case ')':
            return ("')'");
            break;
        case '@':
            return ("'@'");
            break;
        case '{':
            return ("'{'");
            break;
        case '}':
            return ("'}'");
            break;
        default:
            return ("<Invalid Token>");
    }
}

void Token::setPos(const Pos &start, const Pos &end) {
    this->start = start;
    this->end = end;
}

void Token::print(std::ostream &output) const {
    output << '{'
           << kindStr() << ", "
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
        {"true",     Token::makeBoolLiteral(true, Pos(0, 0), Pos(0, 0))},
        {"false",    Token::makeBoolLiteral(false, Pos(0, 0), Pos(0, 0))},
};

//case '+': return("'+'"); break;
//case '/': return("'/'"); break;
//case '-': return("'-'"); break;
//case '*': return("'*'"); break;
//case '=': return("'='"); break;
//case '<': return("'<'"); break;
//case '.': return("'.'"); break;
//case '~': return("'~'"); break;
//case ',': return("','"); break;
//case ';': return("';'"); break;
//case ':': return("':'"); break;
//case '(': return("'('"); break;
//case ')': return("')'"); break;
//case '@': return("'@'"); break;
//case '{': return("'{'"); break;
//case '}': return("'}'"); break;
//default:  return("<Invalid Token>");
