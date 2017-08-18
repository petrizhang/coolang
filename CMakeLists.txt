cmake_minimum_required(VERSION 3.7)
project(cool)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        Token.cpp
        Token.h
        StringTable.cpp
        StringTable.h
        Driver.cpp
        Driver.h
        Scanner.cpp
        Scanner.h Logger.cpp Logger.h Error.cpp Error.h)

set(TEST_FILES test.cpp
        #test_stringtable.cpp
        StringTable.cpp
        test_token.cpp
        Token.cpp Driver.cpp Driver.h Scanner.cpp Scanner.h Logger.cpp Logger.h Error.cpp Error.h)

add_executable(cool ${SOURCE_FILES} Tree.cpp Tree.h)
add_executable(alltest ${TEST_FILES})
target_link_libraries(alltest
         gtest
         pthread)