#include "symbol_table.h"

table_element* create_table(char* tableName, char* tableType){ // se local é 1

	table_element* newTable = (table_element*)malloc(sizeof(table_element));

	newTable->tableName = (char*)strdup(tableName);
	newTable->tableType = (char*)strdup(tableType);
	newTable->variables = NULL;
	newTable->parameters = NULL;
	newTable->next = NULL; // no caso de ser global, fica sempre NULL

	return newTable;
}

void create_semantics(node* root){
	node * actual_node,* aux, *aux1, *aux2, * program, * aux_program;
	var_list *aux_variable, *test_var;
	table_element* local_table, *test_table;
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

			if (strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition

				aux = actual_node->son;
				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type);

				aux1 = aux->brother->son->brother->son;

				while (aux1!=NULL){
					count_params = 0;

					{
						if (aux1->son->brother==NULL){
							aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));
						} else {
							//verificar se existe
							if (search_param_in_params(aux_variable->parameters, aux1->son->brother->id)!=NULL){
							} else {
								aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param(aux1->son->brother->id, aux1->son->type));
							}
						}
					}
					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;


				test_var = search_var_in_table(symtab_global, aux_variable->id);

				if (test_var==NULL){
					insert_global(aux_variable);
					create_local(local_table);
				} else if (test_var->function != 1) { // if already exists
					if (test_var->n_params!=count_params){
						/*printf("Line %d, col %d: Wrong number of arguments to function %s ( got %d,required %d)", 0, 0, aux_variable->id, count_params, test_var->n_params);*/
					}
				}

			}
			else if (strcmp(actual_node->type, "Declaration") == 0) {
				/*if (strcasecmp(actual_node->son->type, "Void") == 0 ){ // ERROR
					printf("Line %d, col %d: Invalid use of void type in declaration\n", aux1->son->line, aux1->son->col);
				} else*/ {
					aux_variable = create_var(actual_node->son->brother->id, actual_node->son->type);
					if (search_var_in_table(symtab_global, actual_node->son->brother->id)==NULL){
						insert_global(aux_variable);
					}
				}
			}
			else if (strcmp(actual_node->type, "FuncDeclaration") == 0) {
				aux = actual_node->son;
				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type); // adiciona à tabela local com variables a null

				aux_variable->function = 0;
				aux1 = aux->brother->son->brother->son;

				while (aux1!=NULL){
					count_params = 0;
					if (aux1->son->brother==NULL){
							aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));
					} else {
						//verificar se existe
						if (search_param_in_params(aux_variable->parameters, aux1->son->brother->id)!=NULL){
						} else {
							/*printf("%s\n",aux1->son->type );
							if (strcasecmp(aux1->son->type, "Void") == 0){ // ERROR
								printf("Line %d, col %d: Invalid use of void type in declaration\n", aux1->son->line, aux1->son->col);
							}*/
							aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param(aux1->son->brother->id, aux1->son->type));
						}
					}

					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;

				test_var = search_var_in_table(symtab_global, aux_variable->id);

				if (test_var==NULL){
					insert_global(aux_variable);
					create_local(local_table);
				} else { // if already exists
					/*if (test_var->n_params!=count_params){
						printf("Line %d, col %d: Wrong number of arguments to function %s ( got %d,required %d)", 0, 0, aux_variable->id, count_params, test_var->n_params);
					}*/
				}
			}


			aux_program = aux_program->brother;
		}

		aux_program = program->son;

		while (aux_program!=NULL)
		{
			actual_node = aux_program;

			if ( strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition
				aux = actual_node->son; //TYPE
				local_table = create_table(aux->brother->son->id, aux->type);
				test_table = search_func_in_table(local_table->tableName);

				if (test_table==NULL){
					create_local(local_table);
				} else { // if already exists
					if (test_table->variables==NULL){
						local_table = test_table; // é capaz de dar erro
					}
					/*if (test_var->n_params!=count_params){
						printf("Line %d, col %d: Wrong number of arguments to function %s ( got %d,required %d)", 0, 0, local_table->tableName, count_params, test_var->n_params);
					}*/
				}

				// adicionar parâmetros

				aux1 = aux->brother->son->brother->son;
				aux_variable = create_var("return", aux->type);

				local_table->variables = aux_variable;

				while (aux1!=NULL){

					count_params = 0;

					if (aux1->son->brother!=NULL){

						if (search_param_in_params(local_table->parameters, aux1->son->brother->id)!=NULL){
						} else {
							//printf("%s\n",aux1->son->type );
							/*if (strcasecmp(aux1->son->type, "Void") == 0){ // ERROR
								printf("Line %d, col %d: Invalid use of void type in declaration\n", aux1->son->line, aux1->son->col);
							}*/
							local_table->parameters = add_to_paramList(local_table->parameters, create_param(aux1->son->brother->id, aux1->son->type));
						}
					}

					count_params++;
					aux1 = aux1->brother;
				}

				aux = aux->brother->brother; //FuncBody

				if (strcmp(aux->type, "FuncBody") == 0){
					aux1 = aux->son;

					while (aux1!=NULL){

						if (strcmp(aux1->type, "Declaration") == 0) {
							aux2 = aux1->son;
							aux_variable = add_to_varList(aux_variable, create_var(aux2->brother->id, aux2->type));
						} else if(strcmp(aux1->type, "Store") == 0 && atoi(aux1->son->id)!=0) {
							printf("Line %d, col %d: Lvalue required\n", aux1->son->line, aux1->son->col);
						} // ver que, se for uma situação em que uma variável esteja a ser utilizada, se esta existe na tabela
						else if (0) { // testar se for alguma das expressions
						}


						aux1 = aux1->brother;
					}

				}

				// MUDAR
				/*if (test_var!=NULL){
					printf("got %d,required %d\n", count_params, test_var->n_params);
				} else {
					printf("sou null\n");
				}*/
			}

			aux_program = aux_program->brother;
		}

	}
}

void create_local(table_element* newLocal){ // adiciona ao fim da tabela local
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
	printf("putchar\tint(int)\ngetchar\tint(void)\n");

	if (symtab_global!=NULL){
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

table_element *search_func_in_table (char* funcName){
	table_element* aux_table;

	aux_table = symtab_local;

	while (aux_table!=NULL){
		if (strcmp(aux_table->tableName, funcName) == 0)
			return aux_table;

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
		if (current_table->variables!= NULL){
			printf("===== Function %s Symbol Table =====\n", current_table->tableName);

			aux = current_table->variables;
			if (strcmp(aux->id, "return") ==0 ){
				printf("%s\t%s\n", aux->id, aux->type);
				aux=aux->next;
			}

			for (aux1=current_table->parameters; aux1; aux1=aux1->next){
				printf("%s\t%s\tparam\n", aux1->id, aux1->type);
			}


			for(; aux; aux=aux->next){
					printf("%s\t%s\n", aux->id, aux->type);
			}
			printf("\n");
		}
		current_table = current_table->next;
	}
}
