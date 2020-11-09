/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include <stdio.h>
    int yylex(void);
    // colocar os erros aqui
    void yyerror (const char *s);


%}

%token CHAR
%token ELSE
%token IF
%token WHILE
%token INT
%token DOUBLE
%token SHORT
%token RETURN
%token VOID
%token BITWISEAND
%token BITWISEOR
%token BITWISEXOR
%token AND
%token ASSIGN
%token MUL
%token COMMA
%token DIV
%token EQ
%token GE
%token GT
%token LBRACE
%token LE
%token LPAR
%token LT
%token MINUS
%token MOD
%token NE
%token NOT
%token OR
%token PLUS
%token RBRACE
%token RPAR
%token SEMI

%token <string> CHRLIT
%token <string> ID
%token <string> INTLIT
%token <string> REALLIT
%token <string> RESERVED

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

%type Program
%type FunctionsAndDeclarations
%type optFuncAndDec
%type FunctionDefinition
%type FunctionBody
%type DeclarationsAndStatements
%type optDecAndState 
%type FunctionDeclaration
%type FunctionDeclarator
%type ParameterList
%type optParamList
%type ParameterDeclaration
%type optParamDec
%type Declaration
%type optDeclaration
%type TypeSpec
%type Declarator
%type OptDeclarator
%type Statement
%type optExp
%type optState
%type optElse
%type Expr
/*%type Expr1
/*%type optExpr*/
%type optLparRpar
%type optID
%type optExpCExp
%type optCExp

%%
Program: FunctionsAndDeclarations
    ;

FunctionsAndDeclarations: FunctionDefinition optFuncAndDec   {;}
    | FunctionDeclaration optFuncAndDec                      {;}
    | Declaration optFuncAndDec                              {;}
    ;

optFuncAndDec: FunctionsAndDeclarations                      {;}
    | /*empty*/                                              {;}
    ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody 
;

FunctionBody: LBRACE DeclarationsAndStatements RBRACE        {;}
    ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI        {;}
;

DeclarationsAndStatements: Statement optDecAndState             {;}
    | Declaration optDecAndState                                {;}
    ;

optDecAndState: DeclarationsAndStatements                       {;}
    | /*empty*/                                                 {;}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  {;}
    ;

ParameterList: ParameterDeclaration optParamList                {;}
    ;

optParamList: optParamList COMMA ParameterDeclaration           {;} 
    | %empty                                                    {;}
    ;

ParameterDeclaration: TypeSpec optParamDec                      {;}
    ;

optParamDec: ID                                                 {;}
    | %empty                                                    {;}
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            {;}
    | error SEMI
    ;

optDeclaration: optDeclaration COMMA Declarator                 {;}
    | %empty                                                    {;}
    ;

TypeSpec: CHAR 
    | INT                                                       {;}
    | VOID                                                      {;}
    | SHORT                                                     {;}
    | DOUBLE                                                    {;}
    ;

Declarator: ID OptDeclarator                                    {;}
    ;

OptDeclarator: ASSIGN Expr                                      {;}
    | %empty                                                    {;}
    ;

Statement: StatementError SEMI                                          {;}
    | LBRACE optState RBRACE                                    {;}
    | IF LPAR Expr RPAR Statement optElse                       {;}
    | WHILE LPAR Expr RPAR Statement                            {;}
    ;

StatementError: optExp
    | RETURN optExp
    | error
    ;

optExp: Expr                                                    {;}
    | %empty                                                    {;}
    ;

optState: optState Statement                                    {;}
    | error
    | %empty                                                    {;}
    ;

optElse: ELSE Statement                                         {;}
    | /*empty*/                                                 {;}
    ;

Expr: PLUS Expr                                                 {;}
    | MINUS Expr                                                {;}
    | NOT Expr                                                  {;}
    | ID optID                                                  {;}
    | INTLIT                                                    {;}
    | CHRLIT                                                    {;}
    | REALLIT                                                   {;}
    | LPAR optLparRpar RPAR                                     {;}
    | Expr ASSIGN Expr
    | Expr COMMA Expr 
    | Expr PLUS Expr 
    | Expr MINUS Expr
    | Expr MUL Expr
    | Expr DIV Expr
    | Expr MOD Expr
    | Expr OR Expr
    | Expr AND Expr
    | Expr BITWISEAND Expr
    | Expr BITWISEOR Expr
    | Expr BITWISEXOR Expr
    | Expr EQ Expr
    | Expr NE Expr 
    | Expr LE Expr 
    | Expr GE Expr 
    | Expr LT Expr 
    | Expr GT Expr
    ;

optLparRpar: Expr
    | error
;

optID: LPAR optExpCExp RPAR
    | /*empty*/
    ;

optExpCExp: Expr optCExp
    | error
    | /*empty*/ 
    ;

optCExp: optCExp COMMA Expr
    | /*empty*/
    ;


%%

int main() {
    yyparse();
    return 0;
}

