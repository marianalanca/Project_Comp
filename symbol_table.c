#include "symbol_table.h"

table_element* create_table(char* tableName, char* tableType){ // se local é 1

	table_element* newTable = (table_element*)malloc(sizeof(table_element));

	newTable->tableName = (char*)strdup(tableName);
    newTable->tableType = (char*)strdup(tableType);
	newTable->tableType[0] = tolower(tableType[0]);

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
	int void_flag_col, void_flag_line, void_flag_first;
    int error_flag_col, error_flag_line;
    char* aux_char = (char*) malloc(20);

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
				void_flag_col = 0;
				void_flag_line = 0;
				count_params = 0;
                error_flag_line = 0;
                error_flag_col = 0;
                void_flag_first = 0;

				aux = actual_node->son;
				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type);

				test_var = search_var_in_table(symtab_global, aux_variable->id);

				aux_variable->function = 1;

				aux1 = aux->brother->son->brother->son;
                void_flag_first = 0;

				while (aux1!=NULL){

					if (strcmp(aux1->son->type, "Void") == 0 && void_flag_first == 0) {
						void_flag_line =  aux1->son->line;
						void_flag_col = aux1->son->col;
                        void_flag_first = 1;
					}
                    else if (strcmp(aux1->son->type, "Void") == 0) {
                        local_table->parameters = add_to_paramList(local_table->parameters, create_param("", aux1->son->type));
                    }

                    if (aux1->son->brother!=NULL && strcmp(aux1->son->type, "Void") == 0){
                        error_flag_line =  aux1->son->line;
						error_flag_col = aux1->son->col;
                    }

					aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));

					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;

				if (void_flag_line && void_flag_col && count_params>1){
					printf("Line %d, col %d: Invalid use of void type in declaration\n", void_flag_line, void_flag_col);
				} else if (error_flag_col && error_flag_line){
                    printf("Line %d, col %d: Invalid use of void type in declaration\n", error_flag_line, error_flag_col);
                } else {
					if (test_var==NULL){
						insert_global(aux_variable);
						create_local(local_table);
					}
				}

                //TESTEEEEEEEEEEEEEEEEEEE
                aux = actual_node->son; //TYPE
				local_table = create_table(aux->brother->son->id, aux->type);
				test_table = search_func_in_table(local_table->tableName);

				if (test_table!=NULL){
                    local_table = test_table;
                    if (test_table->exists==1){
                        printf("Line %d, col %d: Symbol %s already defined\n",aux->brother->son->line, aux->brother->son->col, test_table->tableName);
                    } else {
                        aux1 = aux->brother->son->brother->son;
				        aux_variable = create_var("return", aux->type);

                        local_table->variables = aux_variable;
                        local_table->exists = 1;
                        test_table->exists = 1;

                        count_params = 0;

                        while (aux1!=NULL){
                            if (aux1->son->brother!=NULL){
                                local_table->parameters = add_to_paramList(local_table->parameters, create_param(aux1->son->brother->id, aux1->son->type));
                            } else if (strcmp(aux1->son->type, "Void") == 0) {
                                local_table->parameters = add_to_paramList(local_table->parameters, create_param("", aux1->son->type));
                            }

                            count_params++;
                            aux1 = aux1->brother;
                        }

                        local_table->n_params=count_params;
                        aux = aux->brother->brother; //FuncBody

                        if (strcmp(aux->type, "FuncBody") == 0){
                            aux1 = aux->son;

                            while (aux1!=NULL){
                                if(aux1->type!=NULL){
                                    if(strcmp(aux1->type, "Declaration")==0){
                                        aux2 = aux1->son;
                                        if (search_var_in_variables(aux_variable, aux2->brother->id) == NULL && search_param_in_params(local_table->parameters, aux2->brother->id) == 0){ // procura var na funcao e nos parametros
                                            // testar se é do tipo void!
                                            if (strcmp(aux2->type, "Void") == 0){
                                                printf("Line %d, col %d: Invalid use of void type in declaration\n", aux2->brother->line, aux2->brother->col);
                                            } else {
                                                aux_variable = add_to_varList(aux_variable, create_var(aux2->brother->id, aux2->type));
                                            }
                                        } else {
                                            printf("Line %d, col %d: Symbol %s already defined\n",aux2->brother->line, aux2->brother->col,  aux2->brother->id);
                                        }
                                    }
                                }
                                aux1 = aux1->brother;
                            }

                            //teste - duvida

                            aux1 = aux->son;

                            while (aux1!=NULL){
                                if(aux1->type!=NULL){
                                    if(strcmp(aux1->type, "Declaration")==0){

                                        aux2 = aux1->son->brother->brother;

                                        while(aux2 != NULL){
                                            if( aux2 != NULL && aux2->type != NULL){
                                                anote_ast(symtab_global, local_table, aux2);
                                            }
                                            aux2 = aux2->brother;
                                        }
                                        if (aux1->son!=NULL){
                                            //printf("#DEBUG 168: %s\n", aux1->son->anoted);
                                        }
                                    }
                                    else{
                                        anote_ast(symtab_global, local_table, aux1);
                                    }
                                }
                                aux1 = aux1->brother;
                            }
                        }
                    }
				}


			}
			else if (strcmp(actual_node->type, "Declaration") == 0) {
                if (strcasecmp(actual_node->son->type, "Void") == 0 ){ // ERROR
                if (actual_node->son->col == 1){
                        printf("Line %d, col %d: Invalid use of void type in declaration\n", actual_node->son->line, actual_node->son->col + 5);
                    } else {
                        printf("Line %d, col %d: Invalid use of void type in declaration\n", actual_node->son->line, actual_node->son->col);
                    }
				} else {
					aux_variable = create_var(actual_node->son->brother->id, actual_node->son->type);
                    test_var = search_var_in_table(symtab_global, actual_node->son->brother->id);
					if (test_var==NULL){
						insert_global(aux_variable);
					}
				}
                // teste - duvida
                aux = actual_node->son->brother;
                if(aux != NULL){
                    aux= aux->brother;

                    while(aux != NULL){
                        if( aux->type != NULL){
                            anote_ast(symtab_global, symtab_global, aux);
                        }
                        aux = aux->brother;
                    }
                }
                aux = NULL;
                if (actual_node->son->brother->brother!=NULL && actual_node->son->brother->brother->anoted!=NULL){
                    if (strcmp(actual_node->son->brother->brother->anoted, "void") == 0  || strcmp(actual_node->son->brother->brother->anoted, "undef") == 0 ||
                        (strcmp(actual_node->son->brother->brother->anoted, "double") == 0 && strcasecmp(actual_node->son->brother->brother->anoted, actual_node->son->type) != 0)){
                            aux_char = strdup(actual_node->son->type);
                            aux_char[0] = tolower(actual_node->son->type[0]);
                            printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", actual_node->son->brother->line, actual_node->son->brother->col, actual_node->son->brother->brother->anoted, aux_char);
                            memset(aux_char, 0, 20);
                    }
                }
			}
			else if (strcmp(actual_node->type, "FuncDeclaration") == 0) {
				void_flag_col = 0;
				void_flag_line = 0;
				count_params = 0;
                error_flag_line = 0;
                error_flag_col = 0;
                void_flag_first = 0;

				aux = actual_node->son;

				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type); // adiciona à tabela local com variables a null

				test_var = search_var_in_table(symtab_global, aux_variable->id);

				aux1 = aux->brother->son->brother->son;

				aux_variable->function = 0;

				while (aux1!=NULL){

					if (strcmp(aux1->son->type, "Void") == 0 && void_flag_first == 0) {
						void_flag_line =  aux1->son->line;
						void_flag_col = aux1->son->col;
                        void_flag_first = 1;
					}

                    if (aux1->son->brother!=NULL && strcmp(aux1->son->type, "Void") == 0){
                        error_flag_line =  aux1->son->line;
						error_flag_col = aux1->son->col;
                    }

					aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));

					aux1 = aux1->brother;
					count_params++;
				}


				aux_variable->n_params = count_params;

				if (void_flag_line && void_flag_col && count_params>1){
					printf("Line %d, col %d: Invalid use of void type in declaration\n", void_flag_line, void_flag_col);
				} else if (error_flag_col && error_flag_line){
                    printf("Line %d, col %d: Invalid use of void type in declaration\n", error_flag_line, error_flag_col);
                } else {
					if (test_var==NULL){
						insert_global(aux_variable);
						create_local(local_table);
					}
				}
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

