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
    class vectorTests {
        public:
            static void runTests() {
                vectorSimple1();
                vectorSimple2();
            }

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

            static void vectorSimple1() {
                std::string testName = "vectorSimple1";
                std::string systemCall = "./run test/unit/input/" + testName + ".cpe -s";
                system(systemCall.c_str());
                if ( compareFiles("test/unit/input/" + testName + ".cpp", "test/unit/expected/" + testName + ".cpp") ) {
                    std::cout << green << testName << " Passed" << normal << std::endl;
                    std::string rmStr = "rm test/unit/input/" + testName + ".cpp";
                    system(rmStr.c_str());
                } else {
                    std::cout << red << testName << " Failed" << normal << std::endl;
                }
            }

            static void vectorSimple2() {
                std::string testName = "vectorSimple2";
                std::string systemCall = "./run test/unit/input/" + testName + ".cpe -s";
                system(systemCall.c_str());
                if ( compareFiles("test/unit/input/" + testName + ".cpp", "test/unit/expected/" + testName + ".cpp") ) {
                    std::cout << green << testName << " Passed" << normal << std::endl;
                    std::string rmStr = "rm test/unit/input/" + testName + ".cpp";
                    system(rmStr.c_str());
                } else {
                    std::cout << red << testName << " Failed" << normal << std::endl;
                }
            }
    };

    class varTests {
        public:
            static void runTests() {
                varSimple1();
            }
            static void varSimple1() {
                // token::TokenObject * tok = new token::TokenObject();
                // (void)tok;
                std::string testString = "var x;";
            }
    };
}