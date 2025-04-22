#include <iostream>
#include "map.h"

using namespace std;

int main() {
    Map m;
    std::string s = "sss";
    for(int i=0;i<20;++i){
        m.insert(i,s);
    }
    for(int i=0;i<10;++i){
        m.remove(i);
    }

}
