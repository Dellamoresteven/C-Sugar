#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "../../extensions/parser.h"

#define green "\u001b[32m"
#define red "\u001b[31m"
#define normal "\033[0m"

namespace tests{
    bool static compareFiles(const std::string& p1, const std::string& p2) {
        std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
        std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

        if (f1.fail() || f2.fail()) {
            return false; //file problem
        }

        if (f1.tellg() != f2.tellg()) {
            return false; //size mismatch
        }

        //seek back to beginning and use std::equal to compare contents
        f1.seekg(0, std::ifstream::beg);
        f2.seekg(0, std::ifstream::beg);
        return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                            std::istreambuf_iterator<char>(),
                            std::istreambuf_iterator<char>(f2.rdbuf()));
    }
    
    void static runTests( std::string testName ) {
        std::string systemCall = "./cpe test/unit/input/" + testName + ".cpe -t";
        system(systemCall.c_str());
        if ( ::tests::compareFiles("test/unit/input/" + testName + ".cpp", "test/unit/expected/" + testName + ".cpp") ) {
            std::cout << green << testName << " Passed" << normal << std::endl;
            std::string rmStr = "rm test/unit/input/" + testName + ".cpp";
            system(rmStr.c_str());
        } else {
            std::cout << red << testName << " Failed" << normal << std::endl;
        }
    }

    class vectorTests {
        public:
            static void runTests() {
                vectorSimple1();
                vectorSimple2();
                vectorPush1();
                vectorPush2();
                vectorPush3();
            }

            static void vectorSimple1() {
                ::tests::runTests("vectorSimple1");
            }

            static void vectorSimple2() {
                ::tests::runTests("vectorSimple2");
            }

            static void vectorPush1() {
                ::tests::runTests("vectorPush1");
            }

            static void vectorPush2() {
                ::tests::runTests("vectorPush2");
            }

            static void vectorPush3() {
                ::tests::runTests("vectorPush3");
            }
    };

    class varTests {
        public:
            static void runTests() {
                varSimple1();
            }
            static void varSimple1() {
                ::tests::runTests("varSimple1");
            }
    };

    class functionTests {
        public:
            static void runTests() {
                functionSimple1();
            }
            static void functionSimple1() {
                ::tests::runTests("functions1");
            }
    };

    class printTests {
        public:
            static void runTests() {
                printSimple1();
            }
            static void printSimple1() {
                ::tests::runTests("print");
            }
    };
}