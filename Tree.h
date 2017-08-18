//===---- Tree.h -  ---*- C++ -*-===//
//
//              Created by zeta on 17-8-18.
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

#ifndef COOL_TREE_H
#define COOL_TREE_H

#include <iostream>

class Tree_node {
protected:
    int line_number;            // stash the line number when node is made
public:
    Tree_node();
    virtual Tree_node *copy() = 0;
    virtual ~Tree_node() { }
    virtual void dump(std::ostream& stream, int n) = 0;
    int get_line_number();
    Tree_node *set(Tree_node *);
};

class Tree {

};


#endif //COOL_TREE_H
