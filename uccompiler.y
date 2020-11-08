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

/* //???
%nonassoc   IF 
%nonassoc   ELSE
*/

/*%nonassoc LBRACE RBRACE LPAR RPAR*/

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

/*%left   LBRACE RBRACE LPAR RPAR*/

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
%type optExpr
%type optID
%type optExpCExp
%type optCExp


%%
Program: FunctionsAndDeclarations                            {;}
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

Statement: optExp SEMI                                          {;}
    | LBRACE optState RBRACE                                    {;}
    | IF LPAR Expr RPAR Statement optElse                       {;}
    | WHILE LPAR Expr RPAR Statement                            {;}
    | RETURN optExp SEMI                                        {;}
    ;

optExp: Expr                                                    {;}
    | %empty                                                    {;}
    ;

optState: optState Statement                                    {;}
    | %empty                                                    {;}
    ;

optElse: ELSE Statement                                         {;}
    | /*empty*/                                                 {;}
    ;

Expr: Expr optExpr Expr                                         {;}
    | PLUS Expr                                                 {;}
    | MINUS Expr                                                {;}
    | NOT Expr                                                  {;}
    | ID optID                                                  {;}
    | INTLIT                                                    {;}
    | CHRLIT                                                    {;}
    | REALLIT                                                   {;}
    | LPAR Expr RPAR                                            {;}
    ;

optExpr: ASSIGN | COMMA 
    | PLUS | MINUS
    | MUL | DIV | MOD 
    | OR | AND
    | BITWISEAND | BITWISEOR | BITWISEXOR
    | EQ | NE | LE | GE | LT | GT
    ;

optID: LPAR optExpCExp RPAR
    | /*empty*/
    ;

optExpCExp: Expr optCExp
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

