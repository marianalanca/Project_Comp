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

%token <string> CHRLIT
%token <string> ID
%token INTLIT
%token EXPONENTIAL
%token REALLIT

%token <string> RESERVED

%left '+' '-'
%right '*'


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

