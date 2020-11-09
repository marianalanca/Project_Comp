#ifndef AST_H
#define AST_H

//basic_type type;

typedef struct _t1{
	char* id;
	char* type;
	struct _t1* son;
    struct _t1* brother;
} node;

node* insertNode(char* , char* , node*);
void printTree(node * auxNode, int pontos);
void linkBrothers(node* , node*);


#endif