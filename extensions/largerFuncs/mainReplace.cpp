#include "../parser.h"


void parser::ReplacerObject::mainReplace( token::TokenObject * newtoken ) {
    std::cout << "MAIN\n";
    newtoken->push("int main(int argc, char* argv[]) ");
}