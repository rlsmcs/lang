#ifndef VECTOR_H
#define VECTOR_H
#include "token.h"
void tokenVectorInit(struct TokenVector *vector);
void tokenVectorPush(struct TokenVector *vector, struct Token token);
void tokenVectorFree(struct TokenVector *vector);

#endif
