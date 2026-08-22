#ifndef AST_H
#define AST_H
enum ASTNodeType{
    AST_NUMBER,
    AST_VARIABLE,
    AST_VAR_DECL,
    AST_PRINT,
    AST_BINARY,
};
struct ASTNode{
    enum ASTNodeType type;
    double number;
    char *name;
    struct ASTNode *value;

    struct ASTNode *left;
    struct ASTNode *right;
    enum TokenType operator;
};
#endif
