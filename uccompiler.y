/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex (void);
    // colocar os erros aqui
    void yyerror (char const *s) {
        fprintf (stderr, "Line , col : %s :\n", s);
    }

    int commaFlag = 0;

    typedef struct _t1{
        char* id;
        char* type;
        struct _t1* son;
        struct _t1* brother;
    } node;

    char * auxType;
    node * auxiliar;
    node * nodeAux;

    node * insertNode(char * id, char * type, node * son) {
        node * auxiliar = (node *)malloc(sizeof(node));
        auxiliar->type = type;
        auxiliar->id = id;
        auxiliar->son = son;
        auxiliar->brother = NULL;

        return auxiliar;
    }

    void connectBrothers(node* node1, node* brother){
        node1->brother = brother;
    }

    // Just for testing purposes
    void printTree(node * auxNode, int pontos)
    {
        int i, call=0;

        if (auxNode!=NULL){

            if (auxNode->type!=NULL && strcmp(auxNode->type,"Comma")==0 && commaFlag == 1){
                if (auxNode->son != NULL){
                    printTree(auxNode->son,pontos);
                }
            }
            else if (auxNode->type!=NULL && strcmp(auxNode->type,"Aux")==0){
                if (commaFlag==1){
                    commaFlag = 0;
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
                    commaFlag = 1;
                }
                else
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
            }

            else{
                if (auxNode->id != NULL && strcmp(auxNode->id,"type")==0){
                    for (i = 0; i < pontos-2; i++)
                        printf(".");

                    printf("%s\n", auxNode->type);
                    for (i = 0; i < pontos; i++)
                        printf(".");
                    printf("%s\n",auxType);

                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);

                }

                else if (auxNode->type != NULL){

                    if (strcmp(auxNode->type,"Call")==0){
                        call = 1;
                        commaFlag = 1;
                    }
                    
                    if (strcmp(auxNode->type,"Declaration")==0)
                        auxType = auxNode->son->type;

                    for (i = 0; i < pontos; i++)
                        printf(".");
                    if (auxNode->id != NULL) 
                        printf("%s(%s)\n", auxNode->type, auxNode->id);
                    else   
                        printf("%s\n", auxNode->type);
                    
                    if (auxNode->son != NULL){
                        pontos+=2;
                        printTree(auxNode->son,pontos);
                        pontos-=2;
                    }
                    if (call==1)
                        commaFlag=0;  
                }
                else
                    if (auxNode->son != NULL)
                        printTree(auxNode->son,pontos);
            }
            if (auxNode->brother != NULL)
                    printTree(auxNode->brother,pontos);   
        }  
        free(auxNode);
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
%type <node> optLparRpar
%type <node> optID
%type <node> optExpCExp
%type <node> optCExp

%%

Program: FunctionsAndDeclarations                               { $$ = insertNode(NULL, "Program", $1); printf("hey\n"); printTree($$, 0); printf("hey\n"); }
    ;

FunctionsAndDeclarations: FunctionDefinition optFuncAndDec      {  connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }

    | FunctionDeclaration optFuncAndDec                         { connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }

    | Declaration optFuncAndDec                                 { connectBrothers($1, $2);
                                                                    $$ = $1;
                                                                }
    ;

optFuncAndDec: FunctionsAndDeclarations                         { $$ = $1; }
    | /*epsilon*/                                               { ; }
    ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody    { $$ = insertNode(NULL, "FuncDefinition", $1);
                                                                  connectBrothers($1, $2);
                                                                  connectBrothers($2, $3);
                                                                }
    ;

FunctionBody: LBRACE optDecAndState RBRACE                      { $$ = insertNode(NULL, "FuncBody", $2); }
    ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI           { $$ = insertNode(NULL, "FuncDeclaration", $1);
                                                                  connectBrothers($1, $2);
                                                                }
    ;

DeclarationsAndStatements: Statement optDecAndState             { connectBrothers($1, $2); $$ = $1; }
    | Declaration optDecAndState                                { connectBrothers($1, $2); $$ = $1; }
    | error SEMI optDecAndState                                 { ; }
    ;

optDecAndState: DeclarationsAndStatements                       { $$ = $1; }
    | /*epsilon*/                                               { ; }
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  { // É assim?
                                                                  auxiliar = insertNode($1, "Id", NULL);
                                                                  connectBrothers(auxiliar, $3);
                                                                  $$ = insertNode(NULL, "FuncDeclarator", auxiliar);
                                                                }
    ;

ParameterList: ParameterDeclaration optParamList                { $$ = insertNode(NULL, "ParamList", $1);
                                                                  connectBrothers($1, $2);
                                                                }
    ;

