#include <iostream>
#include <fstream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <functional> 
#include <algorithm>


/************
void push(std::string) - pushes a string onto the tokenlist
std::string peek, peek1, peek2 - looks at tokens ahead
std::string last, last1, last2 - looks at tokens behind
std::string peekNoSpace, peekNoSpace1, peekNoSpace2 - looks at tokens ahead that are not a space or a newline token
*************/

namespace token {
    class TokenObject {
        private:
            std::vector<std::string> tokenList;
            int index;

        public:
            // default Delim list. This can be changed if need be. see @print
            std::vector<std::string> delim{ " ", "(", ")", "{", "}", "\n", ";", "@", "#", "." };
             
            TokenObject() 
                : index(0){}

            virtual ~TokenObject() = default;

            inline void push( std::string strToken ) {
                std::string tok = "";
                for( int i = 0; i < strToken.length(); i++ ) {
                    std::string cStr( 1, strToken.at(i) );
                    // std::cout << "tok: " << tok << std::endl;
                    // std::cout << "cStr: " << cStr << std::endl;
                    if(std::find(delim.begin(), delim.end(), cStr) != delim.end()) {
                        if( tok != "" ) {
                            // std::cout << "tok: " << tok << std::endl;
                            tokenList.push_back( tok );
                            tok = "";
                        }
                        if( cStr != "" ) {
                            // std::cout << "cStr: " << cStr << std::endl;
                            tokenList.push_back( cStr );
                        }
                    } else {
                        tok += strToken.at(i);
                    }
                }
                if( tok != "" ){
                    tokenList.push_back( tok );
                }
                return;
            }

            inline void skip( int skipAmount ) { 
                if(index + skipAmount < tokenList.size()){ index += skipAmount; } 
                else index = tokenList.size();
            }

            inline std::string next( ) { return tokenList.at( index++ ); }

            inline std::string peek( ) { return tokenList.at( index + 1 ); }

            inline std::string peek1( ) { return tokenList.at( index + 2 ); }

            inline std::string peek2( ) { return tokenList.at( index + 3 ); }

            inline std::string last( ) { return tokenList.at( index - 1 ); }

            inline std::string last1( ) { return tokenList.at( index - 2 ); }

            inline std::string last2( ) { return tokenList.at( index - 3 ); }

            inline std::string peekNoSpace( ) {
                for(int i = index; i < tokenList.size(); i++){
                    if( tokenList.at( i ) != " " && tokenList.at( i ) != "\n" ){
                        return tokenList.at( i );
                    }
                }
                return "EOF";
            }

            inline std::string peekNoSpace1( ) {
                for(int i = index + 1; i < tokenList.size(); i++){
                    if( tokenList.at( i ) != " " && tokenList.at( i ) != "\n" ){
                        return tokenList.at( i );
                    }
                }
                return "EOF";
            }

            inline std::string peekNoSpace2( ) {
                for(int i = index + 2; i < tokenList.size(); i++){
                    if( tokenList.at( i ) != " " && tokenList.at( i ) != "\n" ){
                        return tokenList.at( i );
                    }
                }
                return "EOF";
            }

            inline std::string lastNoSpace( ) {
                for(int i = index-2; i > 0; i--){
                    if( tokenList.at( i ) != " " && tokenList.at( i ) != "\n" ){
                        return tokenList.at( i );
                    }
                }
                return "EOF";
            }
            
            inline std::string getUntilToken( std::string from , std::string to ) {
                std::string ret = "";
                bool start = false;
                // std::cout << "index: " << index << " size: " << tokenList.size() << std::endl;
                for(int i = index; i < tokenList.size(); i++) {
                    if( tokenList.at(i) == from && (!start) ){
                        start = true;
                    } else if( tokenList.at(i) == to && start ){
                        return ret;
                    } else if( start ) {
                        ret += tokenList.at(i);
                    }
                }
                // std::cout << "ret : " << ret << std::endl;
                return "EOF";
            }

            inline std::string getUntilToken( std::string to ) {
                std::string ret = "";
                // std::cout << "index: " << index << " size: " << tokenList.size() << std::endl;
                for(int i = index; i < tokenList.size(); i++) {
                    if( tokenList.at(i) == to ){
                        return ret;
                    } else {
                        ret += tokenList.at(i);
                    }
                }
                // std::cout << "ret : " << ret << std::endl;
                return "EOF";
            }

            inline void readUntilDelim( std::string from, std::string to ) {
                if(tokenList.at(index) == from){
                    for(int i = index; i < tokenList.size(); i++) {
                        if( tokenList.at(i) == to ){
                            index = ++i;
                            return;
                        }
                    }
                }

                // std::cout << "ret : " << ret << std::endl;
                return;
            }

            inline bool hasNext( ) { return (index != tokenList.size()); }

            inline int checkIndentLength() {
                int ret = 0;
                for(int i = index; i > 0; i--) {
                    if( tokenList.at(i) == "\n" ){
                        break;
                    } else if( tokenList.at(i) == " "){
                        ret ++;
                    } else {
                        ret = 0;
                    }
                }
                return ret;
            }

            inline void printVector() {
                for (auto i = tokenList.begin(); i != tokenList.end(); ++i) {
                    if(*i == " "){
                        std::cout << "\\s" << ',';
                    } else if(*i == "\n") {
                        std::cout << "\\n" << ',';
                    } else {
                        std::cout << *i << ',';
                    }
                }
                std::cout << "\n\n";
            }
    };
}