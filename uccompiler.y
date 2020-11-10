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
    node * nodeAux;

    node * insertNode(char * id, char * type, node * son) {
        node * auxNode = (node *)malloc(sizeof(node));
        auxNode->type = type;
        auxNode->id = id;
        auxNode->son = son;
        auxNode->brother = NULL;

        return auxNode;
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
%type <node> optElse
%type <node> Expr
%type <node> optLparRpar
%type <node> optID
%type <node> optExpCExp
%type <node> optCExp

%%

Program: FunctionsAndDeclarations                               { $$ = insertNode(NULL, "Program", $1); printTree($$, 0); }
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
    | /*epsilon*/
    ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody    {   $$ = insertNode(NULL, "FuncDefinition", $1);
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

DeclarationsAndStatements: Statement optDecAndState             { ; }
    | Declaration optDecAndState                                { ; }
    | error SEMI optDecAndState
    ;

optDecAndState: DeclarationsAndStatements                       { ; }
    | /*epsilon*/                                               { ; }
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  {   $$ = insertNode($1, "Id", NULL);
                                                                    connectBrothers($1, $3);
                                                                }
    ;

ParameterList: ParameterDeclaration optParamList                { ; }
    ;

optParamList: optParamList COMMA ParameterDeclaration           { ; }
    |  /*epsilon*/                                              { ; }
    ;

ParameterDeclaration: TypeSpec optParamDec                      { ; }
    ;

optParamDec: ID                                                 { $$ = insertNode($1, "Id", NULL); }
    |  /*epsilon*/                                              { ; }
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            { ; }
    ;

optDeclaration: optDeclaration COMMA Declarator                 { ; }
    |  /*epsilon*/                                              { ; }
    ;

TypeSpec: CHAR                                                  { $$ = insertNode(NULL, "Char", NULL); }
    | INT                                                       { $$ = insertNode(NULL, "Int", NULL); }
    | VOID                                                      { $$ = insertNode(NULL, "Void", NULL); }
    | SHORT                                                     { $$ = insertNode(NULL, "Short", NULL); }
    | DOUBLE                                                    { $$ = insertNode(NULL, "Double", NULL); }
    ;

Declarator: ID OptDeclarator                                    { ; }
    ;

OptDeclarator: ASSIGN Expr                                      { ; }
    |  /*epsilon*/                                              { ; }
    ;

Statement: optExp                                               { ; }
    | RETURN optExp                                             { ; }
    | LBRACE optState RBRACE                                    { ; }
    | IF LPAR Expr RPAR StatementError optElse                  { ; }
    | WHILE LPAR Expr RPAR StatementError                       { ; }
    ;

StatementError: error SEMI                                      { ; }
    | Statement                                                 { ; }
    ;

optExp: Expr SEMI                                               { ; }
    | SEMI                                                      { ; }
    ;

optState: StatementError optState                               { ; }
    | error
    | /*epsilon*/                                               { ; }
    ;

optElse: ELSE StatementError                                    { ; }
    | /*epsilon*/                                               { ; }
    ;

Expr: PLUS Expr                                                 { ; }
    | MINUS Expr                                                { ; }
    | NOT Expr                                                  { ; }
    | ID optID                                                  { ; }
    | INTLIT                                                    { $$ = insertNode($1, "IntLit", NULL); }
    | CHRLIT                                                    { $$ = insertNode($1, "ChrLit", NULL); }
    | REALLIT                                                   { $$ = insertNode($1, "RealLit", NULL); }
    | LPAR optLparRpar RPAR                                     { ; }
    | Expr ASSIGN Expr                                          { ; }
    | Expr COMMA Expr                                           { ; }
    | Expr PLUS Expr                                            { ; }
    | Expr MINUS Expr                                           { ; }
    | Expr MUL Expr                                             { ; }
    | Expr DIV Expr                                             { ; }
    | Expr MOD Expr                                             { ; }
    | Expr OR Expr                                              { ; }
    | Expr AND Expr                                             { ; }
    | Expr BITWISEAND Expr                                      { ; }
    | Expr BITWISEOR Expr                                       { ; }
    | Expr BITWISEXOR Expr                                      { ; }
    | Expr EQ Expr                                              { ; }
    | Expr NE Expr                                              { ; }
    | Expr LE Expr                                              { ; }
    | Expr GE Expr                                              { ; }
    | Expr LT Expr                                              { ; }
    | Expr GT Expr                                              { ; }
    ;

optLparRpar: Expr                                               { ; }
    | error                                                     { ; }
;

optID: LPAR optExpCExp RPAR                                     { ; }
    | /*epsilon*/                                               { ; }
    ;

optExpCExp: Expr optCExp                                        { ; }
    | error                                                     { ; }
    | /*epsilon*/                                               { ; }
    ;

optCExp: optCExp COMMA Expr                                     { ; }
    | /*epsilon*/ %prec COMMA                                   { ; }
    ;


%%


