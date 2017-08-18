//===---- StringTable.cpp -  ---*- C++ -*-===//
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

#include <cstring>

#include "StringTable.h"

Entry::Entry(const char *str, size_t len)
        : len(len) {
    // 多分配2字节
    this->str = new char[len + 2];
    strncpy(this->str, str, len);
    this->str[len] = '\0';
    this->str[len + 1] = '\0';
}

bool Entry::equalString(const char *str) const {
    return strcmp(this->str, str) == 0;
}

bool Entry::equalString(const char *str, size_t len) const {
    return (this->len == len) && (strncmp(this->str, str, len) == 0);
}

std::ostream &Entry::print(std::ostream &os) const {
    return os << "{" << str << ", " << len << ", " << "}\n";
}

std::ostream &operator<<(std::ostream &s, const Entry &sym) {
    return s << sym.getString();
}

char *Entry::getString() const {
    return str;
}

size_t Entry::getLength() const {
    return len;
}

const Entry *StringTable::addString(const char *str, size_t length) {
    // 已存在，直接返回
    auto it = data.find(str);
    if(it != data.end()) {
        return it->second;
    }

    // 不存在，插入一个
    const Entry *elem = new Entry(str, length);
    const char *index = elem->getString();
    // 插入数据
    data.insert(std::make_pair(index, elem));
    return elem;
}

const Entry *StringTable::addString(const char *str) {
    return this->addString(str, strlen(str));
}

/// parameter 'str' must end with '\0'
bool StringTable::contains(const char *str) {
    return data.find(str) != data.end();
}


