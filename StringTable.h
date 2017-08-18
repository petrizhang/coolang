//===---- StringTable.h -  ---*- C++ -*-===//
//
//              Created by zeta on 17-7-29.
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

#ifndef COOL_STRINGTABLE_H
#define COOL_STRINGTABLE_H

#include <map>
#include <iostream>
#include <cstring>

class Entry {
protected:
    char *str = nullptr;     /// the string
    size_t len = 0;    /// the length of the string (without trailing \0)
public:
    Entry(const char *str, size_t len);

    bool equalString(const char *str) const;

    bool equalString(const char *str, size_t len) const;

    std::ostream &print(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &s, const Entry &sym);

    /// Return the str and len components of the Entry.
    char *getString() const;

    size_t getLength() const;
};

struct StrCmp {
    bool operator()(const char *lhs, const char *rhs) const {
        return strcmp(lhs, rhs) < 0;
    }
};

class StringTable {
public:
    const Entry *addString(const char *str, size_t length);

    const Entry *addString(const char *str);

    bool contains(const char *str);

private:
    /// 数据区
    std::map<const char *, const Entry *, StrCmp> data;
};


#endif //COOL_STRINGTABLE_H
