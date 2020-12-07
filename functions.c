#include "functions.h"

//ATENÇAO: qd fazemos free no print_tree falta fazer free primeiro dos char*!!!

node * insertNode(char * id, char * type, node * son, int line, int col) {
        node * aux = (node *)malloc(sizeof(node));
        aux->type = type;
        aux->id = id;
        aux->son = son;
        aux->brother = NULL;
        aux->anoted = NULL;
        aux->col = col;
        aux->line = line;
        aux->params = NULL;
        aux->n_params = -1;

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

token* createToken(char *id, int line, int colunm){
    token *new = (token*)malloc(sizeof(token));
    if(id != NULL){
        new->id = (char*)strdup(id);
    }
    else{
        new->id = NULL;
    }
    new->line = line;
    new->col = colunm;
    return new;
}

void freeToken(token *aux){
    if(aux != NULL){
        if(aux->id != NULL){
        free(aux->id);
        aux->id = NULL;
    }
    free(aux);
    aux = NULL;
    } 
}
