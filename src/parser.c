#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token *peek(struct Parser *parser)
{
    return &parser->tokens->data[parser->current]; // returns pointer to token at curr index 
}

struct Token *advance(struct Parser *parser)
{
    if(parser->current < parser->tokens->size){
        parser->current++;
    }
    return &parser->tokens->data[parser->current - 1]; // we return the token we just consumed 
}

bool match(struct Parser *parser, enum TokenType type){
    if(peek(parser)->type == type){
        advance(parser);
        return true;
    }
    return false;
}

void parserInit(struct Parser *parser, struct TokenVector *tokens){
    parser->tokens = tokens;
    parser->current = 0;
}

struct ASTNode *parseNumber(struct Parser *parser){
    struct Token *token= peek(parser);
    struct ASTNode *node = malloc(sizeof(struct ASTNode));
    if(node==NULL){
        fprintf(stderr,"failed to alloc memory for ASTNode in parseNumber\n");
        return NULL;
    }
    node->type = AST_NUMBER;
    char temp[64];
    memcpy(temp, token->start, token->length);
    temp[token->length]= '\0';
    node->number = strtod(temp,NULL);
    advance(parser);
    return node;
}

struct ASTNode *parseVariable(struct Parser *parser)
{
    struct Token *token = peek(parser);
    struct ASTNode *node = malloc(sizeof(struct ASTNode));
    if(node==NULL){
        fprintf(stderr,"failed to alloc memory for variable node\n\n");
        return NULL;
    }
    node->type = AST_VARIABLE;
    node->name = malloc(token->length + 1);
    if(node->name ==NULL){
        free(node);
        return(NULL);
    }
    memcpy(node->name, token->start, token->length);
    node->name[token->length] = '\0';
    advance(parser);
    return node;

}

struct ASTNode *parse(struct TokenVector *tokens)  // entry point
{
    struct Parser parser;
    parserInit(&parser,tokens);
    return parseVariable(&parser);
}

