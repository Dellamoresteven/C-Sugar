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
                // std::cout << "tok: " << tok << " : " << "fullParam: " << fullParam << "\n";
                fundef.paramss.push( std::pair<std::string, std::string>( tok, fullParam ) );
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
    // fundef.print();
    token->readUntilDelim( "{" );
    writeFunctionDef( fundef, newtoken );
    delete insideToken;
}


void parser::ReplacerObject::writeFunctionDef( FunDef f, token::TokenObject * newtoken ) {
    int numOfTemp = 0;
    std::string templateString = "TUGHYKVMNACE";
    std::string argsStr = "";
    while( !f.paramss.empty() ){
        std::string name = f.paramss.front().first;
        std::string typ = f.paramss.front().second;
        if( typ.length() == 4 && typ.substr( 0, 3 ) == "any" ) {
            if( numOfTemp < stoi( typ.substr( 3, 4 ) ) ) {
                numOfTemp = stoi( typ.substr( 3, 4 ) );
            }
            argsStr += templateString.at( stoi( typ.substr( 3, 4 ) ) - 1 );
        } else {
            argsStr += typ;
        }
        argsStr += " ";
        argsStr += (name + ", ");
        f.paramss.pop();
    }
    if( f.isTemplate ) {
        std::string templatePrint = "template <";
        for( int i = 0; i < numOfTemp; i++ ) {
            templatePrint += "typename ";
            templatePrint += templateString.at( i );
            templatePrint += ", ";
        }
        templatePrint = templatePrint.substr( 0, templatePrint.length() - 2 );
        templatePrint += " >\n";
        newtoken->push( templatePrint );
    }
    newtoken->push( f.returnType + " " + f.functionName + "( ");
    
    newtoken->push( argsStr.substr( 0, argsStr.length() - 2 ) );
    newtoken->push(" ) {");
}