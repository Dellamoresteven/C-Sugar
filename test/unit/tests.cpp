#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>

#include "../../extensions/parser.h"

namespace tests{
    class vectorTests {
        public:
            static void runTests() {
                vectorSimple1();
            }
            static void vectorSimple1() {
                token::TokenObject * token = new token::TokenObject();
                std::string testString = "var x;";
                token->push( testString );
                
                parser::ReplacerObject * replacerObject = new parser::ReplacerObject( token );

                token::TokenObject * newToken = replacerObject->replaceTokenList();

                parser::FileWriterObject * writer = new parser::FileWriterObject( newToken, "./test/unit/output/vectorSimple1.cpe" );
                writer->write();
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