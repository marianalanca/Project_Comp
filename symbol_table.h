#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <ctype.h>
#include "functions.h"

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
    int function; //indica se é funçao ou nao
    int n_params; //se for function tem o numero de parametros
	struct _params* parameters;
	struct _vars *next;
} var_list;

typedef struct _symbol_table{
	char* tableName;
	char* tableType;
	struct _vars* variables;
	struct _params* parameters; // lista ligada dos parâmetros que estão incluídos -> será necessário imprimir os tipos
	struct _symbol_table *next; // no caso de ser local
} table_element;

extern table_element* symtab_global;
extern table_element* symtab_local;

void create_local(table_element* newLocal);
void clean_params(param_list* params);
void create_semantics(node* root);
table_element* create_table(char* tableName, char* tableType);
void insert_global(var_list* newVar);
void insert_local(table_element* local_table, var_list* newVar);
var_list* create_var (char *id, char* type);
var_list* add_to_varList(var_list* list, var_list* newVar);
param_list* add_to_paramList( param_list* paramList, param_list* newParam );
param_list* create_param(char* id, char* type);
void show_table();
void show_global_table();
void show_local_table();
void show_local_table();
var_list *search_var_in_table (table_element* symtab, char* str);
param_list *search_param_in_table (table_element* symtab, char* str);
param_list *search_param_in_params (param_list* list, char* str);
table_element *search_func_in_table (char* funcName);
char* get_type(node* actual);

void anote_ast(table_element* table_global, table_element* table_local, node* atual);
void printAnotedAST(node* node, int depth);

#endif

