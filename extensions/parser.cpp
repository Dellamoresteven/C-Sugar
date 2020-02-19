#include "parser.h"
#include <iostream>
#include <string>

void parser::ParserObject::parseFile(std::ifstream& ffstream) {
    ffile = &ffstream; // Setting ffile to the fstream passed in
    std::string line = "";
    char c;
    while( ffile->get(c) ){ // Go until file is done
        if(c == '\n'){
            line += '\n';
            token->push(line);
            line = "";
        } else {
            line += c;
        }
    }
    if( line != "" ){
        token->push(line);
    }
    /* Print the token vector out */
    std::cout << "oldTokenList: " << magenta;
    token->printVector();
    std::cout << normal;
}

