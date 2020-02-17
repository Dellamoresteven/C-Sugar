#include "../../parser.h"
#include <queue> 

/*
def function() {

}
----
auto function () {

}

#################
def int function() {

}
----
int function() {

}

#################
def function(any1 t) {

}
---- 
template<typename T>
auto function(T t) {

}
*/

/*
op = optional
rt = return type

def + op(rt) + name + ( + [op Params] + )
*/

auto parseFunctionDef( std::string inside ) {
    std::string ret;
    token::TokenObject * newToken = new token::TokenObject();
    newToken->delim.clear();
    newToken->delim.push_back("(");
    newToken->delim.push_back(",");
    newToken->delim.push_back(")");
    newToken->delim.push_back(" ");
    newToken->push(inside);
    return newToken; 
}

void parser::ReplacerObject::functionDef( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( "{" );
    std::cout << "inside: " << inside << std::endl;
    std::string rt, name;
    token::TokenObject * insideToken = parseFunctionDef( inside );
    insideToken->printVector();


    token->readUntilDelim( "{" );
}