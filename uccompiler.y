/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "AST.h"


    int yylex (void);
    // colocar os erros aqui
    void yyerror (char const *s) {
        fprintf (stderr, "Line , col : %s :%s\n", s, yytext);
    }
%}

%union{
    char * id;
    struct node* node;
}

%token CHAR ELSE IF WHILE INT DOUBLE SHORT RETURN VOID BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI
// Perceber melhor isto
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

Program: FunctionsAndDeclarations                            {;}
    ;

FunctionsAndDeclarations: FunctionDefinition optFuncAndDec   {;}
    | FunctionDeclaration optFuncAndDec                      {;}
    | Declaration optFuncAndDec                              {;}
    ;

optFuncAndDec: FunctionsAndDeclarations                      {;}
    | /*epsilon*/                                            {;}
    ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody
;

FunctionBody: LBRACE optDecAndState RBRACE                      {;}
    ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI           {;}
;

DeclarationsAndStatements: Statement optDecAndState             {;}
    | Declaration optDecAndState                                {;}
    | error SEMI optDecAndState
    ;

optDecAndState: DeclarationsAndStatements                       {;}
    | /*epsilon*/                                               {;}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR                  {;}
    ;

ParameterList: ParameterDeclaration optParamList                {;}
    ;

optParamList: optParamList COMMA ParameterDeclaration           {;}
    |  /*epsilon*/                                              {;}
    ;

ParameterDeclaration: TypeSpec optParamDec                      {;}
    ;

optParamDec: ID                                                 {;}
    |  /*epsilon*/                                              {;}
    ;

Declaration: TypeSpec Declarator optDeclaration SEMI            {;}
    ;

optDeclaration: optDeclaration COMMA Declarator                 {;}
    |  /*epsilon*/                                              {;}
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
    |  /*epsilon*/                                              {;}
    ;

Statement: optExp                                               {;}
    | RETURN optExp                                             {;}
    | LBRACE optState RBRACE                                    {;}
    | IF LPAR Expr RPAR StatementError %prec optElse            {;}
    | WHILE LPAR Expr RPAR StatementError                       {;}
    ;

StatementError: error SEMI                                      {;}
    | Statement                                                 {;}
    ;

optExp: Expr SEMI                                               {;}
    | SEMI                                                      {;}
    ;

optState: StatementError optState                               {;}
    | error
    | /*epsilon*/                                               {;}
    ;

optElse: ELSE StatementError                                    {;}
    | /*epsilon*/                                               {;}
    ;

Expr: PLUS Expr                                                 {;}
    | MINUS Expr                                                {;}
    | NOT Expr                                                  {;}
    | ID optID                                                  {;}
    | INTLIT                                                    {;}
    | CHRLIT                                                    {;}
    | REALLIT                                                   {;}
    | LPAR optLparRpar RPAR                                     {;}
    | Expr ASSIGN Expr                                          {;}
    | Expr COMMA Expr                                           {;}
    | Expr PLUS Expr                                            {;}
    | Expr MINUS Expr                                           {;}
    | Expr MUL Expr                                             {;}
    | Expr DIV Expr                                             {;}
    | Expr MOD Expr                                             {;}
    | Expr OR Expr                                              {;}
    | Expr AND Expr                                             {;}
    | Expr BITWISEAND Expr                                      {;}
    | Expr BITWISEOR Expr                                       {;}
    | Expr BITWISEXOR Expr                                      {;}
    | Expr EQ Expr                                              {;}
    | Expr NE Expr                                              {;}
    | Expr LE Expr                                              {;}
    | Expr GE Expr                                              {;}
    | Expr LT Expr                                              {;}
    | Expr GT Expr                                              {;}
    ;

optLparRpar: Expr                                               {;}
    | error                                                     {;} 
;

optID: LPAR optExpCExp RPAR                                     {;}
    | /*epsilon*/                                               {;}
    ;

optExpCExp: Expr optCExp                                        {;}
    | error                                                     {;}
    | /*epsilon*/                                               {;}
    ;

optCExp: optCExp COMMA Expr                                     {;}
    | /*epsilon*/ %prec COMMA                                   {;}
    ;


%%


