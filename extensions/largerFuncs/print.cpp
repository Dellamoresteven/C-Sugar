#include "../parser.h"

void parser::ReplacerObject::print( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( "(", ";" );
    // std::cout << "inside: " << inside << std::endl;
    int quoteStatus = 0;
    std::string tok = "";
    newtoken->push("std::cout << ");
    for(int i = 0; i < inside.length()-1; i++){
        if( inside.at(i) == '\"' ) { // found quote
            quoteStatus++;
        } 
        if( quoteStatus == 2 ){ // leaving quote
            quoteStatus = 0;
        }  
        if( quoteStatus == 1 ){ //in quote
            tok += inside.at(i);
        } else { // not in quote
            if( inside.at(i) == '+' ) {
                newtoken->push(tok);
                newtoken->push("<<");
                tok = "";
            } else {
                tok += inside.at(i);
            }
        }
    }
    if(tok != "") {
        newtoken->push(tok);
    }
    newtoken->push(";");
    token->readUntilDelim( "(", ";" ); 
}