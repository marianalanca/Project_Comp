/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int flag;
    int errorFlag;

    int yylex (void);
    void yyerror (char const *s) ;

    int commaFlag = 0;

    typedef struct _t1{
        char* id;
        char* type;
        struct _t1* son;
        struct _t1* brother;
    } node;

    node * aux, aux1;

    node * insertNode(char * id, char * type, node * son) {
        node * aux = (node *)malloc(sizeof(node));
        aux->type = type;
        aux->id = id;
        aux->son = son;
        aux->brother = NULL;

        return aux;
    }

    void connectBrothers(node* node1, node* brother){
        if (node1!= NULL)
        node1->brother = brother;
    }

    void print_tree(node* node, int depth){

        if (node != NULL){
            if (node->type!=NULL){
                int i;


                for (i = 0; i < depth; i++){
                    printf("..");
                }
                printf("%s",node->type);
                if (node->id != NULL){
                    printf("(%s)", node->id);
                }
                printf("\n");
            }

            if (node->type==NULL){
                print_tree(node->son, depth);
            } else {
                print_tree(node->son, depth + 1);
            }

            print_tree(node->brother, depth);

            free(node);
        }
    }


%}

%union{
    char * id;
    struct _t1* node;
}

%token CHAR ELSE IF WHILE INT DOUBLE SHORT RETURN VOID BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI
%token <id> CHRLIT ID INTLIT REALLIT RESERVED

%nonassoc   IFX
%nonassoc   ELSE

%left   COMMA
%right  ASSIGN
%left   OR
%left   AND
%left   BITWISEOR
%left   BITWISEXOR
%left   BITWISEAND
%left   EQ NE
%left   LT GT LE GE
%left   PLUS MINUS
%left   DIV MUL MOD
%right  NOT
%left   RPAR LPAR

%start Program

%type <node> Program
%type <node> FunctionsAndDeclarations
%type <node> optFuncAndDec
%type <node> FunctionDefinition
%type <node> FunctionBody
%type <node> DeclarationsAndStatements
%type <node> optDecAndState
%type <node> FunctionDeclaration
%type <node> FunctionDeclarator
%type <node> ParameterList
%type <node> optParamList
%type <node> ParameterDeclaration
%type <node> optParamDec
%type <node> Declaration
%type <node> optDeclaration
%type <node> TypeSpec
%type <node> Declarator
%type <node> OptDeclarator
%type <node> Statement
%type <node> StatementError
%type <node> optExp
%type <node> optState
%type <node> Expr
%type <node> optExpCExp
%type <node> optCExp

%%

Program: FunctionsAndDeclarations                               { $$ = insertNode(NULL, "Program", $1); if (errorFlag != -1 && flag == 2) print_tree($$, 0); }
    | error Program                                             { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL); }
    ;

FunctionsAndDeclarations: FunctionDefinition optFuncAndDec      { if ($2 != NULL) connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }

    | FunctionDeclaration optFuncAndDec                         { if ($2 != NULL) connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }

    | Declaration optFuncAndDec                                 { if ($2 != NULL) connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }
    ;

optFuncAndDec: FunctionsAndDeclarations                         { $$ = $1; }
    | /*epsilon*/                                               { $$ = NULL; }
    ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody    { $$ = insertNode(NULL, "FuncDefinition", $1);
                                                                  connectBrothers($1, $2);
                                                                  connectBrothers($2, $3);
                                                                }
    ;

FunctionBody: LBRACE optDecAndState RBRACE                      { if ($2 != NULL) $$ = insertNode(NULL, "FuncBody", $2); }
    ;

DeclarationsAndStatements: Statement optDecAndState             { if ($2 != NULL) connectBrothers($1, $2); $$ = $1; }
    | Declaration optDecAndState                                { if ($2 != NULL) connectBrothers($1, $2); $$ = $1; }
    ;

