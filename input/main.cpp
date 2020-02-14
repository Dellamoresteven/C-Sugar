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

int main() {
    // x @TODO
    auto x = std::vector< int >(); // This vector @TODO
    x.push_back(5);
    x.push_back(6);
    x.push_back(7);
    x.push_back(8);
    // Printing out the entire x vector with delim: ", "
    for (auto i = x.begin(); i != x.end(); ++i)
    {
        std::cout << *i << ", ";
    }
    std::cout << "\n";
}