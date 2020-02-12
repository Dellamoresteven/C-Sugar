#include "../parser.h"

void parser::ReplacerObject::replaceIncludes( token::TokenObject * newtoken ){
    token->skip(4); // eat "inc" "\s" "e" "\n"
    newtoken->push("#include <iostream>\n");
    newtoken->push("#include <stdlib.h>\n");
    newtoken->push("#include <fstream>\n");
    newtoken->push("#include <algorithm>\n");
    newtoken->push("#include <vector>\n");
    newtoken->push("#include <string>\n");
    newtoken->push("#include <cctype>\n");
    newtoken->push("#include <list>\n");
    newtoken->push("#include <sys/stat.h>\n");
    newtoken->push("#include <unistd.h>\n");
    newtoken->push("#include <functional>\n");
    newtoken->push("#include <map>\n");
    newtoken->push("#include <sstream>\n");
    newtoken->push("#include <iterator>\n");
}