#include <iostream>
#include "map.h"

using namespace std;

int main() {
    Map m;
    std::string s = "sss";
    for(int i=0;i<200;++i){
        m.insert(i,s);
    }
    m.traverse();
    std::cout << m.mapSize()<<endl;
}
