#include <iostream>
#include <fstream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <functional> 
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <queue>

#include "token.h"

using namespace std;


struct FunDef {
    std::string functionName                                 = "";    // functionName
    std::string returnType                                   = "";    // return type of the function
    std::queue< pair< std::string, std::string > > paramss;           // var pair<name, type>
    bool isTemplate                                          = false; // if the function is template
    int numTemplateVars                                      = 1;     // number of any's. i.e any1 any2 any3 

    void print() {
        std::cout << "rt: " << returnType << "\n";
        std::cout << "FunctionName: " << functionName << "\n";
        std::cout << "isTemplate: " << isTemplate << "\n";
        std::queue< pair< std::string, std::string > > copyParamss = paramss;
        while (!copyParamss.empty()) {
            std::cout << copyParamss.front().first << " " << copyParamss.front().second << "\n";
            copyParamss.pop();
        }
        std::cout << std::endl;
    }
};


namespace parser {
    class ParserObject {
        private: 
            /**
             * VARIABLES
             */
            std::ifstream *ffile; // file object we are reading from
            const std::vector<std::string> delim{ " ", "(", ")", "{", "}", "\n", ";", "@", "#", "=>" }; // Delim list
            const std::vector<std::string> keyWords{ "main" }; // keywords to look for
            token::TokenObject * token;
        public:
            /**
             * FUNCTIONS
             */
            ParserObject() = delete;
            virtual ~ParserObject() = default;
            ParserObject( token::TokenObject * token ) 
                : token( token ) {}
            void parseFile( std::ifstream& );
    };

    class ReplacerObject {
        private:
            /**
             * VARIABLES
             */
            std::vector< std::string > cppFileTokenList;
            token::TokenObject * token;
            std::string filepath;

            /**
             * parseByDelim - Takes in a string that you are trying to parse,
             *                and a list of delims.
             *
             * @param - string str:      String you want to parse
             * @param - Params... param: The delim list you want to parse with
             * 
             * @return - vector<string> of the split string
             *
             * @example - parseByDelim("This-Is-My-Example", "-");
             *            returns -> std::vector<std::string>("This","Is","My","Example")
             */
            template<typename ... Params>
            inline std::vector<std::string> parseByDelim(std::string str, Params... params) {
                std::vector<std::string> ret;
                std::string tok = "";
                // std::cout << "str=>:" << str << std::endl;
                for(int i = 0; i < str.length(); i++) {
                    for (auto x : { params... }) {
                        std::string f(x);
                        if(str.at(i) == f.at(0)){
                            ret.push_back( tok );
                            tok = "";
                        } else {
                            tok += str.at(i);
                        }
                    }
                }
                if(tok != ""){
                    ret.push_back( tok );
                }
                return ret;
            }

        public:
            multimap<std::string, FunDef> functionList; // function name, functionDef

            /**
             * FUNCTIONS
             */
            ReplacerObject() = delete;

            virtual ~ReplacerObject() = default;

            ReplacerObject( token::TokenObject * token ) 
            : token(token){}

            token::TokenObject* replaceTokenList();
            void replaceIncludes( token::TokenObject * );
            void replaceVar( token::TokenObject * );
            void print( token::TokenObject * ); 
            void printv( token::TokenObject * );        // print vector
            void println( token::TokenObject * );
            void vector( token::TokenObject * );
            void pushv( token::TokenObject * );
            void headerComment( token::TokenObject * );
            void functionDef( token::TokenObject * );
            void writeFunctionDef( FunDef, token::TokenObject * );
    };

    class FileWriterObject {
        private:
            /**
             * VARIABLES
             */
             token::TokenObject * token;
             std::string filepath;
        public:
            /**
             * FUNCTIONS
             */
            FileWriterObject() = delete;

            virtual ~FileWriterObject() = default;

            FileWriterObject( token::TokenObject * token, std::string filepath ) 
            : token( token ),
              filepath( filepath ){}
            
            inline void write() {
                std::filebuf outfile; // creating my outfile filebuffer
                std::string outfilename = filepath.substr( 0, filepath.rfind( '.' ) ) + ".cpp";
                outfile.open( outfilename, std::ios::out );
                std::ostream ostream(&outfile);
                while( token->hasNext() ){
                    ostream << token->next();
                }
                outfile.close(); // lets not lose memory! woo.
            }
        };

        class ConfigReaderObject {
        private:
            /**
             * VARIABLES
             */
             std::map< std::string, std::string > mapper;
             std::string filepath;
        public:
            /**
             * FUNCTIONS
             */
            ConfigReaderObject()
                : filepath( "config" ) {
                    readConfigFile();
                }

            virtual ~ConfigReaderObject() = default;

            void readConfigFile();

            std::string getConfig( std::string );
    };
}