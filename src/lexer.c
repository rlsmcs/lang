#include "lexer.h"
#include "vector.h"
#include <ctype.h>  

struct TokenVector lex(const char *source){
    struct TokenVector tokens;
    tokenVectorInit(&tokens); //init
    const char *current = source;
    while(*current !='\0'){
        if(isdigit(*current)){
            const char *start = current;
            while(isdigit(*current)){
                current++;
            }
        }
        current++;
    }
    return tokens;
}
