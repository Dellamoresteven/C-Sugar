#include "parser.h"

void parser::ReplacerObject::replaceTokenList() {
    token::TokenObject * newToken = new token::TokenObject();
    bool isComment = false;
    while( token->hasNext() ) {
        std::string tok = token->next();
        // std::cout << "TOK: " << tok << std::endl;

        if(tok == " " || tok == "\n"){
            if(tok == "\n") isComment = false;
            newToken->push(tok);
        } 
        else if( (isComment) || tok == "//" ) {
            isComment = true;
            newToken->push(tok);
        }
        else if( (tok == "@" && (token->peekNoSpace() == "header") ) ) {
            /* The "#inc e" */
            parser::ReplacerObject::headerComment( newToken );
        }
        else if( (tok == "#") && (token->peekNoSpace() == "inc") && (token->peekNoSpace1() == "e") ) {
            /* The "#inc e" */
            parser::ReplacerObject::replaceIncludes( newToken );
        }
        else if( (tok == "print") && (token->peekNoSpace() == "(")) {
            /* The "print(...);" to std::cout << ...; */
            parser::ReplacerObject::print( newToken );
        }
        else if( (tok == "var") ) {
            /* The "#inc e" */
            parser::ReplacerObject::replaceVar( newToken );
        }
        else if( (tok == "vector") && (token->peekNoSpace() != "<")) {
            /* The "#inc e" */
            parser::ReplacerObject::vector( newToken );
        }
        else if( (tok == "push") && (token->peekNoSpace() == "(") && token->lastNoSpace() == "." ) {
            /* The ".push(" */
            parser::ReplacerObject::push( newToken );
        }
        else if( (tok == "printv") && (token->peekNoSpace() == "(") ) {
            /* The ".push(" */
            parser::ReplacerObject::printv( newToken );
        }
        else {
            /* push if there is no sugar to add */
            newToken->push(tok); 
        }
    }

    parser::FileWriterObject * writer = new parser::FileWriterObject( newToken, filepath );
    writer->write();
    std::cout << "newTokenList: ";
    newToken->printVector();
    delete newToken;
}