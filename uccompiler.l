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
  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;
%}

%%

"\/\/".*{END_OF_LINE}                  { line++; column = 1; }
"\/\*"                                 { BEGIN COMMENTS; errorC = column; errorL = line; }

"char"                                 { if(flag) printf("CHAR\n"); column+=yyleng; }
"else"                                 { if(flag) printf("ELSE\n"); column+=yyleng; }
"if"                                   { if(flag) printf("IF\n"); column+=yyleng; }
"while"                                { if(flag) printf("WHILE\n"); column+=yyleng; }
"int"                                  { if(flag) printf("INT\n"); column+=yyleng; }
"double"                               { if(flag) printf("DOUBLE\n"); column+=yyleng; }
"short"                                { if(flag) printf("SHORT\n"); column+=yyleng; }
"return"                               { if(flag) printf("RETURN\n"); column+=yyleng; }
"void"                                 { if(flag) printf("VOID\n"); column+=yyleng; }
"&"                                    { if(flag) printf("BITWISEAND\n"); column+=yyleng; }
"|"                                    { if(flag) printf("BITWISEOR\n"); column+=yyleng; }
"^"                                    { if(flag) printf("BITWISEXOR\n"); column+=yyleng; }
"&&"                                   { if(flag) printf("AND\n"); column+=yyleng; }
"="                                    { if(flag) printf("ASSIGN\n"); column+=yyleng; }
"*"                                    { if(flag) printf("MUL\n"); column+=yyleng; }
","                                    { if(flag) printf("COMMA\n"); column+=yyleng; }
"/"                                    { if(flag) printf("DIV\n"); column+=yyleng; }
"=="                                   { if(flag) printf("EQ\n"); column+=yyleng; }
">="                                   { if(flag) printf("GE\n");column+=yyleng; }
">"                                    { if(flag) printf("GT\n"); column+=yyleng; }
"{"                                    { if(flag) printf("LBRACE\n"); column+=yyleng; }
"<="                                   { if(flag) printf("LE\n"); column+=yyleng; }
"("                                    { if(flag) printf("LPAR\n"); column+=yyleng; }
"<"                                    { if(flag) printf("LT\n"); column+=yyleng; }
"-"                                    { if(flag) printf("MINUS\n"); column+=yyleng; }
"%"                                    { if(flag) printf("MOD\n"); column+=yyleng; }
"!="                                   { if(flag) printf("NE\n"); column+=yyleng; }
"!"                                    { if(flag) printf("NOT\n"); column+=yyleng; }
"||"                                   { if(flag) printf("OR\n"); column+=yyleng; }
"+"                                    { if(flag) printf("PLUS\n"); column+=yyleng; }
"}"                                    { if(flag) printf("RBRACE\n"); column+=yyleng; }
")"                                    { if(flag) printf("RPAR\n"); column+=yyleng; }
";"                                    { if(flag) printf("SEMI\n"); column+=yyleng; }


{RESERVED}                             { if(flag) printf("RESERVED(%s)\n", yytext); column+=yyleng; }
{ID}                                   { if(flag) printf("ID(%s)\n", yytext); column+=yyleng; }
{INTLIT}                               { if(flag) printf("INTLIT(%s)\n", yytext); column+=yyleng; }
{REALLIT}                              { if(flag) printf("REALLIT(%s)\n", yytext); column+=yyleng; }
\'{CHRLIT}\'                           { if(flag) printf("CHRLIT(%s)\n", yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*'                 { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

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
    if(strcmp(argv[1], "-l")==0)
    {
      flag = 1;
    }
  }

  yylex();
  return 0;
}
int yywrap()
{
  return 1;
}
