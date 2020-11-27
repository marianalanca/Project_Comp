#include "symbol_table.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern table_element* symtab_global;
extern table_element* symtab_local;

table_element* create_table(char* tableName, char* tableType, int flag){ // se local é 1

	table_element* newTable = (table_element*)malloc(sizeof(table_element));
	table_element* aux = symtab_local;

	newTable->tableName = (char*)strdup(tableName);
	newTable->tableType = (char*)strdup(tableType);
	newTable->variables = NULL;
	newTable->parameters = NULL;
	newTable->next = NULL; // no caso de ser global, fica sempre NULL

	if (flag){ 
		if(symtab_local == NULL){
			symtab_local = newTable;
		}
		else{
			while (aux->next!=NULL)
			{
				aux = aux->next;
			}

			aux->next = newTable;
		}
	}

	return newTable;
}

//Insere um novo identificador na cauda de uma lista ligada de simbolo
var_list *insert_global(char *str, char* type/*, int line, int column*/)
{
	var_list *newSymbol=(var_list*) malloc(sizeof(var_list));
	var_list *aux;
	var_list* previous;

	newSymbol->id = (char*)strdup(str);
	newSymbol->type = (char*)strdup(type);
    //newSymbol->line = line;
    //newSymbol->column = column;
	newSymbol->parameters = NULL;
	newSymbol->next=NULL;

	// SEG_FAULT
	if(symtab_global->variables){	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
	for(aux=symtab_global->variables; aux; previous=aux, aux=aux->next)
		if(strcmp(aux->id, str)==0)
			return NULL;

	previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		symtab_global->variables=newSymbol;

	return newSymbol;
}

var_list *insert_local(char *str, char* type/*, int line, int column*/)
{
	var_list *newSymbol=(var_list*) malloc(sizeof(var_list));
	var_list *aux;
	var_list* previous;

	newSymbol->id = (char*)strdup(str);
	newSymbol->type = (char*)strdup(type);
    //newSymbol->line = line;
    //newSymbol->column = column;
	newSymbol->parameters = NULL;
	newSymbol->next=NULL;

	if(symtab_local->variables)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=symtab_local->variables; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->id, str)==0)
				return NULL;

		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		symtab_local->variables=newSymbol;

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

void show_table(){
	show_global_table();
	show_local_table();
}

void show_global_table()
{
 var_list *aux;

printf("===== Global Symbol Table =====\n");
for(aux=symtab_global->variables; aux; aux=aux->next)
	printf("%s\t%s()\n", aux->id, aux->type); // Acabar
printf("\n");
}

//Procura um identificador, devolve 0 caso nao exista
var_list *search_global(char *str)
{
var_list *aux;

for(aux=symtab_global->variables; aux; aux=aux->next)
	if(strcmp(aux->id, str)==0)
		return aux;

return NULL;
}

void show_local_table(){
	var_list *aux;
	table_element *current_table = symtab_local;

	while (current_table)
	{
		printf("===== Function %s Symbol Table =====\n", current_table->tableName);
		for(aux=symtab_local->variables; aux; aux=aux->next)
			printf("%s\t%s()\n", aux->id, aux->type); // Acabar
		current_table = current_table->next;
		printf("\n");
	}
	printf("\n");
}

//Procura um identificador, devolve 0 caso nao exista
var_list *search_local(char *str)
{
var_list *aux;

for(aux=symtab_local->variables; aux; aux=aux->next)
	if(strcmp(aux->id, str)==0)
		return aux;

return NULL;
}

