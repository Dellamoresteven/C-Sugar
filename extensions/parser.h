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

#include "token.h"

using namespace std;

namespace parser {
    class ParserObject {
        private: 
            /**
             * VARIABLES
             */
            std::ifstream *ffile; // file object we are reading from
            const std::vector<std::string> delim{ " ", "(", ")", "{", "}", "\n", ";", "@", "#" }; // Delim list
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
        public:
            /**
             * FUNCTIONS
             */
            ReplacerObject() = delete;

            virtual ~ReplacerObject() = default;

            ReplacerObject( token::TokenObject * token, std::string filepath ) 
            : token(token),
              filepath(filepath){}

            void replaceTokenList();
            void replaceIncludes( token::TokenObject * );
            void replaceVar( token::TokenObject * );
            void print( token::TokenObject * ); 
            void printv( token::TokenObject * );        // print vector
            void vector( token::TokenObject * );
            void push( token::TokenObject * );
            void headerComment( token::TokenObject * );
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