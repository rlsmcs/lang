#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"
#include "parser.h"

char *readSource(FILE *fp, size_t filesize){
    char *buffer = malloc(filesize+1);
    if(buffer==NULL){
        perror("buffer");
        return NULL;
    }
    size_t bytesRead = fread(buffer,1,filesize,fp);
    if(bytesRead!=filesize){
        fprintf(stderr,"all bytes not read- later make readAll func");
        free(buffer);
        return NULL;
    }
    buffer[filesize]='\0'; //stringify 
    return buffer;
}

// temp recursive AST printer to test precedence
void printAST(struct ASTNode *node)
{
    if(node==NULL){
        return;
    }
    printf("type:%d\n", node->type);
    if(node->type == AST_NUMBER){
        printf("number: %f\n", node->number);
    }
    if(node->type == AST_VARIABLE){
        printf("variable: %s\n", node->name);
    }
    if(node->type == AST_BINARY){
        printf("operator: %d\n", node->operator);
        printf("LEFT:\n");
        printAST(node->left);
        printf("RIGHT:\n");
        printAST(node->right);
    }
}
// end of temp func

int main(int argc, char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"usage: %s <source-file>\n", argv[0]);
        return 1;
    }
    char *filepath = argv[1];
    FILE *fp=  fopen(filepath,"r");
    if(!fp){
        perror("fopen");
        return 1;
    }
    fseek(fp,0,SEEK_END);
    long filesize = ftell(fp); // func signature is long ftell(FILE *stream) so we store its result in long 
    if(filesize<0){
        perror("ftell");
        return 1;
    }
    size_t size =(size_t)filesize; // now we can convert to size_t and use everywhere 
    rewind(fp);
    char *source = readSource(fp,size);
    struct TokenVector tokens = lex(source);
    struct ASTNode *ast = parse(&tokens);

    // temporary block of code to inspect tokens and now also parse the numbers.lang file 
    for (size_t i = 0; i < tokens.size; i++) {
        struct Token token = tokens.data[i];

        printf("Token type: %d -  Value: %.*s  -  Line: %zu\n",  // * also expects an int thats why we do type casting
           token.type,
           (int)token.length,
           token.start,
           token.line);
    }
    /* temp block for now
    printf("ast type: %d \n\n",ast->type);
    printf("left: %s \n\n", ast->left->name);
    printf("right: %f \n\n", ast->right->number); */ 
    printAST(ast);

    free(ast);
    fclose(fp);
    if(source ==NULL){
        return 1;
    }
    free(source);
    return 0;
}
