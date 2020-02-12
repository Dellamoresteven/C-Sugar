#include "../parser.h"

void parser::ReplacerObject::replaceVar( token::TokenObject * newtoken ) {
    std::string rhs = token->getUntilToken( "=", ";" );
    auto indenter = [&](auto tok, auto newtok){
        for( int i = 0; i < tok->checkIndentLength(); i ++ ){ 
            newtok->push(" ");
        }
    };
    // std::cout << "typeid(i).name() ->: " << typeid(rhs).name() << std::endl;
    // std::cout << "RHS: " << rhs << std::endl;
    std::string name = token->peekNoSpace();
    // std::cout << "name:" << name << ":\n";
    if(name == "*" || name == "&" || name == "**" || name == "&&"){
        name = token->peekNoSpace1();
    }
    if(name == "*" || name == "&" || name == "**" || name == "&&"){
        name = token->peekNoSpace2();
    }
    // std::cout << "name:" << name << ":\n";
    newtoken->push("// " + name + " @TODO\n");
    indenter(token, newtoken);
    char* p;
    strtol(rhs.c_str(), &p, 10); // Checks to see if its an int
    if (!*p) {
        newtoken->push("int");
        return;
    }
    newtoken->push("auto");
}