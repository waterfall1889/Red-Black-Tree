//
// Created by 30884 on 25-4-21.
//

#include "map.h"

Map::Map() {
    this->Storage.clear();
}

Map::~Map() {
    this->Storage.clear();
}

void Map::insert(uint64_t k, std::string &value) {
    this->Storage.insertNode(k,value);
}

bool Map::remove(uint64_t t) {
    return Storage.deleteNode(t);
}

bool Map::isEmpty() const {
    return (this->Storage.isEmpty());
}

void Map::clear() {
    this->Storage.clear();
}

std::string Map::operator[](uint64_t k) {
    // 查找键值
    const std::string& s = Storage.searchKey(k);

    // 如果找不到该键
    if (s.empty()) {
        return {};
    }

    // 返回副本而不是引用
    return s;
}


