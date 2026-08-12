#include "lexer.h"
#include "vector.h"
#include <ctype.h>  

struct TokenVector lex(const char *source){
    struct TokenVector tokens;
    tokenVectorInit(&tokens); //init
    const char *current = source;
    size_t line=1;
    while(*current !='\0'){
        if(*current == '\n'){
            line++;
            current++;
            continue;
        }
        if(isspace(*current)){
            current++;
            continue;              //whitespace check comes after newline cuz newline is also whitespace and we wanna count the lines first
        }
        //NUMBERS
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
        } // IDENTIFIERS
        if(isalpha(*current) || *current == '_'){
            const char *start = current;
            while(isalnum(*current)||*current == '_'){
                current ++;
            }
            struct Token token;
            token.type = TOKEN_IDENTIFIER;
            token.start =start;
            token.length= current-start;
            token.line=line;
            tokenVectorPush(&tokens,token);
            continue;
        }
        if(*current == '+'){
            struct Token token;
            token.type = TOKEN_PLUS;
            token.start = current;
            token.length=1;
            token.line=line;
            tokenVectorPush(&tokens,token);
            current++;
            continue;
        }
        if (*current == '-') {
            struct Token token;
            token.type = TOKEN_MINUS;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }
        if (*current == '*') {
            struct Token token;
            token.type = TOKEN_STAR;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == '/') {
            struct Token token;
            token.type = TOKEN_SLASH;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == '%') {
            struct Token token;
            token.type = TOKEN_PERCENT;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }       

        if (*current == '=') {
            struct Token token;
            token.type = TOKEN_ASSIGN;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == '(') {
            struct Token token;
            token.type = TOKEN_LPAREN;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == ')') {
            struct Token token;
            token.type = TOKEN_RPAREN;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == '{') {
            struct Token token;
            token.type = TOKEN_LBRACE;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if (*current == '}') {
            struct Token token;
            token.type = TOKEN_RBRACE;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }

        if(*current == ';'){
            struct Token token;
            token.type = TOKEN_SEMICOLON;
            token.start = current;
            token.length = 1;
            token.line = line;
            tokenVectorPush(&tokens, token);
            current++;
            continue;
        }


        current++;

    }
    return tokens;
}
