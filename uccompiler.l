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
OTHER               " "|\t
END_OF_LINE         \n|\r\n|\r

%{

  #include "y.tab.h"

  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;

%}

%%

"char"                                 { if(flag) printf("CHAR\n"); column+=yyleng; return CHAR; }
"else"                                 { if(flag) printf("ELSE\n"); column+=yyleng; return ELSE; }
"if"                                   { if(flag) printf("IF\n"); column+=yyleng; return IF; }
"while"                                { if(flag) printf("WHILE\n"); column+=yyleng; return WHILE; }
"int"                                  { if(flag) printf("INT\n"); column+=yyleng; return INT; }
"double"                               { if(flag) printf("DOUBLE\n"); column+=yyleng; return DOUBLE; }
"short"                                { if(flag) printf("SHORT\n"); column+=yyleng; return SHORT; }
"return"                               { if(flag) printf("RETURN\n"); column+=yyleng; return RETURN; }
"void"                                 { if(flag) printf("VOID\n"); column+=yyleng; return VOID; }
"&"                                    { if(flag) printf("BITWISEAND\n"); column+=yyleng; return BITWISEAND; }
"|"                                    { if(flag) printf("BITWISEOR\n"); column+=yyleng; return BITWISEOR; }
"^"                                    { if(flag) printf("BITWISEXOR\n"); column+=yyleng; return BITWISEXOR; }
"&&"                                   { if(flag) printf("AND\n"); column+=yyleng; return AND; }
"="                                    { if(flag) printf("ASSIGN\n"); column+=yyleng; return ASSIGN; }
"*"                                    { if(flag) printf("MUL\n"); column+=yyleng; return MUL; }
","                                    { if(flag) printf("COMMA\n"); column+=yyleng; return COMMA; }
"/"                                    { if(flag) printf("DIV\n"); column+=yyleng; return DIV; }
"=="                                   { if(flag) printf("EQ\n"); column+=yyleng; return EQ; }
">="                                   { if(flag) printf("GE\n"); column+=yyleng; return GE; }
">"                                    { if(flag) printf("GT\n"); column+=yyleng; return GT; }
"{"                                    { if(flag) printf("LBRACE\n"); column+=yyleng; return LBRACE; }
"<="                                   { if(flag) printf("LE\n"); column+=yyleng; return LE; }
"("                                    { if(flag) printf("LPAR\n"); column+=yyleng; return LPAR; }
"<"                                    { if(flag) printf("LT\n"); column+=yyleng; return LT; }
"-"                                    { if(flag) printf("MINUS\n"); column+=yyleng; return MINUS; }
"%"                                    { if(flag) printf("MOD\n"); column+=yyleng; return MOD; }
"!="                                   { if(flag) printf("NE\n"); column+=yyleng; return NE; }
"!"                                    { if(flag) printf("NOT\n"); column+=yyleng; return NOT; }
"||"                                   { if(flag) printf("OR\n"); column+=yyleng; return OR; }
"+"                                    { if(flag) printf("PLUS\n"); column+=yyleng; return PLUS; }
"}"                                    { if(flag) printf("RBRACE\n"); column+=yyleng; return RBRACE; }
")"                                    { if(flag) printf("RPAR\n"); column+=yyleng; return RPAR; }
";"                                    { if(flag) printf("SEMI\n"); column+=yyleng; return SEMI; }

{RESERVED}                             { if(flag) printf("RESERVED(%s)\n", yytext); yylval.id = strdup(yytext); column+=yyleng; return RESERVED; }
{ID}                                   { if(flag) printf("ID(%s)\n", yytext); yylval.id = (char* ) strdup(yytext); column+=yyleng; return ID; }
{INTLIT}                               { if(flag) printf("INTLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return INTLIT; }
{REALLIT}                              { if(flag) printf("REALLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return REALLIT; }
\'{CHRLIT}\'                           { if(flag) printf("CHRLIT(%s)\n", yytext); yylval.id = (char*) strdup(yytext); column+=yyleng; return CHRLIT; }
\'({EXCEPTIONS}|\\.)*'                 { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

"\/\/".*{END_OF_LINE}?                 { line++; column = 1; }
"\/\*"                                 { BEGIN COMMENTS; errorC = column; errorL = line; }

<COMMENTS><<EOF>>                      { printf("Line %d, col %d: unterminated comment\n", errorL, errorC + 2); BEGIN 0; }
<COMMENTS>"\*\/"                       { BEGIN 0; column += yyleng; }
<COMMENTS>\n                           { line++; column = 1; }
<COMMENTS>.                            {  }

{OTHER}                                {  }
{END_OF_LINE}                          { line++; column = 1; }
.                                      { printf("Line %d, col %d: illegal character (%s)\n", line, column , yytext); column+= yyleng; }

%%

void yyerror (char *s)
{
    printf("Line %d, col %d: %s: %s\n", errorL , errorC, s, yytext);
}

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

  yyparse();
  return 0;
}

int yywrap()
{
  return 1;
}
