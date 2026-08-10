#ifndef LEXER_H
#define LEXER_H
#include "token.h"
struct TokenVector lex(const char *source); // const cuz we dont modify source
// basically we return type struct tokenvector after lexing the source which we dont care where it comes from its now in the ram
#endif
