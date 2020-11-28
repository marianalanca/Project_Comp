#include "symbol_table.h"

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
	char* aux_char;
	node * actual_node,* aux, *aux1, *aux2, *aux3, *aux4, * program, * aux_program;
	var_list * aux_var_list, *aux_variable;;
	param_list* aux_param_list;
	table_element* aux_table;
	table_element* local_table;
	int count_params;

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

			// TERMINAR
			if (strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition

				aux = actual_node->son;
				aux_variable = create_var(aux->brother->son->id, aux->type);


				aux1 = aux->brother->son->brother->son;

				while (aux1!=NULL){

					count_params = 0;
					if (aux1->son->brother==NULL){
						aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));
					} else {
						//verificar se existe
						if (search_param_in_params(aux_variable->parameters, aux1->son->brother->id)!=NULL){
							printf("Line %d, col %d: Symbol %s already defined\n", 0, 0, aux1->son->brother->id);
						} else {
							aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param(aux1->son->brother->id, aux1->son->type));
						}
					}

					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;

				if (search_var_in_table(symtab_global, aux_variable->id)!=NULL){
					printf("Line %d, col %d: Symbol %s already defined\n", 0, 0, aux_variable->id);
				} else {
					insert_global(aux_variable);
				}

			}
			if (strcmp(actual_node->type, "Declaration") == 0) {
				aux_variable = create_var(actual_node->son->brother->id, actual_node->son->type);
				if (search_var_in_table(symtab_global, actual_node->son->brother->id)!=NULL){
					printf("Line %d, col %d: Symbol %s already defined\n", 0, 0, actual_node->son->brother->id);
				} else{
					insert_global(aux_variable);
				}
			}


			// se for uma variável fora de uma função
			aux_program = aux_program->brother;
		}

		aux_program = program->son;

		while (aux_program!=NULL)
		{
			actual_node = aux_program;

			// TERMINAR
			if (strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition
				aux = actual_node->son; //TYPE
				local_table = create_table(aux->brother->son->id, aux->type);

				// adicionar parâmetros

				aux1 = aux->brother->son->brother->son;
				aux_variable = create_var("return", aux->type);

				local_table->variables = aux_variable;

				while (aux1!=NULL){
					// VERIFICAR SE JÁ EXISTE
					if (aux1->son->brother!=NULL){

						if (search_param_in_params(local_table->parameters, aux1->son->brother->id)!=NULL){
							printf("Line %d, col %d: Symbol %s already defined\n", 0, 0, aux1->son->brother->id);
						} else {
							local_table->parameters = add_to_paramList(local_table->parameters, create_param(aux1->son->brother->id, aux1->son->type));
						}
					}

					aux1 = aux1->brother;
				}

				aux = aux->brother->brother; //FuncBody

				if (strcmp(aux->type, "FuncBody") == 0){
					aux1 = aux->son;

					while (aux1!=NULL){

						if (strcmp(aux1->type, "Declaration") == 0) {
							aux2 = aux1->son;
							aux_variable = add_to_varList(aux_variable, create_var(aux2->brother->id, aux2->type));
						}

						else if((strcmp(aux1->type, "") == 0)){} // CONDIÇÃO PARA O PUTCHAR E GETCHAR

						aux1 = aux1->brother;
					}

				}

				// MUDAR
				if (search_var_in_table(symtab_local, local_table->tableName)!=NULL){
					printf("Line %d, col %d: Symbol %s already defined\n", 0, 0, aux_variable->id);
				} else {
					create_local(local_table);
				}
			}

			aux_program = aux_program->brother;
		}

	}
}


void create_local(table_element* newLocal){
	table_element* auxiliar = symtab_local;


	if(auxiliar==NULL){
		symtab_local = newLocal;
	} else
	{
		while (auxiliar->next!=NULL){
			auxiliar = auxiliar->next;
		}
		auxiliar->next = newLocal;
	}
}

//Insere um novo identificador na cauda de uma lista ligada de simbolo
void insert_global(var_list* newVar)
{
	symtab_global->variables = add_to_varList(symtab_global->variables, newVar);
}

void insert_local(table_element* local_table, var_list* newVar){
	local_table->variables = add_to_varList(local_table->variables, newVar);
}

var_list* create_var (char *id, char* type){
	var_list* newVar = (var_list*)malloc(sizeof(var_list));

	newVar->id = (char*)strdup(id);
	newVar->type = (char*)strdup(type);
	newVar->type[0] = tolower(type[0]);
	newVar->parameters=NULL;
	newVar->next=NULL;

	return newVar;
}

var_list* add_to_varList(var_list* list, var_list* newVar){
	var_list* auxiliar = list;

	if(auxiliar==NULL){
		list = newVar;
	} else
	{
		while (auxiliar->next!=NULL){
			auxiliar = auxiliar->next;
		}
		auxiliar->next = newVar;
	}

	return list;
}

param_list* create_param(char* id, char* type){
	param_list* newParam = (param_list*)malloc(sizeof(param_list));

	newParam->id = (char*)strdup(id);
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
		while (auxiliar->next!=NULL){
			auxiliar = auxiliar->next;
		}
		auxiliar->next = newParam;
	}

	return paramList;

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

var_list *search_var_in_table (table_element* symtab, char* str){
	table_element* aux_table;
	var_list * aux_var_list;

	aux_table = symtab;

	while (aux_table!=NULL){
		aux_var_list=aux_table->variables;
		while (aux_var_list!=NULL)
		{
			if (strcmp(aux_var_list->id, str) == 0)
				return aux_var_list;
			aux_var_list = aux_var_list->next;
		}

		aux_table=aux_table->next;
	}

	return NULL;
}

param_list *search_param_in_table (table_element* symtab, char* str){
	table_element* aux_table;
	param_list * aux_param_list;

	aux_table = symtab;

	while (aux_table!=NULL){
		aux_param_list=aux_table->parameters;
		while (aux_param_list!=NULL)
		{
			if (strcmp(aux_param_list->id, str) == 0)
				return aux_param_list;
			aux_param_list = aux_param_list->next;
		}

		aux_table=aux_table->next;
	}

	return NULL;
}

param_list *search_param_in_params (param_list* list, char* str){
	param_list * aux_param_list;

	aux_param_list = list;

	while (aux_param_list!=NULL){
		if (strcmp(aux_param_list->id, str) == 0)
			return aux_param_list;

		aux_param_list=aux_param_list->next;
	}

	return NULL;
}


void show_local_table(){
	var_list *aux;
	param_list * aux1;
	table_element *current_table = symtab_local;

	while (current_table!=NULL)
	{
		printf("===== Function %s Symbol Table =====\n", current_table->tableName);

		for(aux=current_table->variables; aux; aux=aux->next){
				printf("%s\t%s\n", aux->id, aux->type);
		}

		for (aux1=current_table->parameters; aux1; aux1=aux1->next){
			printf("%s\t%s\tparam\n", aux1->id, aux1->type);
		}

		current_table = current_table->next;
		printf("\n");
	}
}
