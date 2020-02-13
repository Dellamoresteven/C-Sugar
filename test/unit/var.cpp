#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>

namespace tests{
    class var {
        public:
            static void runTests() {
                varSimple1();
            }
            static void varSimple1() {
                std::string testString = "var x;";
                std::cout << "HERERERE\n";
            }
    };
}