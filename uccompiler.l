/*
    Mariana Loreto 2018280762
    Mariana Lança  2018288500
*/

%{
    #include "y.tab.h"
    #include "AST.h"
%}

%x COMMENTS

ID                  [a-zA-Z_][a-zA-Z0-9_]*
INTLIT              [0-9]+
EXCEPTIONS          [^\'\\\n]
CHRLIT              {EXCEPTIONS}|"\\n"|"\\t"|"\\\\"|"\\\'"|"\\\""|"\\"[0-7]{1,3}|\t
EXPONENTIAL         [eE][+-]?{INTLIT}
REALLIT             (([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)){EXPONENTIAL}?|{INTLIT}{EXPONENTIAL}
RESERVED            "auto"|"break"|"const"|"continue"|"asm"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"register"|"long"|"signed"|"unsigned"|"sizeof"|"static"|"struct"|"switch"|"case"|"default"|"typedef"|"union"|"volatile"|"break"|"_Bool"|"_Imaginary"|"restrict"|"inline"|"_Complex"|"["|"]"|"++"|"--"
OTHER               " "|\t
END_OF_LINE         \n|\r\n|\r

%{
  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;
%}

%%

"char"                                 { if(flag) printf("CHAR\n"); return CHAR;  column+=yyleng; }
"else"                                 { if(flag) printf("ELSE\n"); return ELSE; column+=yyleng; }
"if"                                   { if(flag) printf("IF\n"); return IF; column+=yyleng; }
"while"                                { if(flag) printf("WHILE\n"); return WHILE; column+=yyleng; }
"int"                                  { if(flag) printf("INT\n"); return INT; column+=yyleng; }
"double"                               { if(flag) printf("DOUBLE\n"); return DOUBLE; column+=yyleng; }
"short"                                { if(flag) printf("SHORT\n"); return SHORT; column+=yyleng; }
"return"                               { if(flag) printf("RETURN\n"); return RETURN; column+=yyleng; }
"void"                                 { if(flag) printf("VOID\n");  return VOID; column+=yyleng; }
"&"                                    { if(flag) printf("BITWISEAND\n");  return BITWISEAND; column+=yyleng; }
"|"                                    { if(flag) printf("BITWISEOR\n");  return BITWISEOR; column+=yyleng; }
"^"                                    { if(flag) printf("BITWISEXOR\n");  return BITWISEXOR; column+=yyleng; }
"&&"                                   { if(flag) printf("AND\n");  return AND; column+=yyleng; }
"="                                    { if(flag) printf("ASSIGN\n");  return ASSIGN; column+=yyleng; }
"*"                                    { if(flag) printf("MUL\n");  return MUL; column+=yyleng; }
","                                    { if(flag) printf("COMMA\n");  return COMMA; column+=yyleng; }
"/"                                    { if(flag) printf("DIV\n");  return DIV; column+=yyleng; }
"=="                                   { if(flag) printf("EQ\n");  return EQ; column+=yyleng; }
">="                                   { if(flag) printf("GE\n"); return GE; column+=yyleng; }
">"                                    { if(flag) printf("GT\n");  return GT; column+=yyleng; }
"{"                                    { if(flag) printf("LBRACE\n");  return LBRACE; column+=yyleng; }
"<="                                   { if(flag) printf("LE\n");  return LE; column+=yyleng; }
"("                                    { if(flag) printf("LPAR\n");  return LPAR; column+=yyleng; }
"<"                                    { if(flag) printf("LT\n");  return LT; column+=yyleng; }
"-"                                    { if(flag) printf("MINUS\n");  return MINUS; column+=yyleng; }
"%"                                    { if(flag) printf("MOD\n");  return MOD; column+=yyleng; }
"!="                                   { if(flag) printf("NE\n");  return NE; column+=yyleng; }
"!"                                    { if(flag) printf("NOT\n");  return NOT; column+=yyleng; }
"||"                                   { if(flag) printf("OR\n");  return OR; column+=yyleng; }
"+"                                    { if(flag) printf("PLUS\n");  return PLUS; column+=yyleng; }
"}"                                    { if(flag) printf("RBRACE\n");  return RBRACE; column+=yyleng; }
")"                                    { if(flag) printf("RPAR\n");  return RPAR; column+=yyleng; }
";"                                    { if(flag) printf("SEMI\n");  return SEMI; column+=yyleng; }


{RESERVED}                             { if(flag) printf("RESERVED(%s)\n", yytext); yylval.id = strdup(yytext); return RESERVED; column+=yyleng; }
{ID}                                   { if(flag) printf("ID(%s)\n", yytext); yylval.id = strdup(yytext); return ID; column+=yyleng; }
{INTLIT}                               { if(flag) printf("INTLIT(%s)\n", yytext); yylval.id = strdup(yytext); return INTLIT; column+=yyleng; }
{REALLIT}                              { if(flag) printf("REALLIT(%s)\n", yytext); yylval.id = strdup(yytext); return REALLIT; column+=yyleng; }
\'{CHRLIT}\'                           { if(flag) printf("CHRLIT(%s)\n", yytext); yylval.id = strdup(yytext); return CHRLIT; column+=yyleng; }
\'({EXCEPTIONS}|\\.)*'                 { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

"\/\/".*{END_OF_LINE}?                 { line++; column = 1; }
"\/\*"                                 { BEGIN COMMENTS; errorC = column; errorL = line; }

<COMMENTS><<EOF>>                      { printf("Line %d, col %d: unterminated comment\n", errorL, errorC + 2); BEGIN 0; }
<COMMENTS>"\*\/"                       { BEGIN 0; column += yyleng; }
<COMMENTS>\n                           { line++; column = 1; }
<COMMENTS>.                            { column+=yyleng; }

{OTHER}                                { column+=yyleng; }
{END_OF_LINE}                          { line++; column = 1; }
.                                      { printf("Line %d, col %d: illegal character (%s)\n", line, column , yytext); column+= yyleng; }

%%
int main(int argc, char **argv)
{
  if (argc == 2)
  {
    /*Sem flag deve escrever erros lexicais e de sintaxe*/
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

  yylex();
  return 0;
}
int yywrap()
{
  return 1;
}
