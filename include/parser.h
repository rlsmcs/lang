#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
#include "token.h"
#include "ast.h"

struct Parser {
    struct TokenVector *tokens;
    size_t current;
};

struct ASTNode *parse(struct TokenVector *tokens);
#endif

