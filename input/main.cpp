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

int main(){ 
    // x @TODO
    auto x = std::vector< int >(); // This vector @TODO
    x.push_back(1); // pushing 1 onto x
    x.push_back(2); // pushing 2 onto x
    x.push_back(3); // pushing 3 onto x
    x.push_back(4); // pushing 4 onto x
    x.push_back(5); // pushing 5 onto x

    // Printing out the entire x vector with delim: " "
    for (auto i = x.begin(); i != x.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
}