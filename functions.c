#include "functions.h"

node * insertNode(char * id, char * type, node * son) {
        node * aux = (node *)malloc(sizeof(node));
        aux->type = type;
        aux->id = id;
        aux->son = son;
        aux->brother = NULL;

        return aux;
}

void connectBrothers(node* node1, node* brother){
    while (node1->brother!=NULL)
        node1 = node1->brother;
    node1->brother = brother;
}

void print_tree(node* node, int depth){

    if (node != NULL){
        if (node->type!=NULL){
            int i;


            for (i = 0; i < depth; i++){
                printf("..");
            }
            printf("%s",node->type);
            if (node->id != NULL){
                printf("(%s)", node->id);
            }
            printf("\n");
        }

        if (node->type==NULL){
            print_tree(node->son, depth);
        } else {
            print_tree(node->son, depth + 1);
        }

        print_tree(node->brother, depth);

        free(node);
    }
}