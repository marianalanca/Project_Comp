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


%token

%token CHAR
%token ELSE
%token IF
%token WHILE
%token INT
%token DOUBLE
%token SHORT
%token RETURN
%token
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
%token INTLIT
%token EXPONENTIAL
%token REALLIT
%token <string> RESERVED

%left PLUS MINUS
%right MUL DIV COMMA


%%

calc: expression                        {printf("%d\n", $1);}

expression:
    |   '(' expression ')'                  {$$=$2;}
    |   expression '+' expression           {$$=$1+$3;}
    |   expression '-' expression           {$$=$1-$3;}
    |   expression '*' expression           {$$=$1*$3;}
    |   expression '/' expression           { if ($3 == 0) {printf("Divide by zero!\n"); $$ = 0; return -1;} $$=$1/$3;}
    |   '-'NUMBER                           {$$=-$1;}
    |   NUMBER                              {$$=$1;}
    |   ;
%%

int main() {
    yyparse();
    return 0;
}

