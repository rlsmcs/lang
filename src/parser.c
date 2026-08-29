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
struct ASTNode *parseTerm(struct Parser *parser);
int isBinaryOperator(enum TokenType type);

struct ASTNode *parseProgram(struct Parser *parser);



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
    return parseProgram(&parser);
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
    if(peek(parser)->type == TOKEN_LPAREN){
        advance(parser);
        struct ASTNode *node =parseExpression(parser);
        if(peek(parser)->type !=TOKEN_RPAREN){
            fprintf(stderr,"expcted )\n");
            return NULL;
        }
        advance(parser);
        return node;
    }
    
    return NULL;
}

struct ASTNode *parseExpression(struct Parser *parser) // we handle + and - 
{
    struct ASTNode *left= parseTerm(parser);
    while(isBinaryOperator(peek(parser)->type)){
        enum TokenType operator = peek(parser)->type;
        if(operator!= TOKEN_PLUS && operator!=TOKEN_MINUS){
            break;
        }
        advance(parser);
        struct ASTNode *right =parseTerm(parser);
        struct ASTNode *node= malloc(sizeof(struct ASTNode));
        if(node==NULL){
            fprintf(stderr, "failed to alloc memory for binary nrode\n");
            return NULL;
        }
        node->type=AST_BINARY;
        node->left=left;
        node->right=right;
        left=node;
        
    }
    return left;
}


int isBinaryOperator(enum TokenType type)  // helper func for our expressions
{
    return type == TOKEN_PLUS ||
           type == TOKEN_MINUS ||
           type == TOKEN_STAR||
           type == TOKEN_SLASH;
}

struct ASTNode *parseTerm(struct Parser *parser)  // we handle * and /
{
    struct ASTNode *left = parsePrimary(parser);
    while(isBinaryOperator(peek(parser)->type)) {
        enum TokenType operator = peek(parser)->type;
        if (operator != TOKEN_STAR &&
            operator != TOKEN_SLASH) {
            break;
        }
        advance(parser);
        struct ASTNode *right = parsePrimary(parser);
        struct ASTNode *node = malloc(sizeof(struct ASTNode));
        if (node == NULL) {
            fprintf(stderr,"failed to alloc memory for binary node\n");
            return NULL;
        }
        node->type = AST_BINARY;
        node->left = left;
        node->right = right;
        node->operator = operator;

        left=node;  // we are building the tree progressively so fun
    }
    return left;
}

struct ASTNode *parseProgram(struct Parser *parser)
{
    struct ASTNode *program= malloc(sizeof(struct ASTNode));
    if(program==NULL){
        fprintf(stderr, "failed to alloc memory for program!\n");
        return NULL;
    }
    program->type=AST_PROGRAM;
    program->statements=NULL;
    program->statementCount=0;

    while(peek(parser)->type != TOKEN_EOF){
        struct ASTNode *statement = NULL;
        if(peek(parser)->type==TOKEN_LET){
            statement=parseVarDeclaration(parser);
        }
        else if(peek(parser)->type == TOKEN_PRINT){
            statement= parsePrint(parser);
        }
        else{
            statement=parseExpression(parser);
        }
        if(statement==NULL){
            free(program);
            return NULL;
        }
        program->statements= realloc(program->statements,sizeof(struct ASTNode *)*(program->statementCount +1));
        if(program->statements==NULL){
            fprintf(stderr, "failed to allocate statement memory\n");
            free(program);
            return NULL;
        }
        program->statements[program->statementCount] = statement;
        program->statementCount++;

        
    }
    return program;
}
