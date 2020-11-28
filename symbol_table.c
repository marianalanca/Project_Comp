#include "symbol_table.h"

extern table_element* symtab_global;
extern table_element* symtab_local;

table_element* create_table(char* tableName, char* tableType){ // se local é 1

	table_element* newTable = (table_element*)malloc(sizeof(table_element));
	table_element* aux = symtab_local;

	newTable->tableName = (char*)strdup(tableName);
	newTable->tableType = (char*)strdup(tableType);
	newTable->variables = NULL;
	newTable->parameters = NULL;
	newTable->next = NULL; // no caso de ser global, fica sempre NULL

	return newTable;
}

// NOTA: NO CASO DE TIPO: fazer str[0] = tolower(str)

void create_semantics(node* root){
	node * actual_node,* aux, * program, * aux_program;
	var_list * aux_var_list;
	param_list* aux_param_list;
	table_element* aux_table;
	table_element* local_table;

	program = root;

	if (program == NULL){
		return; // termina se vazia
	}

	if( strcmp(program->type, "Program") == 0 ){ // se for um program

		aux_program = program->son;

		symtab_global = create_table("Global", "Global");

		while (aux_program!=NULL)
		{
			actual_node = aux_program;

			// falta fazer o funcbody
			if (strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition
				actual_node = actual_node->son;

				local_table = create_table(actual_node->brother->son->id, actual_node->type);

				aux_var_list = insert_global(actual_node->brother->son->id, actual_node->type);

				// adicionar parâmetros

				aux = actual_node->brother->son->brother->son;

				while (aux!=NULL){

					if (aux->brother==NULL){
						aux_var_list->parameters = add_to_paramList(aux_var_list->parameters, create_param("", aux->son->type));
					} else {
						aux_var_list->parameters = add_to_paramList(aux_var_list->parameters, create_param(aux->brother->id, aux->son->type));
					}

					aux = aux->brother;
				}

				// printf("%s\n", aux->type);
				aux = actual_node->brother->brother->son;
				while ( aux!=NULL ){ // FuncBody
					if (strcmp(aux->type, "Declaration") == 0 ) {
						insert_local(aux->son->type, aux->son->brother->id, local_table);
						//printf("%s\t%s\n", aux->son->type, aux->son->brother->id);
					}
					aux = aux->brother;
				}


				/* FALTA BODYFUNC*/
				// a partir daqui é local

				aux_table = symtab_local;

				if(aux_table==NULL){
					symtab_local = local_table;
				} else{
					while(aux_table->next!=NULL){
						aux_table = aux_table->next;
					}

					aux_table->next = local_table;
				}

				

			}

			if (strcmp(actual_node->type, "Declaration") == 0) {

				insert_global(actual_node->son->brother->id, actual_node->son->type);
			}


			// se for uma variável fora de uma função
			aux_program = aux_program->brother;
		}

		// globais -> variáveis, putchars, funções
	}


}

//Insere um novo identificador na cauda de uma lista ligada de simbolo
var_list *insert_global(char *str, char* type/*, int line, int column*/)
{
	var_list *newSymbol=(var_list*) malloc(sizeof(var_list));
	var_list *aux;
	var_list* previous;

	newSymbol->id = (char*)strdup(str);
	newSymbol->type = (char*)strdup(type);
	newSymbol->type[0] = tolower(type[0]);
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

var_list *insert_local(char *str, char* type/*, int line, int column*/, table_element* local_table)
{
	var_list *newSymbol=(var_list*) malloc(sizeof(var_list));
	var_list *aux;
	var_list* previous;

	newSymbol->id = (char*)strdup(str);
	newSymbol->type = (char*)strdup(type);
	newSymbol->type[0] = tolower(type[0]);
    //newSymbol->line = line;
    //newSymbol->column = column;
	newSymbol->parameters = NULL;
	newSymbol->next=NULL;

	if(local_table->variables)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=local_table->variables; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->id, str)==0)
				return NULL;

		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		local_table->variables=newSymbol;

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
	newParam->type[0] = tolower(type[0]);
	newParam->next=NULL;

	return newParam;
}

param_list* add_to_paramList( param_list* paramList, param_list* newParam ){
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

	return paramList;

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
 param_list * aux1;

printf("===== Global Symbol Table =====\n");
for(aux=symtab_global->variables; aux; aux=aux->next){
	if (aux->parameters!=NULL){
		printf("%s\t%s(%s", aux->id, aux->type, aux->parameters->type );
		aux1 = aux->parameters->next;
		while(aux1!=NULL){
			printf(",%s", aux1->type);
			aux1 = aux1->next;
		}
		printf(")\n");
	} else {
		printf("%s\t%s\n", aux->id, aux->type );
	}
}
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
			printf("%s\t%s\n", aux->id, aux->type); // Acabar
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

