#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include "./unit/var.cpp"
#include "unit/vector.cpp"

// #define blue 
#define green "\u001b[32m"
#define normal "\033[0m"

int main(int argc, char * argv[]){ 
    std::cout << "Running Tests\n";
    if(argc > 1) {
        std::string argv1(argv[1]);
        if(argv1 == "all") {
            tests::var::runTests();
            tests::vector::runTests();
        } else if(argv1 == "var") {
            tests::var::runTests();
        } else if(argv1 == "vector") {
            tests::vector::runTests();
        }
    }

}