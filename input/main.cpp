// author: Steven Dellamore
// date: 2020-2-12
// version: 1.0.0

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <list>
#include <sys/stat.h>
#include <unistd.h>
#include <functional>
#include <map>
#include <sstream>
#include <iterator>

class Object {

};

int main() {
    // vecInt @TODO
    auto vecInt = std::vector< int >(); // This vector @TODO 
    // vecStr @TODO
    auto vecStr = std::vector< std::string >(); // This vector @TODO
    vecInt.push_back(5);
    vecInt.push_back(6);
    vecInt.push_back(7);
    vecInt.push_back(8);
    vecInt.push_back(9);
    vecStr.push_back("Steve");
    vecStr.push_back("john");
    // obj @TODO
    auto * obj = new Object();

    // Printing out the entire vecInt vector with delim: ", "
    for (auto i = vecInt.begin(); i != vecInt.end(); ++i)
    {
        std::cout << *i << ", ";
    }
    std::cout << "\n";

    std::cout << "vecIntpush(5): " << vecInt.at(0) << "\n";
    std::cout << "vecStr(0): " << vecStr.at(0) << "\n";
    std::cout << "vecStr(1): " << vecStr.at(1) << "\n";
}