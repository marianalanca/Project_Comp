#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct _params{
	char* id;
	char* type;
	int line;
    int column;
	struct _params *next;
} param_list;

typedef struct _symbol_table{
	char* name;
	char* type;
	int line;
    int column;
	struct _params* parametes; // lista ligada dos parâmetros que estão incluídos -> será necessário imprimir os tipos
	struct _symbol_table *next;
} table_element;

table_element *insert_el(char *str, char* type);
void add_to_paramList( param_list* paramList, param_list* newParam );
param_list* create_param(char* id, char* type);
void show_table();
table_element *search_el(char *str);

#endif

