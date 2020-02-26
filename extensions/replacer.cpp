#include "parser.h"

token::TokenObject* parser::ReplacerObject::replaceTokenList() {
    token::TokenObject * newToken = new token::TokenObject();
    bool isComment = false;
    newToken->push("/* This file is auto generated by C-Sugar @author Steven Dellamore \nURL = https://github.com/Dellamoresteven/C-Sugar */\n\n");
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
        else if( (tok == "m" && (token->peekNoSpace() == "{") ) ) {
            /* The "#inc e" */
            parser::ReplacerObject::mainReplace( newToken );
        }
        else if( (tok == "#") && (token->peekNoSpace() == "inc") && (token->peekNoSpace1() == "e") ) {
            /* The "#inc e" */
            parser::ReplacerObject::replaceIncludes( newToken );
        }
        else if( (tok == "print") && (token->peekNoSpace() == "(")) {
            /* The "print(...);" to std::cout << ...; */
            parser::ReplacerObject::print( newToken );
        }
        else if( (tok == "println") && (token->peekNoSpace() == "(")) {
            /* The "print(...);" to std::cout << ...; */
            parser::ReplacerObject::println( newToken );
        }
        else if( (tok == "var") ) {
            /* The "#inc e" */
            parser::ReplacerObject::replaceVar( newToken );
        }
        else if( (tok == "vector") && (token->peekNoSpace() != "<")) {
            /* The "#inc e" */
            parser::ReplacerObject::vector( newToken );
        }
        else if( (tok == "pushv") && (token->peekNoSpace() == "(") && token->lastNoSpace() == "." ) {
            /* The ".push(" */
            parser::ReplacerObject::pushv( newToken );
        }
        else if( (tok == "printv") && (token->peekNoSpace() == "(") ) {
            /* The ".push(" */
            parser::ReplacerObject::printv( newToken );
        }
        else if( (tok == "def") ) {
            /* The "def" */
            parser::ReplacerObject::functionDef( newToken );
        }
        else {
            /* push if there is no sugar to add */
            newToken->push(tok); 
        }
    }

    // parser::FileWriterObject * writer = new parser::FileWriterObject( newToken, filepath );
    // writer->write();
    // std::cout << "\nnewTokenList: " << magenta;
    // newToken->printVector();
    // std::cout << normal <<"\nFunctionList: \n";
    // for (auto itr = functionList.begin(); itr != functionList.end(); ++itr) { 
    //     cout  << green << itr->first << normal <<"\n";
    // } 
    // cout << endl; 
    return newToken;
}