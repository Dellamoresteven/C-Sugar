#include "../parser.h"

void parser::ReplacerObject::push( token::TokenObject * newtoken ) {
    auto indenter = [&](auto tok, auto newtok){
        for( int i = 0; i < tok->checkIndentLength(); i ++ ){ 
            newtok->push(" ");
        }
    };
    newtoken->push("push_back");
}