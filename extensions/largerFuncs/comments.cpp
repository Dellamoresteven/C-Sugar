#include "../parser.h"

void parser::ReplacerObject::headerComment( token::TokenObject * newtoken ) {
    parser::ConfigReaderObject * configFile = new parser::ConfigReaderObject();
    token::TokenObject * tokenReplace = new token::TokenObject();
    std::string replace = configFile->getConfig("header");
    tokenReplace->push(replace);
    tokenReplace->delim.clear();
    tokenReplace->delim.push_back(" ");
    while( tokenReplace->hasNext() ) {
        std::string tok = tokenReplace->next();
        if(tok == "^date"){
            newtoken->push("date: ");
            std::time_t t = std::time(0);   // get time now
            std::tm* now = std::localtime(&t);
            newtoken->push(to_string(now->tm_year + 1900));
            newtoken->push("-");
            newtoken->push(to_string((now->tm_mon + 1)));
            newtoken->push("-");
            newtoken->push(to_string(now->tm_mday));
        } else {
            newtoken->push(tok);
        }
    }
    token->skip( 1 );
    delete configFile;
    delete tokenReplace;
}