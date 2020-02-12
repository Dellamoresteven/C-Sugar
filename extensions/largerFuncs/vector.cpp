#include "../parser.h"

void parser::ReplacerObject::vector( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( ";" );
    newtoken->push("std::vector<");
    newtoken->push(inside);
    newtoken->push(" >(); // This vector @TODO");
    token->readUntilDelim( " ", ";" );
}