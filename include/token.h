#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h> // we use size_t thats why

enum TokenType{
    //special ones 
    TOKEN_EOF,
    TOKEN_ERROR,
    //literals:
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    //keywords:
    TOKEN_LET,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_PRINT,
    TOKEN_TRUE,
    TOKEN_FALSE,
    //operators 
    TOKEN_PLUS, 
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_ASSIGN,          // = equal
    TOKEN_EQUAL,           // == double equal
    TOKEN_NOT_EQUAL,       // !=
    TOKEN_LESS,            
    TOKEN_LESS_EQUAL,      
    TOKEN_GREATER,         
    TOKEN_GREATER_EQUAL,   
    TOKEN_AND,             // &&
    TOKEN_OR,              // ||
    TOKEN_NOT,             // !
    //delimiters only these for now
    TOKEN_LPAREN,          // (
    TOKEN_RPAREN ,          // )
    TOKEN_LBRACE,          // {
    TOKEN_RBRACE,          // }
    TOKEN_SEMICOLON,       // ;
    TOKEN_COMMA            // ,
};

struct Token{
    enum TokenType type;
    const char *start; // jus storing pointer to the start of the token
    size_t length;// now we can just do :  for this length keep going from start 
    size_t line; 
};

struct TokenVector{
    struct Token *data;
    size_t size;
    size_t capacity;
};

#endif
