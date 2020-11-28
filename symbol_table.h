#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol_table.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "functions.h"
#include <ctype.h>

typedef struct _params{
	char* id;
	char* type;
	int line;
    int column;
	struct _params *next;
} param_list;

typedef struct _vars{
	char* id;
	char* type;
	int line;
    int column;
	// adicionar as variáveis -> ex funções; se variáveis não é necessário
	struct _params* parameters;
	struct _vars *next;
} var_list;

typedef struct _symbol_table{
	char* tableName;
	// necessário?
	char* tableType; // tipo function, local, global?
	struct _vars* variables;
	struct _params* parameters; // lista ligada dos parâmetros que estão incluídos -> será necessário imprimir os tipos
	struct _symbol_table *next; // no caso de ser local
} table_element;

void create_semantics(node* root);
table_element* create_table(char* tableName, char* tableType);
var_list *insert_global(char *str, char* type);
var_list *insert_local(char *str, char* type/*, int line, int column*/, table_element* local_table);
param_list* add_to_paramList( param_list* paramList, param_list* newParam );
param_list* create_param(char* id, char* type);
void show_table();
void show_global_table();
void show_local_table();
//Procura um identificador, devolve 0 caso nao exista
var_list *search_global(char *str);
void show_local_table();
var_list *search_local(char *str);

#endif

