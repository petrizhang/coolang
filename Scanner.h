//===---- Scanner.h -  ---*- C++ -*-===//
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

#ifndef COOL_SCANNER_H
#define COOL_SCANNER_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "Logger.h"

class Scanner {
public:
    Scanner(std::istream *input, StringTable &strTable, StringTable &idTable)
            : input(input),
              strTable(strTable),
              idTable(idTable),
              bufferPos(0) {
    }

    bool scan(std::vector<Token> &tokens) {
        char c;
        bool success = true;
        while (true) {
            // 清空缓冲区，跳过空白，读取一个字符，记录当前位置
            clearBuffer();
            skipBlank();
            c = get(success);
            if (!success) {
                return false;
            }
            startPos = {lineNo, columnNo};
            if (c == EOF) {
                // eof
                return true;
            } else if (c == '(') {
                // 注释
                if (peek() == '*') {
                    get(success);
                    while (true) {
                        c = get(success, false);
                        if (c == EOF) {
                            logger.error(Error::unclosedComment(startPos, endPos()));
                            return false;
                        }
                        if (c == '*' && peek() == ')') {
                            get(success, false);
                            break;
                        }
                    }
                }
            } else if (c == '"') {
                // 字符串常量

                // 首先清空buf准备保存字符串
                clearBuffer();

                // 然后继续读取字符
                c = get(success);
                if (!success) {
                    return false;
                }

                while (c != '"') {
                    if (c == EOF) {
                        // TODO =========================== 引号未闭合错误
                        logger.error(Error::eofInStrConst(startPos, endPos()));
                        return false;
                    }
                    c = get(success);
                    if (!success) {
                        return false;
                    }
                }
                // 遇到了引号
                bufferPos--;
                buffer[bufferPos] = 0;
                // 向buffer末尾添加'\0'
                bufferTrail();
                const Entry *symbol = strTable.addString(buffer);
                tokens.push_back(Token::makeStrLiteral(symbol, startPos, endPos()));
            } else if (isSingleSymbol(c)) {
                // 特殊符号
                switch (c) {
                    case '=':
                        // =>
                        if (peek() != '>') {
                            tokens.push_back(
                                    Token::makeNormalToken(c, startPos, endPos())
                            );
                        } else {
                            c = get(success);
                            if (!success) {
                                return false;
                            }
                            tokens.push_back(
                                    Token::makeNormalToken(TK_DARROW, startPos, endPos())
                            );
                        }
                        break;
                    case '<':
                        // <-
                        if (peek() != '-') {
                            tokens.push_back(
                                    Token::makeNormalToken(c, startPos, endPos())
                            );
                        } else {
                            // =>
                            c = get(success);
                            if (!success) {
                                return false;
                            }
                            tokens.push_back(
                                    Token::makeNormalToken(TK_ASSIGN, startPos, endPos())
                            );
                        }
                        break;
                    default:
                        tokens.push_back(
                                Token::makeNormalToken(c, startPos, endPos())
                        );
                }
            } else if (isalpha(c) || c == '_') {
                // 标识符
                while (isalpha(c) || c == '_') {
                    c = get(success);
                    if (!success) {
                        return false;
                    }
                }
                unget();
                // 向buffer末尾添加'\0'
                bufferTrail();
                auto it = tokenMap.find(buffer);
                if (it != tokenMap.end()) {
                    // 关键字
                    it->second.setPos(startPos,endPos());
                    tokens.push_back(it->second);
                } else {
                    // 标识符/布尔常量
                    const Entry *symbol = idTable.addString(buffer);
                    Token token = Token::makeIdentifier(symbol, startPos, endPos());
                    tokens.push_back(token);
                }
            } else if (isdigit(c)) {
                // 数字
                while (isdigit(c)) {
                    c = get(success);
                    if (!success) {
                        return false;
                    }
                }
                unget();
                // 向buffer末尾添加'\0'
                bufferTrail();
                // 将字符串转为整数值
                char *endptr;
                int64_t value = strtoll(buffer, &endptr, 10);
                tokens.push_back(Token::makeIntLiteral(value, startPos, endPos()));
            }
        }
    }

public:
    std::istream *input = nullptr;
    /// 当前行号
    size_t lineNo = 1;
    /// 当前列号
    size_t columnNo = 0;
    /// 字符缓冲区
    char buffer[MAX_STR_LENGTH + 2];
    /// 当前缓冲区位置
    size_t bufferPos = 0;
    /// token匹配的起始位置
    Pos startPos;

    Pos endPos() {
        return Pos(lineNo, columnNo);
    }

    StringTable &idTable;
    StringTable &strTable;

    Logger logger;

    /// 向buffer末尾添加\0
    /// \return 成功返回true
    bool bufferTrail() {
        if (isBufferOverflow()) {
            return false;
        }

        buffer[bufferPos] = '\0';
        buffer[bufferPos + 1] = '\0';
        return true;
    }

    bool isBufferOverflow() {
        return bufferPos >= MAX_STR_LENGTH;
    }

    /// 获取一个字符
    /// success标志是否成功
    /// note: 调用此函数之前需要确保buffer未满
    char get(bool &success, bool addToBuffer = true) {
        if (isBufferOverflow()) {
            logger.error(Error::tokenTooLong(startPos, endPos()));
            success = false;
            return EOF;
        }
        char ret = input->get();
        if (addToBuffer) {
            buffer[bufferPos] = ret;
            bufferPos++;
        }
        columnNo++;
        // newline
        if (ret == '\n') {
            newline();
        }
        success = true;
        return ret;
    }

    /// 向前看一个字符而不从字符流中取出
    char peek() {
        return input->peek();
    }

    /// 回退一个字符
    void unget(bool rmBuffer = true) {
        assert(bufferPos - 1 >= 0);
        columnNo--;
        if (rmBuffer) {
            bufferPos -= 1;
            buffer[bufferPos] = '\0';
        }
        input->unget();
    }

    /// 退回n个字符
    void ungetN(size_t n) {
        assert(bufferPos - n >= 0);
        bufferPos -= n;
        for (size_t i = 0; i < n; i++) {
            unget();
        }
    }

    /// 清空缓冲区(将bufferPos置为0)
    void clearBuffer() {
        bufferPos = 0;
        buffer[0] = '\0';
        buffer[1] = '\0';
    }

    void newline() {
        lineNo++;
        columnNo = 0;
    }

    void skipBlank() {
        bool success;
        char c = get(success, false);
        while (isblank(c)) {
            if (c == '\n') {
                newline();
            }
            c = get(success, false);
        }
        unget(false);
    }

    bool isSingleSymbol(char c) {
        switch (c) {
            case '+':
            case '/':
            case '-':
            case '*':
            case '=':
            case '<':
            case '.':
            case '~':
            case ',':
            case ';':
            case ':':
            case '(':
            case ')':
            case '@':
            case '{':
            case '}':
                return true;
            default:
                return false;
        }
    }
};


#endif //COOL_SCANNER_H
