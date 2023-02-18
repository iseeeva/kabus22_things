#include <string>

std::string parse_escape(std::string input)
{
    std::string escapeArray[9] = {"\\'","\\\"","\\\\","\\n","\\r","\\t","\\b","\\f","\\v"};
    std::string escapeArrayL[9] = {"\'","\"","\\","\n","\r","\t","\b","\f","\v"};
    for( unsigned int i = 0; i < sizeof(escapeArray)/sizeof(escapeArray[0]); i = i + 1 ){
        std::string::size_type index = 0;
        while ((index = input.find(escapeArray[i], index)) != std::string::npos) {
            input.replace(index, 2, escapeArrayL[i]);
            ++index;
        }
    }
    return input;
}

//sprintf_s(char_dummy, "%ld x %ld", find_resolution(i).x,find_resolution(i).y);