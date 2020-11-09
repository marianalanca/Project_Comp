#include "AST.h"
#include <stdlib.h>
#include<string.h>
#include<stdio.h>

char * auxType;
node * nodeAux;

int commaFlag = 0;

node * insertNode(char * id, char * type, node * son) {
        node * auxNode = (node *)malloc(sizeof(node));
        auxNode->type = type;
        auxNode->id = id;
        auxNode->son = son;
        auxNode->brother = NULL;

        return auxNode;
    }

    void printTree(node * auxNode, int pontos)
    {
        int i, call=0;

        if (auxNode!=NULL){

            if (auxNode->type!=NULL && strcmp(auxNode->type,"Comma")==0 && commaFlag == 1){
                if (auxNode->son != NULL){
                    printTree(auxNode->son,pontos);
                }
            }
            else if (auxNode->type!=NULL && strcmp(auxNode->type,"Aux")==0){
                if (commaFlag==1){
                    commaFlag = 0;
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
                    commaFlag = 1;
                }
                else
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
            }

            else{
                if (auxNode->id != NULL && strcmp(auxNode->id,"type")==0){
                    for (i = 0; i < pontos-2; i++)
                        printf(".");
                    
                    printf("%s\n", auxNode->type);
                    for (i = 0; i < pontos; i++)
                        printf(".");
                    printf("%s\n",auxType);
                
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);  
                            
                }
                
                else if (auxNode->type != NULL){
                    
                    if (strcmp(auxNode->type,"Call")==0){
                        call = 1;
                        commaFlag = 1;
                    }
                    
                    if (strcmp(auxNode->type,"Declaration")==0)
                        auxType = auxNode->son->type;

                    for (i = 0; i < pontos; i++)
                        printf(".");
                    if (auxNode->id != NULL) 
                        printf("%s(%s)\n", auxNode->type, auxNode->id);
                    else   
                        printf("%s\n", auxNode->type);
                    
                    if (auxNode->son != NULL){
                        pontos+=2;
                        printTree(auxNode->son,pontos);
                        pontos-=2;
                    }
                    if (call==1)
                        commaFlag=0;  
                }
                else
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
            }
            if (auxNode->brother != NULL)
                    printTree(auxNode->brother,pontos);
        }  
        free(auxNode);
    }

    void linkBrothers(node * node1, node * node2){
        node1->brother = node2;
    }