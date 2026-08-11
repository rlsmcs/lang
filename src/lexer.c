#include "lexer.h"
#include "vector.h"
#include <ctype.h>  

struct TokenVector lex(const char *source){
    struct TokenVector tokens;
    tokenVectorInit(&tokens); //init
    const char *current = source;
    size_t line=1;
    while(*current !='\0'){
        if(isdigit(*current)){
            const char *start = current;
            while(isdigit(*current)){
                current++;
            }
            struct Token token;
            token.type=TOKEN_NUMBER;
            token.start=start;
            token.length= (current-start);
            token.line=line;
            tokenVectorPush(&tokens,token);
            continue;
        }
        current++;
    }
    return tokens;
}
