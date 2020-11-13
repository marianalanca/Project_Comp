/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%x COMMENTS

ID                  [a-zA-Z_][a-zA-Z0-9_]*
INTLIT              [0-9]+
EXCEPTIONS          [^\'\\\n]
CHRLIT              {EXCEPTIONS}|"\\n"|"\\t"|"\\\\"|"\\\'"|"\\\""|"\\"[0-7]{1,3}|\t
EXPONENTIAL         [eE][+-]?{INTLIT}
REALLIT             (([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)){EXPONENTIAL}?|{INTLIT}{EXPONENTIAL}
RESERVED            "auto"|"break"|"const"|"continue"|"asm"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"register"|"long"|"signed"|"unsigned"|"sizeof"|"static"|"struct"|"switch"|"case"|"default"|"typedef"|"union"|"volatile"|"break"|"_Bool"|"_Imaginary"|"restrict"|"inline"|"_Complex"|"["|"]"|"++"|"--"
OTHER               ([ ]|"\t")
END_OF_LINE         \n|\r\n|\r

%{

  #include "y.tab.h"

  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;

%}

%%

"char"                                 { if(flag==1) printf("CHAR\n"); column+=yyleng; return CHAR; }
"else"                                 { if(flag==1) printf("ELSE\n"); column+=yyleng; return ELSE; }
"if"                                   { if(flag==1) printf("IF\n"); column+=yyleng; return IF; }
"while"                                { if(flag==1) printf("WHILE\n"); column+=yyleng; return WHILE; }
"int"                                  { if(flag==1) printf("INT\n"); column+=yyleng; return INT; }
"double"                               { if(flag==1) printf("DOUBLE\n"); column+=yyleng; return DOUBLE; }
"short"                                { if(flag==1) printf("SHORT\n"); column+=yyleng; return SHORT; }
"return"                               { if(flag==1) printf("RETURN\n"); column+=yyleng; return RETURN; }
"void"                                 { if(flag==1) printf("VOID\n"); column+=yyleng; return VOID; }
"&"                                    { if(flag==1) printf("BITWISEAND\n"); column+=yyleng; return BITWISEAND; }
"|"                                    { if(flag==1) printf("BITWISEOR\n"); column+=yyleng; return BITWISEOR; }
"^"                                    { if(flag==1) printf("BITWISEXOR\n"); column+=yyleng; return BITWISEXOR; }
"&&"                                   { if(flag==1) printf("AND\n"); column+=yyleng; return AND; }
"="                                    { if(flag==1) printf("ASSIGN\n"); column+=yyleng; return ASSIGN; }
"*"                                    { if(flag==1) printf("MUL\n"); column+=yyleng; return MUL; }
","                                    { if(flag==1) printf("COMMA\n"); column+=yyleng; return COMMA; }
"/"                                    { if(flag==1) printf("DIV\n"); column+=yyleng; return DIV; }
"=="                                   { if(flag==1) printf("EQ\n"); column+=yyleng; return EQ; }
">="                                   { if(flag==1) printf("GE\n"); column+=yyleng; return GE; }
">"                                    { if(flag==1) printf("GT\n"); column+=yyleng; return GT; }
"{"                                    { if(flag==1) printf("LBRACE\n"); column+=yyleng; return LBRACE; }
"<="                                   { if(flag==1) printf("LE\n"); column+=yyleng; return LE; }
"("                                    { if(flag==1) printf("LPAR\n"); column+=yyleng; return LPAR; }
"<"                                    { if(flag==1) printf("LT\n"); column+=yyleng; return LT; }
"-"                                    { if(flag==1) printf("MINUS\n"); column+=yyleng; return MINUS; }
"%"                                    { if(flag==1) printf("MOD\n"); column+=yyleng; return MOD; }
"!="                                   { if(flag==1) printf("NE\n"); column+=yyleng; return NE; }
"!"                                    { if(flag==1) printf("NOT\n"); column+=yyleng; return NOT; }
"||"                                   { if(flag==1) printf("OR\n"); column+=yyleng; return OR; }
"+"                                    { if(flag==1) printf("PLUS\n"); column+=yyleng; return PLUS; }
"}"                                    { if(flag==1) printf("RBRACE\n"); column+=yyleng; return RBRACE; }
")"                                    { if(flag==1) printf("RPAR\n"); column+=yyleng; return RPAR; }
";"                                    { if(flag==1) printf("SEMI\n"); column+=yyleng; return SEMI; }

{RESERVED}                             { if(flag==1) printf("RESERVED(%s)\n", yytext); yylval.id = strdup(yytext); column+=yyleng; return RESERVED; }
{ID}                                   { if(flag==1) printf("ID(%s)\n", yytext); yylval.id = (char* ) strdup(yytext); column+=yyleng; return ID; }
{INTLIT}                               { if(flag==1) printf("INTLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return INTLIT; }
{REALLIT}                              { if(flag==1) printf("REALLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return REALLIT; }
\'{CHRLIT}\'                           { if(flag==1) printf("CHRLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return CHRLIT; }
\'({EXCEPTIONS}|\\.)*'                 { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

"\/\/".*{END_OF_LINE}?                 { line++; column = 1; }
"\/\*"                                 { BEGIN COMMENTS; errorC = column; errorL = line; }

<COMMENTS><<EOF>>                      { printf("Line %d, col %d: unterminated comment\n", errorL, errorC + 2); BEGIN 0; }
<COMMENTS>"\*\/"                       { BEGIN 0; column += yyleng + 2; }
<COMMENTS>\n                           { line++; column = 1; }
<COMMENTS>.                            { column+=yyleng; }

{OTHER}                                { column+=yyleng; }
{END_OF_LINE}                          { line++; column = 1; }
<<EOF>>                                { column+=yyleng; yyterminate(); }
.                                      { printf("Line %d, col %d: illegal character (%s)\n", line, column , yytext); column+= yyleng; }

%%

void yyerror (char *s)
{
  if(flag >= 2)
    printf("Line %d, col %d: %s: %s\n", line , column - (int)yyleng, s, yytext);
}

int main(int argc, char **argv)
{
  if (argc == 2)
  {
    if(strcmp(argv[1], "-e1")==0)
    {
      flag = 0; /*Só analise lexical - erros*/
    }
    else if(strcmp(argv[1], "-l")==0)
    {
      flag = 1; /*Só analise lexical - erros e tokens*/
    }
    else if(strcmp(argv[1], "-t")==0){
      flag = 2; /*parsing tree*/
    }
    else if(strcmp(argv[1], "-e2")==0){
      flag= 3; /*erros sintaticos e lexicais*/
    }
  }
  else{
    /*Sem flag deve escrever erros lexicais e de sintaxe*/
    flag = 4;
  }

  yyparse();
  return 0;
}

int yywrap()
{
  return 1;
}