void show_local_table(){
	var_list *aux;
	param_list * aux1;
	table_element *current_table = symtab_local;

	while (current_table!=NULL)
	{
		if (current_table->variables!=NULL){
			printf("===== Function %s Symbol Table =====\n", current_table->tableName);

			aux = current_table->variables;
			if (strcmp(aux->id, "return") ==0 ){
				printf("%s\t%s\n", aux->id, aux->type);
				aux=aux->next;
			}

			for (aux1=current_table->parameters; aux1; aux1=aux1->next){
                if (strcmp(aux1->type, "void") != 0)
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

var_list *search_var_in_table (table_element* symtab, char* str){

	table_element* aux_table;
	var_list * aux_var;

	aux_table = symtab;

	while (aux_table!=NULL){
        aux_var = search_var_in_variables(aux_table->variables, str);
		if (aux_var!=NULL) {
            return aux_var;
        }
		aux_table=aux_table->next;
	}
	return NULL;
}

var_list *search_var_in_variables (var_list* list, char* str){

	var_list * aux_var_list = list;

	while (aux_var_list!=NULL){
        if (strcmp(aux_var_list->id, str) == 0)
            return aux_var_list;
        aux_var_list = aux_var_list->next;
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

var_list *search_var(table_element *table_global, table_element *table_local, char *var_name){
    var_list *aux = search_var_in_table(table_local, var_name);
    if(aux != NULL){
        return aux;
    }
    aux = search_var_in_table(table_global, var_name);
    if(aux != NULL){
        return aux;
    }
    return NULL;
}

var_list *search_var_teste(table_element *table_global, table_element *table_local, char *var_name){
    var_list *aux;
    table_element *aux_table;

    aux_table = table_local;
    
    if(aux_table != NULL){
        aux = aux_table->variables;
        while(aux != NULL){
            if(strcmp(aux->id, var_name) == 0){
                return aux;
            }
            aux = aux->next;
        }
    }
    
    aux_table = table_global;
    
    if(aux_table != NULL){
        aux = aux_table->variables;
        while(aux != NULL){
            if(strcmp(aux->id, var_name) == 0){
                return aux;
            }
            aux = aux->next;
        }
    }

    return NULL;
}

int count_params;


void anote_ast(table_element *table_global, table_element *table_local, node *atual){

    char* aux = NULL;

    var_list *aux_vars = NULL, *aux_vars_local = NULL;
	param_list *aux_param = NULL;

    node *aux1, *aux2, *aux3;
    table_element * aux_func;

    if(atual == NULL){ //arvore vazia
        return;
    }
    if(atual->type == NULL){
        //printf("NULL\n");

        aux1 = atual->son;

        while(aux1 != NULL){
            if(aux1->type != NULL){
                count_params++;
            }
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        if(atual->son != NULL){
            atual->anoted = atual->son->anoted;
        }

        return;
    }
    if(strcmp(atual->type, "Null") == 0){
        return;
    }
    else if(strcmp(atual->type, "Id") == 0){ //ID
		//printf("id\n");

        aux_vars = search_var_teste(table_global, table_local, atual->id);
		aux_param = search_param_in_params (table_local->parameters, atual->id);
        aux_func = search_func_in_table(atual->id);

        if(aux_param != NULL){
			atual->anoted = aux_param->type;
		}
        else if(aux_vars != NULL){
            atual->anoted = aux_vars->type;
            if(aux_func != NULL){
                atual->params = aux_vars->parameters;
                atual->n_params = 0;
            }
        }
        else{//erro 8 - Unknown symbol <token >
            printf("Line %d, col %d: Unknown symbol %s\n", atual->line, atual->col, atual->id);
            atual->anoted = "undef";
        }
    }
    else if(strcmp(atual->type, "If") == 0){
		//printf("if\n");

        aux1 = atual->son;

        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
        if (atual->son->anoted!=NULL){
            if((strcmp(atual->son->anoted, "int")!= 0 && strcmp(atual->son->anoted, "short")!= 0 && strcmp(atual->son->anoted, "char")!= 0)
                || atual->son->params!=NULL){
                printf("Line %d, col %d: Conflicting types (got %s", atual->son->line, atual->son->col, atual->son->anoted);
                if (atual->son->params!=NULL){
                    printf("(");
                    aux_param = atual->son->params;
                    while(aux_param->next!=NULL){
                        printf("%s, ", aux_param->type);
                        aux_param = aux_param->next;
                    }
                    printf("%s)", aux_param->type);
                }
                printf(", expected int)\n");
            }
        }
    }
    else if(strcmp(atual->type, "While") == 0){
		//printf("while\n");

        aux1 = atual->son;
        anote_ast(table_global, table_local, aux1);
        aux1 = aux1->brother;

        //atual->anoted = "int";

        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        if (atual->son->anoted!=NULL){
            if((strcmp(atual->son->anoted, "int")!= 0 && strcmp(atual->son->anoted, "short")!= 0 && strcmp(atual->son->anoted, "char")!= 0)
                || atual->son->params!=NULL){
                printf("Line %d, col %d: Conflicting types (got %s", atual->son->line, atual->son->col, atual->son->anoted);
                if (atual->son->params!=NULL){
                    printf("(");
                    aux_param = atual->son->params;
                    while(aux_param->next!=NULL){
                        printf("%s, ", aux_param->type);
                        aux_param = aux_param->next;
                    }
                    printf("%s)", aux_param->type);
                }
                printf(", expected int)\n");
            }
        }
    }
    else if(strcmp(atual->type, "Return") == 0){
		//printf("return\n");

		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->son;
        while (aux2!=NULL && aux2->anoted==NULL){
            aux2 = aux2->son;
        }

        if(aux2 != NULL){
            if (aux2->params!=NULL){
                printf("Line %d, col %d: Conflicting types (got %s",  aux2->line, aux2->col, aux2->anoted);
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
                printf(", expected %s)\n", table_local->variables->type);
            }
            else if(strcmp(table_local->variables->type, aux2->anoted) == 0){
                return;
            }
            else if (strcmp(table_local->variables->type, "void") == 0 && strcmp(aux2->anoted, "undef")!=0){
                printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n",  aux2->line, aux2->col, aux2->anoted, table_local->variables->type);

            }
            else if(strcmp(aux2->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 || strcmp(aux2->anoted, "void")==0){
                printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n",  aux2->line, aux2->col, aux2->anoted, table_local->variables->type);
            }
        }
        else{
            /*printf("Line %d, col %d: Conflicting types (got %s",  atual->line, atual->col, table_local->tableType);
            if (table_local->parameters!=NULL){
                printf("(");
                aux_param = table_local->parameters;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", expected %s)\n", table_local->variables->type);*/


            /*if(strcmp(table_local->variables->type, "void")){
                printf("Line %d, col %d: Incompatible type void in return statement\n",  atual->line, atual->col);
            }*/
        }
    }
    else if(strcmp(atual->type, "Store") == 0){//Store
		//printf("store\n");

        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux1 = atual->son;
        aux2 = aux1->brother;

        while (aux1->anoted==NULL){
            aux1 = aux1->son;
        }
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }

        atual->anoted = aux1->anoted;

        if(aux1->anoted == NULL){
            aux1->anoted = "undef";
            //return;
        } else {
            if (aux1->id==NULL || ( aux1->id!=NULL && atoi(aux1->id)!=0)){
                printf("Line %d, col %d: Lvalue required\n", aux1->line, aux1->col);
            }
        }

        if(aux2->anoted == NULL){
            aux2->anoted = "undef";
            //return;
        }

        if (aux1->params!= NULL || aux2->params!=NULL){
            printf("Line %d, col %d: Operator = cannot be applied to types ", atual->line, atual->col);
            printf("%s", aux1->anoted);
            if (aux1->params!=NULL){
                printf("(");
                aux_param = aux1->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        } else if(strcmp(aux2->anoted, "undef")==0 || strcmp(aux1->anoted, "undef")==0 ||
            strcmp(aux2->anoted, "void")==0 || strcmp(aux1->anoted, "void")==0 || (strcmp(aux2->anoted, "double")==0 && strcmp(aux1->anoted, "double")!=0)){
                printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->line, atual->col, aux1->anoted, aux2->anoted);
        } else {
            return;
        }
    }
    else if(strcmp(atual->type, "Comma") == 0){
        //printf("Comma\n");

        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            // talvez seja desnecessario
            if(aux1->anoted != NULL){
                atual->anoted = aux1->anoted;
            }
            aux1 = aux1->brother;
        }

        aux2 = atual->son;
        aux3 = aux2->brother;
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }
        while (aux3->anoted==NULL){
            aux3 = aux3->son;
        }
        
        if (aux2->params!= NULL || aux3->params!=NULL){
            printf("Line %d, col %d: Operator , cannot be applied to types ", atual->line, atual->col);
            printf("%s", aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
            atual->anoted = "undef";

        } else if(strcmp(aux2->anoted, "undef")==0 || strcmp(aux3->anoted, "undef")==0){
            printf("Line %d, col %d: Operator , cannot be applied to types %s, %s\n", atual->line, atual->col, aux2->anoted, aux3->anoted);
        }
    }
    else if(strcmp(atual->type, "Call") == 0){//Rever Call
        //printf("call - ainda falta\n");

		count_params = 0;

        if(atual->son != NULL && atual->son->id != NULL){


            //Fazer protecoes!!!!!!!!!!!!!!!!!

            if(strcmp(atual->son->id, "getchar")==0){

                aux1 = (atual->son)->brother;
                while(aux1 != NULL){
                    anote_ast(table_global, table_local, aux1);
                    if (strcmp(aux1->son->anoted, "undef")==0 || strcmp(aux1->son->anoted, "double") == 0 || strcmp(aux1->son->anoted, "void") == 0 ){
                        printf("Line %d, col %d: Conflicting types (got %s, expected int)\n", aux1->son->line, aux1->son->col, aux1->son->anoted); // COLUNA MAL ???
                    }
                    aux1 = aux1->brother;
                }

                if( count_params != 0){
                    printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required 1)\n", atual->line, atual->col, atual->son->id, count_params);
                }

                atual->son->n_params = 1;
                atual->son->params = create_param("", "void"); //tecnicamente
                atual->son->anoted = "int";
                atual->anoted = atual->son->anoted;

                return;
            }

            if(strcmp(atual->son->id, "putchar")==0){

                aux1 = (atual->son)->brother;
                while(aux1 != NULL){
                    anote_ast(table_global, table_local, aux1);
                    if (strcmp(aux1->son->anoted, "undef")==0 || strcmp(aux1->son->anoted, "double") == 0 || strcmp(aux1->son->anoted, "void") == 0 ){
                        printf("Line %d, col %d: Conflicting types (got %s, expected int)\n", aux1->son->line, aux1->son->col, aux1->son->anoted); // COLUNA MAL ???
                    }
                    aux1 = aux1->brother;
                }

                if( count_params != 1){
                    printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required 1)\n", atual->line, atual->col, atual->son->id, count_params);
                }

                atual->son->n_params = 1;
                atual->son->params = create_param("", "int"); //tecnicamente
                atual->son->anoted = "int";
                atual->anoted = atual->son->anoted;

                return;
            }

        }

        if(atual->son != NULL){
            aux_vars = search_var_teste(table_global, table_global, atual->son->id);
            aux_func = search_func_in_table(atual->son->id);

            aux_vars_local = search_var_in_variables(table_local->variables, atual->son->id);

            //printf("DEBUG #741: %s params: %d", aux_func->tableName, aux_func->n_params);

            if(aux_func != NULL){
                if(aux_vars != NULL){
                    atual->son->params = aux_vars->parameters;
                }
                atual->anoted = aux_func->tableType;
                atual->anoted[0] = tolower(atual->anoted[0]);

                atual->son->anoted = atual->anoted;
            }
            else if(aux_vars_local!=NULL){ //muita muita duvida!!!
                atual->n_params = -1;
                atual->anoted = aux_vars_local->type;
                atual->son->anoted = aux_vars_local->type;
            }
            else{ //a funcao nao existe
                atual->anoted = "undef";
                atual->son->anoted = "undef";
                // procura nas variáveis globais -> se existir, é porque é variável logo está mal; se não, não existe
                if (search_var_in_table(symtab_global, atual->son->id) != NULL){ // se não existe na local, mas existe na global, é porque não é função, mas variável
                    printf("Line %d, col %d: Symbol %s is not a function\n", atual->line, atual->col, atual->son->id);
                }
            }


            aux1 = (atual->son)->brother;
            int aux_counter = 0;

            if (aux1!=NULL){
                aux1 = aux1->son;

                //printf("atual: %s\n",atual->son->id);

                while(aux1 != NULL){
                anote_ast(table_global, table_local, aux1); //duvida

                aux_counter++;
                aux1 = aux1->brother;
            }
            }

            atual->son->n_params = aux_counter; //verificar numero de parametros
            if (aux_func!=NULL){
                if ((aux_vars->n_params == 1 && strcmp(aux_vars->parameters->type, "void") == 0)){
                    if (atual->son->n_params!=0 || (atual->son->n_params==1 && strcmp(atual->son->params->type, "void") != 0)){ // RETHINK
                        printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required 0)\n", atual->son->line, atual->son->col, aux_func->tableName, atual->son->n_params);
                    }
                } else if (atual->son->n_params != aux_vars->n_params){
                    printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required %d)\n", atual->son->line, atual->son->col, aux_func->tableName, atual->son->n_params, aux_vars->n_params);
                } else {
                    aux1 = (atual->son)->brother;
                    if (aux1!=NULL){
                        aux1 = aux1->son;

                        if (aux_vars!=NULL && aux_func!=NULL)
                            aux_param = aux_vars->parameters;

                        //printf("atual: %s\n",atual->son->id);

                        while(aux1 != NULL){

                        if (aux_param!=NULL){

                            //printf("DEBUG: func %s: param (%d) type: %s\n", table_local->tableName, table_local->n_params, aux_param->type);
                            //printf("DEBUG: got %s, expected %s\n", aux1->son->anoted, aux_param->type);
                            //printf("DEBUG: %d %d\n", aux1->son->line, aux1->son->col);
                            if (strcmp(atual->anoted, "undef") != 0){
                                if ((strcmp(aux1->anoted, "undef")==0 || strcmp(aux_param->type, "undef")==0)
                                    || ((strcmp(aux1->anoted, "double") == 0 && strcmp(aux_param->type, "double") != 0))
                                    || ((strcmp(aux1->anoted, "void") == 0 && strcmp(aux_param->type, "void") != 0)
                                    || (strcmp(aux_param->type, "void") == 0 && strcmp(aux1->anoted , "void") != 0))){
                                        printf("Line %d, col %d: Conflicting types (got %s, expected %s)\n", aux1->line, aux1->col, aux1->anoted, aux_param->type);
                                }
                            }
                            aux_param = aux_param->next;
                        }
                        aux1 = aux1->brother;
                    }
                    }
                }
            } else {
                printf("Line %d, col %d: Unknown symbol %s\n", atual->line, atual->col, atual->son->id);
                printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required 0)\n", atual->line, atual->col, atual->son->id, atual->son->n_params);
            }
        }
    }
    else if(strcmp(atual->type, "And") == 0 || strcmp(atual->type, "Or") == 0){
        //printf("and-or\n");

		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
        atual->anoted = "int";

        aux2 = atual->son;
        aux3 = aux2->brother;
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }
        while (aux3->anoted==NULL){
            aux3 = aux3->son;
        }

        if((strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 ||
            strcmp(aux3->anoted, "undef")==0 || aux2->params!=NULL || aux3->params!=NULL)  && strcmp(atual->type, "And") == 0){
            printf("Line %d, col %d: Operator && cannot be applied to types %s", atual->line, atual->col, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        }
        else if((strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 ||
        strcmp(aux3->anoted, "undef")==0  || aux2->params!=NULL || aux3->params!=NULL) && strcmp(atual->type, "Or") == 0){
            printf("Line %d, col %d: Operator || cannot be applied to types %s", atual->line, atual->col, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        }

    }
    else if(strcmp(atual->type, "BitWiseAnd") == 0 || strcmp(atual->type, "BitWiseOr") == 0 || strcmp(atual->type, "BitWiseXor") == 0){
        //printf("bitwise\n");
        
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
        atual->anoted = "int";

        aux2 = atual->son;
        aux3 = aux2->brother;
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }
        while (aux3->anoted==NULL){
            aux3 = aux3->son;
        }


        if((strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 ||
        strcmp(aux3->anoted, "undef")==0 || aux2->params!=NULL || aux3->params)  && strcmp(atual->type, "BitWiseAnd") == 0){
            printf("Line %d, col %d: Operator & cannot be applied to types %s", atual->line, atual->col, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        }
        else if((strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 ||
        strcmp(aux3->anoted, "undef")==0 || aux2->params!=NULL || aux3->params) && strcmp(atual->type, "BitWiseOr") == 0){
            printf("Line %d, col %d: Operator | cannot be applied to types %s", atual->line, atual->col, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        }
        else if((strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0 || strcmp(aux2->anoted, "undef")==0 ||
                strcmp(aux3->anoted, "undef")==0 || aux2->params!=NULL || aux3->params) && strcmp(atual->type, "BitWiseXor") == 0){
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s", atual->line, atual->col, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        }
    }
    else if(strcmp(atual->type, "Eq") == 0 || strcmp(atual->type, "Gt") == 0 || strcmp(atual->type, "Ge") == 0
        || strcmp(atual->type, "Le") == 0 || strcmp(atual->type, "Lt") == 0 || strcmp(atual->type, "Ne") == 0){
        //printf("cenas1\n");

        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        atual->anoted = "int";

        aux2 = atual->son;
        aux3 = aux2->brother;
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }
        while (aux3->anoted==NULL){
            aux3 = aux3->son;
        }

        //memset(aux, 0 , sizeof(aux));

        if(strcmp(atual->type, "Eq") == 0){
            aux = "==";
        }
        else if(strcmp(atual->type, "Gt") == 0){
            aux = ">";
        }
        else if(strcmp(atual->type, "Ge") == 0){
            aux = ">=";
        }
        else if(strcmp(atual->type, "Le") == 0){
            aux = "<=";
        }
        else if(strcmp(atual->type, "Lt") == 0){
            aux = "<";
        }
        else if(strcmp(atual->type, "Ne") == 0){
            aux = "!=";
        }

        if(strcmp(aux2->anoted, "undef")==0 || strcmp(aux3->anoted, "undef")==0 || 
            strcmp(aux2->anoted, "void")==0 || strcmp(aux3->anoted, "void")==0 || aux2->params!=NULL || aux3->params!=NULL){
            printf("Line %d, col %d: Operator %s cannot be applied to types %s", atual->line, atual->col, aux, aux2->anoted);
            if (aux2->params!=NULL){
                printf("(");
                aux_param = aux2->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf(", %s", aux3->anoted);
            if (aux3->params!=NULL){
                printf("(");
                aux_param = aux3->params;
                while(aux_param->next!=NULL){
                    printf("%s,", aux_param->type);
                    aux_param = aux_param->next;
                }
                printf("%s)", aux_param->type);
            }
            printf("\n");
        } else {
            return;
        }
    }
    else if(strcmp(atual->type, "Add") == 0 || strcmp(atual->type, "Sub") == 0 || strcmp(atual->type, "Mul") == 0
        || strcmp(atual->type, "Div") == 0 || strcmp(atual->type, "Mod") == 0){
		//printf("contas\n");

        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->son;
        aux3 = aux2->brother;
        while (aux2->anoted==NULL){
            aux2 = aux2->son;
        }
        while (aux3->anoted==NULL){
            aux3 = aux3->son;
        }


        if(aux2->anoted == NULL){
            if(aux2->type == NULL){
                aux2 = aux2->son; //duvida
            }
            else{
                aux2->anoted = "undef";
            }
        }//DUVIDA

        if(aux3->anoted == NULL){
            if(aux3->type == NULL){
                aux3 = aux3->son;  //duvida
            }
            else{
                aux3->anoted = "undef";
            }
        }
        
        if(strcmp(atual->type, "Add") == 0){
            aux = (char*) malloc (sizeof(char)* strlen("+"));
            strcpy(aux, "+");
        }
        else if(strcmp(atual->type, "Sub") == 0){
            aux = (char*) malloc (sizeof(char)* strlen("-"));
            strcpy(aux, "-");
        }
        else if(strcmp(atual->type, "Mul") == 0){
            aux = (char*) malloc (sizeof(char)* strlen("*"));
            strcpy(aux, "*");
        }
        else if(strcmp(atual->type, "Div") == 0){
            aux = (char*) malloc (sizeof(char)* strlen("/"));
            strcpy(aux, "/");
        }
        else{
            aux = (char*) malloc (sizeof(char)* strlen("%"));
            strcpy(aux, "%");
        }

        //DUVIDA
        if (strcmp(aux, "%") == 0) {
            if(strcmp(aux2->anoted, "undef")==0 || strcmp(aux3->anoted, "undef")==0 || 
                strcmp(aux2->anoted, "void")==0 || strcmp(aux3->anoted, "void")==0  ||
                strcmp(aux2->anoted, "double")==0 || strcmp(aux3->anoted, "double")==0){
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
            }
            atual->anoted = "int";
        } else {
            // RETHINK
            if (aux2->params!=NULL || aux3->params!=NULL){
                printf("Line %d, col %d: Operator %s cannot be applied to types ", atual->line, atual->col, aux);
                printf("%s", aux2->anoted);
                if (aux2->params!=NULL){
                    printf("(");
                    aux_param = aux2->params;
                    while(aux_param->next!=NULL){
                        printf("%s,", aux_param->type);
                        aux_param = aux_param->next;
                    }
                    printf("%s)", aux_param->type);
                }
                printf(", %s", aux3->anoted);
                if (aux3->params!=NULL){
                    printf("(");
                    aux_param = aux3->params;
                    while(aux_param->next!=NULL){
                        printf("%s,", aux_param->type);
                        aux_param = aux_param->next;
                    }
                    printf("%s)", aux_param->type);
                }
                printf("\n");
                atual->anoted = "undef";
            }
            else if(strcmp(aux2->anoted, "int")==0){
                if(strcmp(aux3->anoted, "int")==0){
                    atual->anoted = "int";
                }
                else if(strcmp(aux3->anoted, "double")==0){
                    atual->anoted = "double";
                }
                else if(strcmp(aux3->anoted, "short")==0){
                    atual->anoted = "int";
                }
                else if(strcmp(aux3->anoted, "char")==0){
                    atual->anoted = "int";
                }
                else{
                    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                    atual->anoted = "undef";
                }
            }
            else if(strcmp(aux2->anoted, "double")==0){
                if(strcmp(aux3->anoted, "int")!=0 && strcmp(aux3->anoted, "short")!=0 && strcmp(aux3->anoted, "double")!=0 && strcmp(aux3->anoted, "char")!=0){
                    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                    atual->anoted = "undef";//duvida
                }
                else{
                    atual->anoted = "double";
                }
            }
            else if(strcmp(aux2->anoted, "short")==0){
                if(strcmp(aux3->anoted, "int")==0){
                    atual->anoted = "int";
                }
                else if(strcmp(aux3->anoted, "double")==0){
                    atual->anoted = "double";
                }
                else if(strcmp(aux3->anoted, "short")==0){
                    atual->anoted = "short";
                }
                else if(strcmp(aux3->anoted, "char")==0){
                    atual->anoted = "short"; //DUVIDAAA
                }
                else{
                    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                    atual->anoted = "undef"; //duvida
                }
            }
            else if(strcmp(aux2->anoted, "char")==0){
                if(strcmp(aux3->anoted, "char")==0){
                    atual->anoted = "char";
                }
                else{
                    //duvida
                    atual->anoted = aux3->anoted;
                }
            }
            else{
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
        }


        

        free(aux);
        aux = NULL;

    }
    else if(strcmp(atual->type, "Plus") == 0 || strcmp(atual->type, "Minus") == 0){
        //printf("plus-minus\n");

		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
		
        aux1 = atual->son;
        atual->anoted = aux1->anoted;

        if(aux1->anoted == NULL){
            aux1->anoted = "undef";
        }

        if(strcmp(aux1->anoted, "int") == 0 || strcmp(aux1->anoted, "short") == 0 || strcmp(aux1->anoted, "double") == 0 || strcmp(aux1->anoted, "char") == 0){
            atual->anoted = aux1->anoted;
        }
        else{
            if (strcmp(aux1->anoted, "void") == 0){
                atual->anoted= "void";
            } else {
                atual->anoted = "undef"; //duvida
            }
            if(strcmp(atual->type, "Plus") == 0){
                printf("Line %d, col %d: Operator + cannot be applied to type %s\n", atual->line, atual->col, aux1->anoted);
            }
            else{
                printf("Line %d, col %d: Operator - cannot be applied to type %s\n", atual->line, atual->col, aux1->anoted);
            }
        }
    }
    else if(strcmp(atual->type, "Not") == 0){
        //printf("not\n");
		
		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->son;

        if(strcmp(aux2->anoted, "double") ==0 || strcmp(aux2->anoted, "undef") ==0 || strcmp(aux2->anoted, "void") ==0){
            printf("Line %d, col %d: Operator ! cannot be applied to type %s\n", atual->line, atual->col, aux2->anoted);
        } else if (aux2->params!=NULL){
            printf("Line %d, col %d: Operator ! cannot be applied to type %s(", atual->line, atual->col, aux2->anoted);
            aux_param = aux2->params;
            while(aux_param->next!=NULL){
                printf("%s,", aux_param->type);
                aux_param = aux_param->next;
            }
            printf("%s)\n", aux_param->type);
        }

        atual->anoted = "int";

    }
    else if(strcmp(atual->type, "IntLit") == 0){
        //printf("int\n");
        atual->anoted = "int";
    }
    else if(strcmp(atual->type, "ChrLit") == 0){
        //printf("chrlit\n");
        atual->anoted = "int";
    }
    else if(strcmp(atual->type, "RealLit") == 0){
        //printf("realLit\n");
		atual->anoted = "double";
    }
    else if(strcmp(atual->type, "StatList") == 0){
        //printf("StatList\n");
        
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
}

int expression(char *type){
    if(strcmp(type, "Store") == 0 || strcmp(type, "Or") == 0 || strcmp(type, "And") == 0 || strcmp(type, "BitWiseAnd") == 0
        || strcmp(type, "BitWiseOr") == 0 || strcmp(type, "BitWiseXor") == 0 || strcmp(type, "Eq") == 0
        || strcmp(type, "Ne") == 0 || strcmp(type, "Lt") == 0 || strcmp(type, "Ge") == 0
        || strcmp(type, "Add") == 0 || strcmp(type, "Sub") == 0 || strcmp(type, "Mul") == 0
        || strcmp(type, "Div") == 0 || strcmp(type, "Mod") == 0 || strcmp(type, "Not") == 0
        || strcmp(type, "Minus") == 0 || strcmp(type, "Plus") == 0 || strcmp(type, "Comma") == 0
        || strcmp(type, "Call") == 0 || strcmp(type, "Id") == 0 || strcmp(type, "IntLit") == 0
        || strcmp(type, "ChrLit") == 0 || strcmp(type, "RealLit") == 0 || strcmp(type, "Gt") == 0 || strcmp(type, "Le") == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void printAnotedAST(node *node, int depth){
    int i;
    param_list *aux;

    if(node == NULL){ //Arvore vazia
        return;
    }

    if(node->type == NULL){
        printAnotedAST(node->son, depth);
        printAnotedAST(node->brother, depth);
        return;
    }
    else{
        for(i=0; i< depth; i++){
            printf("..");
        }

        printf("%s",node->type);

        if(node->id != NULL){ //ID/INTLIT/CHRLIT/REALLIT
            if(node->anoted != NULL && expression(node->type) == 1){
                printf("(%s) - %s", node->id, node->anoted);
                if(node->n_params >= 0 && strcmp(node->anoted, "undef") != 0){
                    
                    printf("(");
                    
                    aux = node->params;
                    while(aux != NULL){
                        printf("%s", aux->type);
                        if(aux->next != NULL){
                            printf(",");
                        }
                        aux = aux->next;
                    }

                    printf(")");
                }
            }    
            else{
                printf("(%s)", node->id);
            }
        }
        else{
            if(node->anoted != NULL && expression(node->type) == 1){
                printf(" - %s", node->anoted);
            }
        }

        printf("\n");
    }
    
    printAnotedAST(node->son, depth+1);
    printAnotedAST(node->brother, depth);
}

