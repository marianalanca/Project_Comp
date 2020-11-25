#include "symbol_table.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern table_element* symtab;

//Insere um novo identificador na cauda de uma lista ligada de simbolo
table_element *insert_el(char *str, char* type/*, int line, int column*/)
{
	table_element *newSymbol=(table_element*) malloc(sizeof(table_element));
	table_element *aux;
	table_element* previous;

	newSymbol->name = (char*)strdup(str);
	newSymbol->type = (char*)strdup(type);
    //newSymbol->line = line;
    //newSymbol->column = column;
	newSymbol->parametes = NULL;
	newSymbol->next=NULL;

	if(symtab)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=symtab; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->name, str)==0)
				return NULL;

		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		symtab=newSymbol;

	return newSymbol;
}

param_list* create_param(char* id, char* type){
	param_list* newParam = (param_list*)malloc(sizeof(param_list));

	if (id!=NULL)
		newParam->id = (char*)strdup(id);
	else
	{
		newParam->id = NULL;
	}

	newParam->type = (char*)strdup(type);
	newParam->next=NULL;

	return newParam;
}

void add_to_paramList( param_list* paramList, param_list* newParam ){
	param_list* auxiliar = paramList;

	if(auxiliar==NULL){
		paramList = newParam;
	} else
	{
		while (auxiliar->next!=NULL)
	{
		auxiliar = auxiliar->next;
	}
	auxiliar->next = newParam;
	}

}

// INCOMPELTO
char* print_param_types(param_list* paramList){
	param_list* auxiliar = paramList;
	char* types;

	strcpy(types, auxiliar->type);
	auxiliar= auxiliar->next;

	while (auxiliar!=NULL)
	{
		strcat(types, ", "); // INCOMPELTO
	}
	return types;
}

void delete_el(table_element* element){
    free(element);
    element=NULL;
}

void show_table()
{
table_element *aux;
printf("\n");
printf("===== Global Symbol Table =====\n");
for(aux=symtab; aux; aux=aux->next)
	printf("%s\t%s()\n", aux->name, aux->type); // Acabar
}

//Procura um identificador, devolve 0 caso nao exista
table_element *search_el(char *str)
{
table_element *aux;

for(aux=symtab; aux; aux=aux->next)
	if(strcmp(aux->name, str)==0)
		return aux;

return NULL;
}

