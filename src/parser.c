#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ASTNode *parseNumber(struct Parser *parser);
struct ASTNode *parseVariable(struct Parser *parser);
struct ASTNode *parseVarDeclaration(struct Parser *parser);
struct ASTNode *parsePrint(struct Parser *parser);
struct ASTNode *parseBinary(struct Parser *parser);
struct ASTNode *parsePrimary(struct Parser *parser);
struct ASTNode *parseExpression(struct Parser *parser);
int isBinaryOperator(enum TokenType type);



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
    if(peek(&parser)->type == TOKEN_LET){
    return parseVarDeclaration(&parser);
    }
    if(peek(&parser)->type == TOKEN_PRINT){
        return parsePrint(&parser);
    }
    return parseExpression(&parser);
}


struct ASTNode *parseVarDeclaration(struct Parser *parser){
    match(parser, TOKEN_LET);
    struct Token *nameToken= peek(parser);
    advance(parser);
    match(parser,TOKEN_ASSIGN);
    struct ASTNode *value = parseExpression(parser);
    match(parser, TOKEN_SEMICOLON);
    
    struct ASTNode *node=  malloc(sizeof(struct ASTNode));
    if(node==NULL){
        fprintf(stderr, "failed to alloc memory\n");
        return NULL;
    }
    node->type = AST_VAR_DECL;
    node->name=malloc(nameToken->length + 1);
    memcpy(node->name, nameToken->start, nameToken->length);
    node->name[nameToken->length]='\0';
    node->value = value;
    return node;
}

struct ASTNode *parsePrint(struct Parser *parser){
    match(parser, TOKEN_PRINT);
    match(parser, TOKEN_LPAREN);
    struct ASTNode *value = parseExpression(parser);
    match(parser, TOKEN_RPAREN);
    match(parser,TOKEN_SEMICOLON);

    struct ASTNode *node = malloc(sizeof(struct ASTNode));
    if(node==NULL){
        fprintf(stderr, "failed to alloc memory\n");
        return NULL;
    }
    node->type = AST_PRINT;
    node->value = value;
    return node;
}

struct ASTNode *parseBinary(struct Parser *parser)
{
    struct ASTNode *left = parsePrimary(parser);
    enum TokenType operator= peek(parser)->type;
    if(!isBinaryOperator(operator)){
        return left;
    }
    advance(parser);
    struct ASTNode *right = parsePrimary(parser);
    struct ASTNode *node=malloc(sizeof(struct ASTNode));
    if(node==NULL){
        fprintf(stderr,"failed to alloc memory for binary node \n");
        return NULL;
    }
    node->type= AST_BINARY;
    node->left=left;
    node->right=right;
    node->operator=operator;
    return node;
}

struct ASTNode *parsePrimary(struct Parser *parser){
    if(peek(parser)->type == TOKEN_NUMBER){
        return parseNumber(parser);
    }
    if(peek(parser)->type == TOKEN_IDENTIFIER){
        return parseVariable(parser);
    }
    return NULL;
}

struct ASTNode *parseExpression(struct Parser *parser)
{
    return parseBinary(parser);
}


int isBinaryOperator(enum TokenType type)  // helper func for our expressions
{
    return type == TOKEN_PLUS ||
           type == TOKEN_MINUS ||
           type == TOKEN_STAR||
           type == TOKEN_SLASH;
}


