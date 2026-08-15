#ifndef AST_H
#define AST_H
enum ASTNodeType{
    AST_NUMBER,
};
struct ASTNode{
    enum ASTNodeType type;
    double number;
};
#endif
