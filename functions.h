#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _t1{
        char* id;
        char* type;
        struct _t1* son;
        struct _t1* brother;
    } node;

node * insertNode(char * id, char * type, node * son);
void connectBrothers(node* node1, node* brother);
void print_tree(node* node, int depth);

#endif