#include "../parser.h"

void parser::ReplacerObject::printv( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( "(", ")" );
    std::string vecName = inside.substr(0, inside.find(","));
    std::string rest = inside.substr(inside.find(","));
    std::string delim = "";
    bool first = true;
    for(int i = 0; i < rest.length(); i++){
        if(rest.at(i) == '\"'){
            first = !first;
        } else if(!first){
            delim += rest.at(i);
        }
    }
    auto indenter = [&](auto tok, auto newtok){
        for( int i = 0; i < tok->checkIndentLength(); i ++ ){ 
            newtok->push(" ");
        }
    };
    newtoken->push("// Printing out the entire " + vecName + " vector with delim: \"" + delim + "\"\n");
    // std::cout << "INDENT LENGTH: " + to_string(token->checkIndentLength()) << std::endl;
    indenter(token, newtoken);
    newtoken->push("for (auto i = " + vecName + ".begin(); i != " + vecName + ".end(); ++i)\n");
    indenter(token, newtoken);
    newtoken->push("{\n");
    indenter(token, newtoken);
    indenter(token, newtoken);
    newtoken->push("std::cout << *i << \"" + delim + "\";\n");
    indenter(token, newtoken);
    newtoken->push("}");
    // std::cout << "inside: " << inside << std::endl;

    token->readUntilDelim( "(", ";" );
}