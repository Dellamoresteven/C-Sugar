#include "parser.h"

void parser::ConfigReaderObject::readConfigFile() {
    char c;
    std::ifstream ffile;
    ffile.open( "config.txt" );
    std::string value = "";
    std::string key = "";
    bool newKey = true;
    while( ffile.get(c) ){
        if(c == '\n' && newKey){ // new key
            newKey = false;
        } else if(newKey) {
            key += c;
        } else if(c == '\\') {
            mapper[ key ] = value;
            key = "";
            value = "";
            ffile.get(c);
        } else {
            value += c;
        }
    }
    // int i = 0;
    // for(auto it = mapper.cbegin(); it != mapper.cend(); ++it) {
    //     std::cout << "i: " << i << "\n" << it->first << "\n" << it->second;
    //     i++;
    // }
}

std::string parser::ConfigReaderObject::getConfig( std::string key ) {
    if ( mapper.find(key) != mapper.end() ) {
        return mapper.find(key)->second;
    } else {
        return "DNE";
    }
}