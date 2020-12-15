/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include "functions.h"
    #include "symbol_table.h"

    extern int flag;
    int errorFlag = 0;

    int yylex (void);
    void yyerror (char const *s) ;

    node * aux;
    node * aux1;

    node* AST_root;

%}

%union{
    struct _token* id;
    struct _t1* node;
}

%token <id> CHAR ELSE IF WHILE INT DOUBLE SHORT RETURN VOID BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI
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

Program: FunctionsAndDeclarations                               { $$ = insertNode(NULL, "Program", $1, 0, 0); AST_root = $$; }
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

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody    { $$ = insertNode(NULL, "FuncDefinition", $1, 0, 0);
                                                                  connectBrothers($1, $2);
                                                                  connectBrothers($2, $3);
                                                                }
    ;

FunctionBody: LBRACE optDecAndState RBRACE                      { $$ = insertNode(NULL, "FuncBody", $2, 0, 0); }
    ;

DeclarationsAndStatements: Statement optDecAndState             { if ($1 != NULL){
                                                                    $$ = $1;
                                                                    if ($2 != NULL)
                                                                        connectBrothers($1, $2);
                                                                    } else{
                                                                        $$ = $2;
                                                                    }
                                                                }
    | Declaration optDecAndState                                { if ($2 != NULL) connectBrothers($1, $2); $$ = $1; }
    ;

optDecAndState: DeclarationsAndStatements                       { $$ = $1; }
    | /*epsilon*/                                               { $$ = NULL; }
    ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI           { $$ = insertNode(NULL, "FuncDeclaration", $1, 0, 0);
                                                                  connectBrothers($1, $2);
                                                                }
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  { aux = insertNode($1->id, "Id", NULL, $1->line, $1->col);
                                                                  connectBrothers(aux, insertNode(NULL, "ParamList", $3, 0, 0));
                                                                  $$ = insertNode(NULL, NULL, aux, 0, 0);
                                                                  /*freeToken($1);*/
                                                                }
    ;

ParameterList: ParameterList COMMA ParameterDeclaration         { $$ = $1;
                                                                  connectBrothers($1, $3);
                                                                }
    | ParameterDeclaration                                      { $$ = $1; }
    ;

ParameterDeclaration: TypeSpec optParamDec                      { $$ = insertNode(NULL, "ParamDeclaration", $1, 0, 0); if ( $2 != NULL) connectBrothers ($1, $2); }
    ;

optParamDec: ID                                                 { $$ = insertNode($1->id, "Id", NULL, $1->line, $1->col);
                                                                  /*freeToken($1);*/ }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            { $$ = insertNode(NULL, "Declaration", $1, 0, 0);
                                                                  connectBrothers($1, $2);
                                                                  if ($3 != NULL) {
                                                                      connectBrothers($$, $3);
                                                                      while ($3!=NULL){
                                                                          aux = $3->son;
                                                                          $3->son = insertNode(NULL, $1->type, NULL, 0, 0);
                                                                          connectBrothers($3->son, aux);
                                                                          $3 = $3->brother;
                                                                      }
                                                                  }
                                                                }
    | error SEMI                                                { $$ = insertNode(NULL, NULL, NULL, 0, 0); errorFlag=-1;}
    ;



optDeclaration: optDeclaration COMMA Declarator                 { aux = insertNode(NULL, "Declaration", $3, 0, 0);
                                                                  if ( $1 != NULL){
                                                                      connectBrothers($1, aux);
                                                                      $$ = $1;
                                                                  } else {
                                                                      $$ = aux;
                                                                  }
                                                                }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

TypeSpec: CHAR                                                  { $$ = insertNode(NULL, "Char", NULL, 0, 0); }
    | INT                                                       { $$ = insertNode(NULL, "Int", NULL, 0, 0); }
    | VOID                                                      { $$ = insertNode(NULL, "Void", NULL, $1->line, $1->col); }
    | SHORT                                                     { $$ = insertNode(NULL, "Short", NULL, 0, 0); }
    | DOUBLE                                                    { $$ = insertNode(NULL, "Double", NULL, 0, 0); }
    ;

Declarator: ID OptDeclarator                                    { aux = insertNode($1->id, "Id", NULL, $1->line, $1->col);
                                                                  if ($2 != NULL){
                                                                    connectBrothers(aux, $2);
                                                                  }
                                                                  $$ =aux;
                                                                  /*freeToken($1);*/
                                                                }
    ;

OptDeclarator: ASSIGN Expr                                      { $$ = $2; }
    |  /*epsilon*/                                              { $$ = NULL; }
    ;

