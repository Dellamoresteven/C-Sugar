#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>

#include "unit/tests.cpp"


int main(int argc, char * argv[]){ 
    std::cout << "Running Tests\n";
    // system("make");
    if(argc > 1) {
        std::string argv1(argv[1]);
        if(argv1 == "all") {
            tests::varTests::runTests();
            tests::vectorTests::runTests();
            tests::functionTests::runTests();
            tests::printTests::runTests();
        } else if(argv1 == "var") {
            tests::varTests::runTests();
        } else if(argv1 == "vector") {
            tests::vectorTests::runTests();
        }
    }

}