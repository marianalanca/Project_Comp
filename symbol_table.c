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
	int void_flag_col, void_flag_line;

	program = root;

	if (program == NULL){
		return; // termina se vazia
	}

	if( strcmp(program->type, "Program") == 0 ){ // se for um program

		aux_program = program->son;

		symtab_global = create_table("Global", "Global");

        //aux_variable = create_var("putchar", "int");
        //aux_variable->function = 1;
        //insert_global(aux_variable);
        //aux_variable->n_params =1;
        //add_to_paramList(aux_variable->parameters, create_param("", "int"));
        //local_table = create_table("putchar", "int");
        //create_local(local_table);


        //insert_global(create_var("getchar", "int"));

		while (aux_program!=NULL)
		{
			actual_node = aux_program;

			if (strcmp(actual_node->type, "FuncDefinition") == 0 ) { // se for do tipo FuncDefinition
				void_flag_col = 0;
				void_flag_line = 0;
				count_params = 0;

				aux = actual_node->son;
				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type);

				test_var = search_var_in_table(symtab_global, aux_variable->id);

				aux_variable->function = 1;

				aux1 = aux->brother->son->brother->son;

				while (aux1!=NULL){

					if (strcmp(aux1->son->type, "Void") == 0) {
						void_flag_line =  aux1->son->line;
						void_flag_col = aux1->son->col;
					}
					aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));

					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;

				if (void_flag_line && void_flag_col && count_params>1){
					printf("Line %d, col %d: Invalid use of void type in declaration\n", void_flag_line, void_flag_col);
				} else {
					if (test_var==NULL){
						insert_global(aux_variable);
						create_local(local_table);
					} else if (test_var->function == 1){
						if (test_var->n_params!=count_params){
							printf("Line %d, col %d: Wrong number of arguments to function %s ( got %d,required %d)\n", 0, 0, aux_variable->id, count_params, test_var->n_params);
						} else {
							printf("Line %d, col %d: Symbol %s already defined\n", aux->brother->son->line, aux->brother->son->col, aux->brother->son->id);
						}
					}
				}
			}
			else if (strcmp(actual_node->type, "Declaration") == 0) {
				if (strcasecmp(actual_node->son->type, "Void") == 0 ){ // ERROR
					printf("Line %d, col %d: Invalid use of void type in declaration\n", actual_node->son->line, actual_node->son->col);
				} else {
					aux_variable = create_var(actual_node->son->brother->id, actual_node->son->type);
					if (search_var_in_table(symtab_global, actual_node->son->brother->id)==NULL){
						insert_global(aux_variable);
					} else {
						printf("Line %d, col %d: Symbol %s already defined\n", actual_node->son->brother->line, actual_node->son->brother->col, actual_node->son->brother->id);
					}
				}
			}
			else if (strcmp(actual_node->type, "FuncDeclaration") == 0) {
				void_flag_col = 0;
				void_flag_line = 0;
				count_params = 0;

				aux = actual_node->son;

				aux_variable = create_var(aux->brother->son->id, aux->type);
				local_table = create_table(aux->brother->son->id, aux->type); // adiciona à tabela local com variables a null

				test_var = search_var_in_table(symtab_global, aux_variable->id);

				aux1 = aux->brother->son->brother->son;

				aux_variable->function = 0;

				while (aux1!=NULL){

					if (strcmp(aux1->son->type, "Void") == 0) {
						void_flag_line =  aux1->son->line;
						void_flag_col = aux1->son->col;
					}
					aux_variable->parameters = add_to_paramList(aux_variable->parameters, create_param("", aux1->son->type));

					aux1 = aux1->brother;
					count_params++;
				}

				aux_variable->n_params = count_params;

				if (void_flag_line && void_flag_col && count_params>1){
					printf("Line %d, col %d: Invalid use of void type in declaration\n", void_flag_line, void_flag_col);
				} else {
					if (test_var==NULL){
						insert_global(aux_variable);
						create_local(local_table);
					} else { // if already exists
						if (test_var->n_params!=count_params){
							printf("Line %d, col %d: Wrong number of arguments to function %s ( got %d,required %d)\n", 0, 0, aux_variable->id, count_params, test_var->n_params);
						} else {
							printf("Line %d, col %d: Symbol %s already defined\n", aux->brother->son->line, aux->brother->son->col, aux->brother->son->id);
						}
					}
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
				} 
                else { // if already exists
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

					if (aux1->son->brother!=NULL){

						if (search_param_in_params(local_table->parameters, aux1->son->brother->id)!=NULL){
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
                        } /*else if(strcmp(aux1->type, "Store") == 0 && atoi(aux1->son->id)!=0) {
							printf("Line %d, col %d: Lvalue required\n", aux1->son->line, aux1->son->col);
						} // ver que, se for uma situação em que uma variável esteja a ser utilizada, se esta existe na tabela
						else if (0) { // testar se for alguma das expressions
						}*/
						
                        if(aux1->type!=NULL){
                            if(strcmp(aux1->type, "Declaration")==0){
                                aux2 = aux1->son->brother->brother;
                                while(aux2 != NULL){
                                    if( aux2 != NULL && aux2->type != NULL){
                                        anote_ast(symtab_global, local_table, aux2); 
                                    }
                                    aux2 = aux2->brother;
                                }    
                            }
                            else{
                                anote_ast(symtab_global, local_table, aux1);
                            }
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
		aux_var_list = aux_table->variables;
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

var_list *search_type_var(table_element *table_global, table_element *table_local, char *var_name){
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

int count_params;

void anote_ast(table_element *table_global, table_element *table_local, node *atual){
	
	//var_list  *aux;
    char* aux = NULL;
    char* aux_params_type, final_params_type;

    var_list *aux_vars;

	param_list *aux_param;
    param_list *aux_params, *final_params;

    //int count_params;
    int count_equals, count_all_equals, find_function;

    node *aux1, *aux2, *aux3, *ant;

    if(atual == NULL){ //arvore vazia
        return;
    }

    if(atual->type == NULL){    
        
        aux1 = atual->son;
        
        while(aux1 != NULL){
            if(aux1->type != NULL){
                count_params++;
            }
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        return;
    }

    if(strcmp(atual->type, "NULL") == 0){ //nós de erro
        return;
    }
    else if(strcmp(atual->type, "Id") == 0){ //ID
		//printf("id - quase certo\n");

        aux_vars = search_type_var(table_global, table_local, atual->id);
		aux_param = search_param_in_table(table_local,atual->id);

        if(aux_vars != NULL){
            atual->anoted = aux_vars->type;
        }
		else if(aux_param != NULL){
			atual->anoted = aux_param->type;
		}
        else{//erro 8 - Unknown symbol <token >
            printf("Line %d, col %d: Cannot find symbol %s\n", atual->line, atual->col, atual->id);
            atual->anoted = "undef";
        }
    }
    else if(strcmp(atual->type, "If") == 0){
		//printf("if\n");

        aux1 = atual->son;
        anote_ast(table_global, table_local, aux1);
        aux1 = aux1->brother;

        /*
        aux2 = atual->son;
        if(strcmp(aux2->anoted, "boolean")){
            printf("Line %d, col %d: Incompatible type %s in if statement\n", aux2->line, aux2->col, aux2->anoted);
        }*/
		
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->type, "While") == 0){
		//printf("while\n");

        aux1 = atual->son;
        anote_ast(table_global, table_local, aux1);
        aux1 = aux1->brother;

        /*
        aux2 = atual->son;
        if(strcmp(aux2->anoted, "boolean")){
            printf("Line %d, col %d: Incompatible type %s in while statement\n", aux2->line, aux2->col, aux2->anoted);
            atual->anoted = "undef";
        }
        else{
            atual->anoted = "boolean";
        }*/


        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
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
        if(aux2 != NULL){
            if(strcmp(table_local->variables->type, "void") == 0){ //Tem filhos, portanto nao pode ser void!
                printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->col, aux2->anoted);
            }
            else if(strcmp(table_local->variables->type, aux2->anoted) == 0){//Okay
                return;
            }
            else if(strcmp(table_local->variables->type, "double") == 0){ //???
                if(strcmp(aux2->anoted, "int")!=0 && strcmp(aux2->anoted, "double")!=0 && strcmp(aux2->anoted, "short")!=0){
                    printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->col, aux2->anoted);
                }
            }
            else{
                printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->col, aux2->anoted);
            }
        }
        /*
        else{
            if(strcmp(table_local->variables->type, "void")){ //Se nao tem filhos deve ser void!
                printf("Line %d, col %d: Incompatible type void in return statement\n",  atual->line, atual->col);
            }//no nosso projeto este erro nao existe
        }*/
    }
    else if(strcmp(atual->type, "Store") == 0){//Store
		//printf("store - certo acho\n");
		
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
		
        aux1 = atual->son;
        aux2 = aux1->brother;

        atual->anoted = aux1->anoted;

        if(strcmp(aux1->anoted, aux2->anoted) == 0 && strcmp(aux1->anoted, "undef") && strcmp(aux1->anoted, "")){
            return;
        }
        else if(strcmp(aux1->anoted, "double") == 0 && strcmp(aux2->anoted, "int") == 0){
            return; //REVER CONDICOES ELSE IF (AS 3)     
        }
        else if(strcmp(aux1->anoted, "double") == 0 && strcmp(aux2->anoted, "short") == 0){
            return;
        }
        else if(strcmp(aux1->anoted, "int") == 0 && strcmp(aux2->anoted, "short") == 0){
            return;
        }
        else if(strcmp(aux2->anoted, "char") == 0){
            return;
        }
        else{//erro 5
            printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->line, atual->col, aux1->anoted, aux2->anoted);
        }
    }
    else if(strcmp(atual->type, "Comma") == 0){
        printf("Comma\n");
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            atual->anoted = aux1->anoted; //Duvida
            aux1 = aux1->brother;
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
                    aux1 = aux1->brother;
                }

                if( count_params == 1){
                    //correto
                }
                else{
                    //incorreto
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
                    aux1 = aux1->brother;
                }

                if( count_params == 1){
                    //correto
                }
                else{
                    //incorreto
                }
                atual->son->n_params = 1;
                atual->son->params = create_param("", "int"); //tecnicamente
                atual->son->anoted = "int";
                atual->anoted = atual->son->anoted;

                return;
            }
        
        }

        aux1 = (atual->son)->brother;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
        
        if(atual->son != NULL){
            atual->son->n_params = count_params;
            atual->son->params = search_func_in_table(atual->son->id)->parameters;
            atual->anoted = atual->son->anoted; //duvida
        }   
        
		/*
        aux_vars = table_global->variables;
        while(aux_vars != NULL){
            count_equals = 0;
            count_all_equals = 0;
            //e funcao, tem o msm numero de parametros e o msm nome
            if(aux_vars->function && aux_vars->n_params == count_params && strcmp(aux_vars->id, atual->son->id)){
                //aux_params_type = aux_vars->type;
                aux1 = (atual->son)->brother;
                while(aux1 != NULL){
                    if(aux1->type != NULL){
                        if(strcmp(aux_vars->type, aux1->anoted)==0){
                            count_all_equals++;
                            count_equals++;
                        }
                        else if(strcmp(aux1->anoted, "int") == 0 && strcmp(aux_vars->type, "double")==0){
                            count_equals++;
                        }
                        else{
                            break;
                        }
                        aux_params = aux_params->next;
                    }
                    aux1 = aux1->brother;
                }
                if(count_all_equals == count_params){
                    find_function = 1;
                    aux = aux_vars->type;
                    final_params_type = aux_vars->type;
                    break;
                }
                else if(count_equals == count_params){
                    aux = aux_vars->type;
                    final_params_type = aux_vars->type;
                    find_function++;
                }
            }
            aux_vars = aux_vars->next;
        }*/
        /*
        if(find_function == 1){
            atual->son->n_params = count_params;
            if(final_params == NULL){
                atual->son->params = NULL;
            }
            else{
                atual->son->params = final_params;
            }
            atual->anoted = aux;
        }
        else if(find_function > 1){
            printf("Line %d, col %d: Reference to method %s(", atual->son->line, atual->son->col, atual->son->id);     
            aux1 = (atual->son)->brother;
            while(aux1 != NULL){
                if(strcmp(aux1->type, "NULL")){
                    printf("%s", aux1->anoted);
                    if(aux1->brother != NULL){
                        printf(",");
                    }
                }
                aux1 = aux1->brother;
            }
            printf(") is ambiguous\n");
            atual->anoted = "undef";
            atual->son->anoted = "undef";
        }
        else{
            atual->son->anoted = "undef";
            atual->son->params = NULL;
            atual->anoted = "undef";
            //erro 8 - Unknown symbol <token >
            printf("Line %d, col %d: Cannot find symbol %s(", atual->son->line, atual->son->col, atual->son->id);     
            aux1 = (atual->son)->brother;
            while(aux1 != NULL){
                if(strcmp(aux1->type, "NULL")){
                    printf("%s", aux1->anoted);
                    if(count_params != 1){
                        printf(",");
                    }
                    count_params--;
                }
                aux1 = aux1->brother;
            }
            printf(")\n");
        }*/
    }
    else if(strcmp(atual->type, "And") == 0 || strcmp(atual->type, "Or") == 0){
        printf("and-or\n");
		
		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
		/*
        aux2 = atual->son;
        aux3 = aux2->brother;*/
        /*
        if(strcmp(aux2->anoted, "boolean") && strcmp(atual->type, "And") == 0){
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->col, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux2->anoted, "boolean") && strcmp(atual->type, "Or") == 0){
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->col, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "boolean") && strcmp(atual->type, "And") == 0){
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->col, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "boolean") && strcmp(atual->type, "Or") == 0){
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->col, aux2->anoted, aux3->anoted);
        }*/

        //atual->anoted = "boolean";
    }
    else if(strcmp(atual->type, "BitWiseAnd") == 0 || strcmp(atual->type, "BitWiseOr") == 0 || strcmp(atual->type, "BitWiseXor") == 0){
        //printf("bitwise\n");
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
        atual->anoted = "int";
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
        /*
        aux2 = atual->son;
        aux3 = aux2->brother;

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

        /*
        if(strcmp(atual->type, "Eq") == 0 || strcmp(atual->type, "Neq") == 0){
            if(strcmp(aux2->anoted, "boolean") == 0 && strcmp(aux3->anoted, "boolean") == 0){
                return;
            }
        }

        if(strcmp(aux2->anoted, "int") && strcmp(aux2->anoted, "double")){
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "double") && strcmp(aux3->anoted, "int")){
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
        }*/
    }
    else if(strcmp(atual->type, "Add") == 0 || strcmp(atual->type, "Sub") == 0 || strcmp(atual->type, "Mul") == 0
        || strcmp(atual->type, "Div") == 0 || strcmp(atual->type, "Mod") == 0){
		//printf("cenas2 - certo\n");
		
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
		
        aux2 = atual->son;
        aux3 = aux2->brother;

        
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
		
        if(strcmp(aux2->anoted, "int")==0){
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
                atual->anoted = "int"; //duvida??
            }
            else{
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
        }
        else if(strcmp(aux2->anoted, "double")==0){
            if(strcmp(aux3->anoted, "int")!=0 || strcmp(aux3->anoted, "short")!=0 || strcmp(aux3->anoted, "double")!=0){
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
            else{
                atual->anoted = "double";
            }
        }
        else if(strcmp(aux2->anoted, "short")==0){
             if(strcmp(aux3->anoted, "short")==0){
                atual->anoted = "short";
            }
            else if(strcmp(aux3->anoted, "double")==0){
                atual->anoted = "double";
            }
            else if(strcmp(aux3->anoted, "int")==0){
                atual->anoted = "int";
            }
            else{
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->col, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
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

        free(aux);
        aux = NULL;
    }
    else if(strcmp(atual->type, "Plus") == 0 || strcmp(atual->type, "Minus") == 0){
        printf("plus-minus\n");
		
		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
		
        aux1 = atual->son;
        atual->anoted = aux1->anoted;
        if(strcmp(aux1->anoted, "int") == 0 || strcmp(aux1->anoted, "short") == 0 || strcmp(aux1->anoted, "double") == 0 || strcmp(aux1->anoted, "char") == 0){
            atual->anoted = aux2->anoted;
        }
        else{
            atual->anoted = "undef";
            if(strcmp(atual->type, "Plus") == 0){
                printf("Line %d, col %d: Operator + cannot be applied to type %s\n", atual->line, atual->col, aux1->anoted);
            }
            else{
                printf("Line %d, col %d: Operator - cannot be applied to type %s\n", atual->line, atual->col, aux1->anoted);
            }
        }
    }
    else if(strcmp(atual->type, "Not") == 0){
        printf("not\n");
		
		aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        atual->anoted = "int";
		/*
        aux2 = atual->son;
        
        if(strcmp(aux2->anoted, "boolean")){
            printf("Line %d, col %d: Operator ! cannot be applied to type %s\n", atual->line, atual->col, aux2->anoted);
        }*/

    }
    else if(strcmp(atual->type, "IntLit") == 0){ 
        atual->anoted = "int";
    }
    else if(strcmp(atual->type, "ChrLit") == 0){ 
        atual->anoted = "int";
    }
    else if(strcmp(atual->type, "RealLit") == 0){
		atual->anoted = "double";
    }
    else if(strcmp(atual->type, "StatList") == 0){
        aux1 = atual->son;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
}

int itsExpression(char *type){
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

    if(node->type == NULL){ //caso o nó for Null (error) imprimimos o irmão
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
            if(node->n_params >=0 && itsExpression(node->type) == 1){
                printf("(%s) - %s(", node->id, node->anoted);
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
            else if(node->anoted != NULL && itsExpression(node->type) == 1){
                printf("(%s) - %s", node->id, node->anoted);
            }
            else{
                printf("(%s)", node->id);
            }
        }
        else{
            if(node->anoted != NULL && itsExpression(node->type) == 1){
                printf(" - %s", node->anoted);
            }
        }

        //printf(" %d %d", node->line, node->colunm);

        printf("\n");
    }
    
    printAnotedAST(node->son, depth+1);
    printAnotedAST(node->brother, depth);
}

