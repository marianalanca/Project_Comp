#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct _params{
	char id[32];
	basic_type type;
	int line;
    int column;
	struct _params *next;
} param_list;

typedef enum {integer, character, doub, shor} basic_type;
typedef struct _t1{
	char name[32];
	basic_type type;
	int line;
    int column;
	struct _params* parametes; // lista ligada dos parâmetros que estão incluídos -> será necessário imprimir os tipos
	struct _t1 *next;
} table_element;

table_element *insert_el(char *str, basic_type t);
void show_table();
table_element *search_el(char *str);

#endif