optDecAndState: DeclarationsAndStatements                       { $$ = $1; }
    | /*epsilon*/                                               { $$ = NULL; }
    ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI           { $$ = insertNode(NULL, "FuncDeclaration", $1);
                                                                  connectBrothers($1, $2);
                                                                }
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  { aux = insertNode($1, "Id", NULL);
                                                                  connectBrothers(aux, $3);
                                                                  $$ = insertNode(NULL, NULL, aux);
                                                                }
    ;

ParameterList: ParameterDeclaration optParamList                { $$ = insertNode(NULL, "ParamList", $1);
                                                                  if ($2 != NULL) connectBrothers($1, $2);
                                                                }
    ;

optParamList: optParamList COMMA ParameterDeclaration           { if ($1 != NULL) { connectBrothers($1, $3); $$ = $1; } else $$ = $3; }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

ParameterDeclaration: TypeSpec optParamDec                      { $$ = insertNode(NULL, "ParamDeclaration", $1); if ( $2 != NULL) connectBrothers ($1, $2); }
    ;

optParamDec: ID                                                 { $$ = insertNode($1, "Id", NULL); }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            { $$ = insertNode(NULL, "Declaration", $1);
                                                                  connectBrothers($1, $2);
                                                                  if ($3 != NULL) connectBrothers($2, $3);
                                                                }
    | error SEMI                                                { $$ = insertNode(NULL, NULL, NULL);}
    ;

optDeclaration: optDeclaration COMMA Declarator                 { if ($1 != NULL) { connectBrothers($1, $3); $$ = $1; } else $$ = $3; }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

TypeSpec: CHAR                                                  { $$ = insertNode(NULL, "Char", NULL); }
    | INT                                                       { $$ = insertNode(NULL, "Int", NULL); }
    | VOID                                                      { $$ = insertNode(NULL, "Void", NULL); }
    | SHORT                                                     { $$ = insertNode(NULL, "Short", NULL); }
    | DOUBLE                                                    { $$ = insertNode(NULL, "Double", NULL); }
    ;

Declarator: ID OptDeclarator                                    { aux = insertNode($1, "Id", NULL);
                                                                  if ($2 != NULL) connectBrothers(aux, $2);
                                                                  $$ = insertNode(NULL, NULL, aux);

                                                                }
    ;

OptDeclarator: ASSIGN Expr                                      { $$ = $2; }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

Statement: optExp                                               { $$ = $1; }
    | LBRACE optState RBRACE                                    { $$ = insertNode(NULL, "StatList", $2); }

    | RETURN Expr SEMI                                          { $$ = insertNode(NULL, "Return", $2); }
    | RETURN SEMI                                               { $$ = insertNode(NULL, "Return", insertNode(NULL, "Null", NULL)); }

    | IF LPAR Expr RPAR StatementError ELSE StatementError      { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL);
                                                                  }
                                                                  if ($7 == NULL){
                                                                      $7 = insertNode(NULL, "Null", NULL);
                                                                  }
                                                                  $$ = insertNode(NULL, "If", $3);
                                                                  connectBrothers($5, $7);
                                                                  connectBrothers($3, $5);
                                                                }
    | IF LPAR Expr RPAR StatementError %prec IFX                { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL);
                                                                  }

                                                                  $$ = insertNode(NULL, "If", $3);
                                                                  connectBrothers($3, $5);
                                                                }

    | WHILE LPAR Expr RPAR StatementError                       { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL);
                                                                  }
                                                                  $$ = insertNode(NULL, "While", $3);
                                                                  connectBrothers($3, $5);
                                                                }
    ;

StatementError: error SEMI                                      { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL); }
    | Statement                                                 { $$ = $1; }
    ;

optExp: Expr SEMI                                               { $$ = $1; }
    | SEMI                                                      { $$ = NULL; }
    ;

optState: StatementError optState                               { if ($1!= NULL) 
                                                                    $$ = $1;
                                                                    if ($2 !=NULL){
                                                                        connectBrothers( $1, $2);
                                                                    } else {
                                                                        $$ = $2;
                                                                    }
                                                                }
    | error                                                     { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL); }
    | /*epsilon*/                                               { $$ = NULL; }
    ;

