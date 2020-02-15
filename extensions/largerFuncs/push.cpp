#include "../parser.h"

void parser::ReplacerObject::push( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( "(", ";" );
    std::vector<std::string> insideVec = parseByDelim( inside.substr( 0, inside.length() - 1 ), "," );
    std::string varName = token->last2();
    
    auto indenter = [&](auto tok, auto newtok){
        for( int i = 0; i < tok->checkIndentLength(); i ++ ){ 
            newtok->push(" ");
        }
    };

    newtoken->push("push_back(");
    newtoken->push(insideVec.at(0));
    newtoken->push("); // pushing " + insideVec.at(0) + " onto " + varName + "\n");
    for( int i = 1; i < insideVec.size(); i++ ){
        indenter(token, newtoken);
        newtoken->push(varName + ".");
        newtoken->push("push_back(");
        newtoken->push(insideVec.at(i));
        newtoken->push("); // pushing " + insideVec.at(i) + " onto " + varName + "\n");
    }
    token->readUntilDelim( "(", ";" );
}