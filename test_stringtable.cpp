//===---- test_stringtable.cpp -  ---*- C++ -*-===//
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

#include <iostream>

#include "StringTable.h"
#include "gtest/gtest.h"

TEST(scanner, stringtable) {
    StringTable table;
    const char *a[] = {"zhang", "peng", "cheng", "zdf", "sdf"};
    for (int i = 0; i < 5000; i++) {
        table.addString(a[0]);
    }
    bool b = true;
    for (int i = 0; i < 5000000; i++) {
        b &= table.contains(a[0]);
    }
    EXPECT_TRUE(b);
}