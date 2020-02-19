#include "../../parser.h"
#include <queue> 

/*
def function() {

}
----
auto function () {

}

#################
def int function() {

}
----
int function() {

}

#################
def function(any1 t) {

}
---- 
template<typename T>
auto function(T t) {

}
*/

/*
op = optional
rt = return type

def + op(rt) + name + ( + [op Params] + )
*/


auto parseFunctionDef( std::string inside ) {
    std::string ret;
    token::TokenObject * newToken = new token::TokenObject();
    newToken->delim.clear();
    newToken->delim.push_back("(");
    newToken->delim.push_back(",");
    newToken->delim.push_back(")");
    newToken->delim.push_back(" ");
    newToken->push(inside);
    return newToken; 
}



void parser::ReplacerObject::functionDef( token::TokenObject * newtoken ) {
    std::string inside = token->getUntilToken( "{" );
    // std::cout << "\ninsimde: " << inside << std::endl;
    std::string fullParam = "", tok = "";
    token::TokenObject * insideToken = parseFunctionDef( inside );
    FunDef fundef; // fill this in with all the types
    while( insideToken->hasNext() ) {
        tok = insideToken->next();
        
        if(tok == " " || tok == "\n" || tok == "(" ) {

        } else if( insideToken->peekNoSpace() != "(" && fundef.returnType == "" ) {
            fundef.returnType = tok;
        } else if( insideToken->peekNoSpace() == "(" && fundef.functionName == "" ) {
            /* Checks to see if the next tok is a '('. Then make sure we have not
               already grabbed the name of the function */
            if(fundef.returnType == "") {
                fundef.returnType = "auto";
            }
            fundef.functionName = tok;
        } else {
            /* After ret and funcName */
            if( insideToken->peekNoSpace() == "," || insideToken->peekNoSpace() == ")" ) {
                if( fullParam == "" ) {
                    fullParam = "any" + to_string( fundef.numTemplateVars++ );
                    fundef.isTemplate = true;
                } else if( fullParam == "any1" || fullParam == "any2" || fullParam == "any3" || fullParam == "any4" ) {
                    fundef.isTemplate = true;
                }
                fundef.params[tok] = fullParam;
                fullParam = "";
            } else if( tok == "," || tok == ")" ) {
                fullParam = "";
            } else {
                fullParam += tok;
            }
        }
    }
    // fundef.print();
    functionList.insert(pair <std::string, FunDef> (fundef.functionName, fundef));
    token->readUntilDelim( "{" );
    writeFunctionDef( fundef, newtoken );
    delete insideToken;
}


void parser::ReplacerObject::writeFunctionDef( FunDef f, token::TokenObject * newtoken ) {
    int numOfTemp = 0;
    for (auto it = f.params.begin(); it!=f.params.end(); ++it) {
        if( (*it).second.length() == 4 && (*it).second.substr(0,3) == "any") {
            std::cout << stoi( (*it).second.substr( 3, 4 ) ) << " I\n";
            if( numOfTemp < stoi( (*it).second.substr( 3, 4 ) ) ) {
                numOfTemp = stoi( (*it).second.substr( 3, 4 ) );
            }
        }
    }
    numOfTemp++;
    if( f.isTemplate ) {
        if( numOfTemp == 1 ) newtoken->push( "template < typename T >\n" );
        if( numOfTemp == 2 ) newtoken->push( "template < typename T, typename U >\n" );
        if( numOfTemp == 3 ) newtoken->push( "template < typename T, typename U, typename G >\n" );
        if( numOfTemp == 4 ) newtoken->push( "template < typename T, typename U, typename G >\n" );
        if( numOfTemp == 5 ) newtoken->push( "template < typename T, typename U, typename G, typename H >\n" );
    }
    newtoken->push( f.returnType + " " + f.functionName + "( ");
    std::string argsStr = "";
    for (auto it = f.params.begin(); it!=f.params.end(); ++it) {
        if( (*it).second == "any1" ) argsStr += ( "T " + (*it).first + ", ");
        else if( (*it).second == "any2" ) argsStr += ( "U " + (*it).first + ", ");
        else if( (*it).second == "any3" ) argsStr += ( "G " + (*it).first + ", ");
        else if( (*it).second == "any4" ) argsStr += ( "H " + (*it).first + ", ");
        else argsStr += ( (*it).second + " " + (*it).first + ", ");
    }
    newtoken->push( argsStr.substr( 0, argsStr.length() - 2 ) );
    newtoken->push(" ) {");
}