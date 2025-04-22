//
// Created by 30884 on 25-4-21.
//

#ifndef RED_BLACK_TREE_MAP_H
#define RED_BLACK_TREE_MAP_H
#include "RedBlackTree.h"

class Map {
private:
    RedBlackTree Storage;
public:
    Map();
    ~Map();

    void insert(uint64_t k,std::string &value);
    bool remove(uint64_t t);

    bool isEmpty()const;
    void clear();
    std::string operator[](uint64_t k);

};


#endif //RED_BLACK_TREE_MAP_H