Statement: optExp                                               { $$ = $1; }
    | LBRACE RBRACE                                             { $$ = NULL; }
    | LBRACE error RBRACE                                       { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL, 0, 0); }
    | LBRACE optState RBRACE                                    { if($2!=NULL && $2->brother!=NULL) $$ = insertNode(NULL, "StatList", $2, 0, 0); else $$ = $2; } /*caso {;;;} não pode entrar*/

    | RETURN Expr SEMI                                          { $$ = insertNode(NULL, "Return", $2, $1->line, $1->col);
                                                                  /*freeToken($1); */
                                                                }
    | RETURN SEMI                                               { $$ = insertNode(NULL, "Return", insertNode(NULL, "Null", NULL, 0, 0), $1->line, $1->col); 
                                                                  /*freeToken($1);*/
                                                                }

    | IF LPAR Expr RPAR StatementError ELSE StatementError      { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL, 0, 0);
                                                                  }
                                                                  if ($7 == NULL){
                                                                      $7 = insertNode(NULL, "Null", NULL, 0, 0);
                                                                  }
                                                                  $$ = insertNode(NULL, "If", $3, $1->line, $1->col);
                                                                  connectBrothers($5, $7);
                                                                  connectBrothers($3, $5);
                                                                  /*freeToken($1);*/
                                                                }
    | IF LPAR Expr RPAR StatementError %prec IFX                { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL, 0, 0);
                                                                  }
                                                                  $$ = insertNode(NULL, "If", $3, $1->line, $1->col);
                                                                  connectBrothers($3, $5);
                                                                  connectBrothers($5, insertNode(NULL, "Null", NULL, 0, 0));
                                                                  /*freeToken($1);*/
                                                                }

    | WHILE LPAR Expr RPAR StatementError                       { if ($5 == NULL){ /*SEMI*/
                                                                    $5 = insertNode(NULL, "Null", NULL, 0, 0);
                                                                  }
                                                                  $$ = insertNode(NULL, "While", $3, $1->line, $1->col);
                                                                  connectBrothers($3, $5);
                                                                  /*freeToken($1);*/
                                                                }
    ;

StatementError: error SEMI                                      { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL, 0, 0); }
    | Statement                                                 { $$ = $1; }
    ;

optExp: Expr SEMI                                               { $$ = $1; }
    | SEMI                                                      { $$ = NULL; }
    ;

optState: StatementError optState                               { if ($1!= NULL){
                                                                    $$ = $1;
                                                                    if ($2 !=NULL)
                                                                        connectBrothers( $1, $2);
                                                                  } else {
                                                                    $$ = $2;
                                                                  }
                                                                }
    | StatementError                                            { $$ = $1; }
    ;

Expr: Expr ASSIGN Expr                                          { $$ = insertNode(NULL, "Store", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr COMMA Expr                                           { $$ = insertNode(NULL, "Comma", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | LPAR error RPAR                                           { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL, 0, 0); }
    | ID LPAR error RPAR                                        { errorFlag = -1; $$ = insertNode(NULL, NULL, NULL, 0, 0); }

    | Expr PLUS Expr                                            { $$ = insertNode(NULL, "Add", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr MINUS Expr                                           { $$ = insertNode(NULL, "Sub", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr MUL Expr                                             { $$ = insertNode(NULL, "Mul", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr DIV Expr                                             { $$ = insertNode(NULL, "Div", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr MOD Expr                                             { $$ = insertNode(NULL, "Mod", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr OR Expr                                              { $$ = insertNode(NULL, "Or", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr AND Expr                                             { $$ = insertNode(NULL, "And", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr BITWISEAND Expr                                      { $$ = insertNode(NULL, "BitWiseAnd", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr BITWISEOR Expr                                       { $$ = insertNode(NULL, "BitWiseOr", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr BITWISEXOR Expr                                      { $$ = insertNode(NULL, "BitWiseXor", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr EQ Expr                                              { $$ = insertNode(NULL, "Eq", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr NE Expr                                              { $$ = insertNode(NULL, "Ne", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr LE Expr                                              { $$ = insertNode(NULL, "Le", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr GE Expr                                              { $$ = insertNode(NULL, "Ge", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr LT Expr                                              { $$ = insertNode(NULL, "Lt", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}
    | Expr GT Expr                                              { $$ = insertNode(NULL, "Gt", $1, $2->line, $2->col); connectBrothers($1, $3); /*freeToken($2);*/}

    | PLUS Expr %prec NOT                                       { $$ = insertNode(NULL, "Plus", $2, $1->line, $1->col); /*freeToken($1);*/}
    | MINUS Expr %prec NOT                                      { $$ = insertNode(NULL, "Minus", $2, $1->line, $1->col); /*freeToken($1);*/}
    | NOT Expr                                                  { $$ = insertNode(NULL, "Not", $2, $1->line, $1->col); /*freeToken($1);*/}

    | ID LPAR RPAR                                              { $$ = insertNode(NULL, "Call", insertNode($1->id, "Id", NULL, $1->line, $1->col), 0, 0); /*freeToken($1);*/}
    | ID LPAR optExpCExp RPAR                                   { aux = insertNode($1->id, "Id", NULL, $1->line, $1->col);
                                                                  if ($3 == NULL){ $$ = insertNode(NULL, "Call", aux, 0, 0); }
                                                                  else{$$ = insertNode(NULL, "Call", aux, 0, 0); connectBrothers(aux , $3); }
                                                                  /*freeToken($1);*/;
                                                                }
    | ID                                                        { $$ = insertNode($1->id, "Id", NULL, $1->line, $1->col); /*freeToken($1);*/}
    | INTLIT                                                    { $$ = insertNode($1->id, "IntLit", NULL, $1->line, $1->col); /*freeToken($1);*/}
    | CHRLIT                                                    { $$ = insertNode($1->id, "ChrLit", NULL, $1->line, $1->col); /*freeToken($1);*/}
    | REALLIT                                                   { $$ = insertNode($1->id, "RealLit", NULL, $1->line, $1->col); /*freeToken($1);*/}
    | LPAR Expr RPAR                                            { $$ = insertNode(NULL, NULL, $2, 0, 0); }
    ;

optExpCExp: Expr optCExp                                        { if ($2!= NULL) connectBrothers( $1, $2); $$ = insertNode(NULL, NULL, $1, 0, 0); }
    ;

optCExp: optCExp COMMA Expr                                     { if ($1 != NULL) {connectBrothers( $1, $3); $$ = $1; } else { $$ = $3; }  }
    | /*epsilon*/ %prec COMMA                                   { $$ = NULL; }
    ;


%%