optParamList: optParamList COMMA ParameterDeclaration           { connectBrothers($1, $3); $$ = $1; }
    |  /*epsilon*/                                              { ; }
    ;

ParameterDeclaration: TypeSpec optParamDec                      { $$ = insertNode(NULL, "ParamDeclaration", $1);
                                                                  connectBrothers($1, $2);
                                                                }
    ;

optParamDec: ID                                                 { $$ = insertNode($1, "Id", NULL); }
    |  /*epsilon*/                                              { ; }
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            { $$ = insertNode(NULL, "Declaration", $1);
                                                                  connectBrothers($1, $2);
                                                                  connectBrothers($2, $3);
                                                                }
    ;

optDeclaration: optDeclaration COMMA Declarator                 { connectBrothers($1, $3); $$ = $1; }
    |  /*epsilon*/                                              { ; }
    ;

TypeSpec: CHAR                                                  { $$ = insertNode(NULL, "Char", NULL); }
    | INT                                                       { $$ = insertNode(NULL, "Int", NULL); }
    | VOID                                                      { $$ = insertNode(NULL, "Void", NULL); }
    | SHORT                                                     { $$ = insertNode(NULL, "Short", NULL); }
    | DOUBLE                                                    { $$ = insertNode(NULL, "Double", NULL); }
    ;

Declarator: ID OptDeclarator                                    { auxiliar = insertNode($1, "Id", NULL);
                                                                  connectBrothers(auxiliar, $2);
                                                                  $$ = auxiliar;
                                                                }
    ;

OptDeclarator: ASSIGN Expr                                      { $$ = $2; }
    |  /*epsilon*/                                              { ; }
    ;

Statement: optExp                                               { ; }
    | RETURN optExp                                             { $$ = insertNode(NULL, "Return", $2); }
    | LBRACE optState RBRACE                                    { ; }
    | IF LPAR Expr RPAR StatementError %prec IFX                { ; }
    | IF LPAR Expr RPAR StatementError ELSE StatementError      { ; }
    | WHILE LPAR Expr RPAR StatementError                       { ; }
    ;

StatementError: error SEMI                                      { ; }
    | Statement                                                 { $$ = $1; }
    ;

optExp: Expr SEMI                                               { $$ = $1; }
    | SEMI                                                      { ; }
    ;

optState: StatementError optState                               { connectBrothers( $1, $2); $$ = $1; }
    | error                                                     { ; }
    | /*epsilon*/                                               { ; }
    ;

Expr: PLUS Expr                                                 { $$ = insertNode(NULL, "Plus", $2); }
    | MINUS Expr                                                { $$ = insertNode(NULL, "Minus", $2); }
    | NOT Expr                                                  { $$ = insertNode(NULL, "Not", $2); }
    | ID optID                                                  { $$ = insertNode($1, "Call", $2); connectBrothers($1, $2); }
    | INTLIT                                                    { $$ = insertNode($1, "IntLit", NULL); }
    | CHRLIT                                                    { $$ = insertNode($1, "ChrLit", NULL); }
    | REALLIT                                                   { $$ = insertNode($1, "RealLit", NULL); }
    | LPAR optLparRpar RPAR                                     { ; }
    | Expr ASSIGN Expr                                          { $$ = insertNode(NULL, "Store", $1); connectBrothers($1, $3); }
    | Expr COMMA Expr                                           { $$ = insertNode(NULL, "Comma", $1); connectBrothers($1, $3); }
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
    | Expr LE Expr                                              { $$ = insertNode(NULL, "Store", $1); connectBrothers($1, $3); }
    | Expr GE Expr                                              { $$ = insertNode(NULL, "Ge", $1); connectBrothers($1, $3); }
    | Expr LT Expr                                              { $$ = insertNode(NULL, "Lt", $1); connectBrothers($1, $3); }
    | Expr GT Expr                                              { $$ = insertNode(NULL, "Gt", $1); connectBrothers($1, $3); }
    ;

optLparRpar: Expr                                               { $$ = $1; }
    | error                                                     { ; }
    ;

optID: LPAR optExpCExp RPAR                                     { $$ = $2; }
    | /*epsilon*/                                               { ; }
    ;

optExpCExp: Expr optCExp                                        { connectBrothers( $1, $2); $$ = $1; }
    | error                                                     { ; }
    | /*epsilon*/                                               { ; }
    ;

optCExp: optCExp COMMA Expr                                     { connectBrothers( $1, $3); $$ = $1; }
    | /*epsilon*/ %prec COMMA                                   { ; }
    ;


%%


