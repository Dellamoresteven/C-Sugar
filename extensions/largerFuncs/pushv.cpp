#include "../parser.h"

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void parser::ReplacerObject::pushv( token::TokenObject * newtoken ) {
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
    if( insideVec.size() > 1 ) {
        newtoken->push("); // pushing " + insideVec.at(0) + " onto " + varName + "\n");
    } else {
        newtoken->push("); // pushing " + insideVec.at(0) + " onto " + varName);
    }
    
    for( int i = 1; i < insideVec.size(); i++ ){
        indenter(token, newtoken);
        newtoken->push(varName + ".");
        newtoken->push("push_back(");
        std::string insideVectok = insideVec.at(i);
        ltrim(insideVectok);
        rtrim(insideVectok);
        newtoken->push( insideVectok );
        if( i+1 == insideVec.size() ) {
            newtoken->push("); // pushing " + insideVectok + " onto " + varName);
        } else {
            newtoken->push("); // pushing " + insideVectok + " onto " + varName + "\n");
        }
        
    }
    token->readUntilDelim( "(", ";" );
}