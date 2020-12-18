#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _t1{
    char* id;
    char* type;
    char *anoted;
    int line;
    int col;
    int n_params;
    struct _params *params;
    struct _t1* son;
    struct _t1* brother;
}node;

typedef struct _token{
    char *id;
    int line, col;
}token;

node * insertNode(char * id, char * type, node * son, int line, int col);
void connectBrothers(node* node1, node* brother);
void print_tree(node* node, int depth);

//AST anotada
token* createToken(char *id, int line, int colunm);
void freeToken(token *aux);


#endif