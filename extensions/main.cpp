#include <iostream>
#include <fstream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <time.h>

#include "parser.h"


int main(int argc, char* agrv[]) {
    clock_t begin = clock();
    // Create my file object
    std::ifstream ffile;

    // Usage lambda
    auto usage = [](){ std::cout << "Usage: gee [file.ce] -output [exe]" << std::endl; };

    // Creating my token object
    token::TokenObject * token = new token::TokenObject( );

    // Creating my parsing object
    parser::ParserObject * parser = new parser::ParserObject( token );

    // Creating my replacing object
    parser::ReplacerObject * replacer = new parser::ReplacerObject( token );

    if( argc == 1 ){
        usage();
    } else if( argc == 2 ) {
        /**
        * Fastest way to check if a file exists. 
        */ 
        struct stat buffer; 
        if ( stat( agrv[1], &buffer ) == 0 ) { 
            // Open the file
            ffile.open( agrv[1] );
            // Start the parser
            parser->parseFile( ffile );
            // Start replacing syntex sugar
            token::TokenObject * newToken = replacer->replaceTokenList();
            std::cout << "\nnewTokenList: " << magenta;
            newToken->printVector();
            std::cout << normal <<"\nFunctionList: \n";
            for (auto itr = replacer->functionList.begin(); itr != replacer->functionList.end(); ++itr) { 
                cout  << green << itr->first << normal <<"\n";
            } 
            cout << endl;

            parser::FileWriterObject * writer = new parser::FileWriterObject( newToken, agrv[1] );
            writer->write();
        } else {
            // call specific error here
        }
    } else if( argc == 3 ) {

    } else if( argc == 4 ) {
        
    } else if( argc == 5 ) {
        
    } else { 
        usage();
    }
    ffile.close();
    clock_t end = clock();
    double time_spent = ( double )( end - begin ) / CLOCKS_PER_SEC;
    std::cout << "This took " << time_spent << " seconds.\n";

    std::cout << "\n\nCompiling\n";
    std::string bash(agrv[1]);
    std::string bashSub = bash.substr( 0, bash.rfind( '.' ) ) + ".cpp";
    bashSub = "g++ --std=c++2a -o " + bash.substr( 0, bash.rfind( '/' ) + 1 ) + "run " + bashSub;
    std::cout << bashSub;
    std::system(bashSub.c_str());
    std::cout << "\nRunning\n";
    bashSub = bash.substr( 0, bash.rfind( '/' ) + 1 ) + "run";
    bashSub = "./" + bashSub;
    std::system(bashSub.c_str());
}