optExpCExp: Expr optCExp                                        { if ($2!= NULL) connectBrothers( $1, $2); $$ = insertNode(NULL, NULL, $1); }
    ;

optCExp: optCExp COMMA Expr                                     { connectBrothers( $1, $3); $$ = insertNode(NULL, NULL, $1); }
    | /*epsilon*/ %prec COMMA                                   { $$ = NULL; }
    ;

Expr: Expr ASSIGN Expr                                          { $$ = insertNode(NULL, "Store", $1); connectBrothers($1, $3); }
    | Expr COMMA Expr                                           { $$ = insertNode(NULL, "Comma", $1); connectBrothers($1, $3); }
    | LPAR error RPAR                                           { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL); }
    | ID LPAR error RPAR                                        { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL); }

    | Expr PLUS Expr                                            { $$ = insertNode(NULL, "Add", $1); connectBrothers($1, $3); }
    | Expr MINUS Expr                                           { $$ = insertNode(NULL, "Sub", $1); connectBrothers($1, $3); }
    | Expr MUL Expr                                             { $$ = insertNode(NULL, "Mul", $1); connectBrothers($1, $3); }
    | Expr DIV Expr                                             { $$ = insertNode(NULL, "Div", $1); connectBrothers($1, $3); }
    | Expr MOD Expr                                             { $$ = insertNode(NULL, "Mod", $1); connectBrothers($1, $3); }
    | Expr OR Expr                                              { $$ = insertNode(NULL, "Or", $1); connectBrothers($1, $3); }
    | Expr AND Expr                                             { $$ = insertNode(NULL, "And", $1); connectBrothers($1, $3); }
    | Expr BITWISEAND Expr                                      { $$ = insertNode(NULL, "BitWiseAnd", $1); connectBrothers($1, $3); }
    | Expr BITWISEOR Expr                                       { $$ = insertNode(NULL, "BitWiseOr", $1); connectBrothers($1, $3); }
    | Expr BITWISEXOR Expr                                      { $$ = insertNode(NULL, "BitWiseXor", $1); connectBrothers($1, $3); }
    | Expr EQ Expr                                              { $$ = insertNode(NULL, "Eq", $1); connectBrothers($1, $3); }
    | Expr NE Expr                                              { $$ = insertNode(NULL, "Ne", $1); connectBrothers($1, $3); }
    | Expr LE Expr                                              { $$ = insertNode(NULL, "Le", $1); connectBrothers($1, $3); }
    | Expr GE Expr                                              { $$ = insertNode(NULL, "Ge", $1); connectBrothers($1, $3); }
    | Expr LT Expr                                              { $$ = insertNode(NULL, "Lt", $1); connectBrothers($1, $3); }
    | Expr GT Expr                                              { $$ = insertNode(NULL, "Gt", $1); connectBrothers($1, $3); }

    | PLUS Expr                                                 { $$ = insertNode(NULL, "Plus", $2); }
    | MINUS Expr                                                { $$ = insertNode(NULL, "Minus", $2); }
    | NOT Expr                                                  { $$ = insertNode(NULL, "Not", $2); }
    | ID LPAR RPAR                                              { $$ = insertNode(NULL, "Call", insertNode($1, "Id", NULL));}
    | ID LPAR optExpCExp RPAR                                   { aux = insertNode($1, "Id", NULL);
                                                                  if ($3 == NULL){ $$ = insertNode(NULL, NULL, aux); }
                                                                  else{$$ = insertNode(NULL, "Call", aux); connectBrothers(aux , $3); }
                                                                }
    | ID                                                        { $$ = insertNode($1, "Id", NULL); }
    | INTLIT                                                    { $$ = insertNode($1, "IntLit", NULL); }
    | CHRLIT                                                    { $$ = insertNode($1, "ChrLit", NULL); }
    | REALLIT                                                   { $$ = insertNode($1, "RealLit", NULL); }
    | LPAR Expr RPAR                                            { $$ = insertNode(NULL, NULL, $2); }
    ;

%%


