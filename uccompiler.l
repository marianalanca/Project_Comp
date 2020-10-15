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

  void print(char* string)
  {
    if (flag){
        printf("%s", string);
    }
  }
%}

%%

"char"                                 { if(flag) print("CHAR\n"); column+=yyleng; }
"else"                                 { if(flag) print("ELSE\n"); column+=yyleng; }
"if"                                   { if(flag) print("IF\n"); column+=yyleng; }
"while"                                { if(flag) print("WHILE\n"); column+=yyleng; }
"int"                                  { if(flag) print("INT\n"); column+=yyleng; }
"double"                               { if(flag) print("DOUBLE\n"); column+=yyleng; }
"short"                                { if(flag) print("SHORT\n"); column+=yyleng; }
"return"                               { if(flag) print("RETURN\n"); column+=yyleng; }
"void"                                 { if(flag) print("VOID\n"); column+=yyleng; }
"&"                                    { if(flag) print("BITWISEAND\n"); column+=yyleng; }
"|"                                    { if(flag) print("BITWISEOR\n"); column+=yyleng; }
"^"                                    { if(flag) print("BITWISEXOR\n"); column+=yyleng; }
"&&"                                   { if(flag) print("AND\n"); column+=yyleng; }
"="                                    { if(flag) print("ASSIGN\n"); column+=yyleng; }
"*"                                    { if(flag) print("MUL\n"); column+=yyleng; }
","                                    { if(flag) print("COMMA\n"); column+=yyleng; }
"/"                                    { if(flag) print("DIV\n"); column+=yyleng; }
"=="                                   { if(flag) print("EQ\n"); column+=yyleng; }
">="                                   { if(flag) print("GE\n");column+=yyleng; }
">"                                    { if(flag) print("GT\n"); column+=yyleng; }
"{"                                    { if(flag) print("LBRACE\n"); column+=yyleng; }
"<="                                   { if(flag) print("LE\n"); column+=yyleng; }
"("                                    { if(flag) print("LPAR\n"); column+=yyleng; }
"<"                                    { if(flag) print("LT\n"); column+=yyleng; }
"-"                                    { if(flag) print("MINUS\n"); column+=yyleng; }
"%"                                    { if(flag) print("MOD\n"); column+=yyleng; }
"!="                                   { if(flag) print("NE\n"); column+=yyleng; }
"!"                                    { if(flag) print("NOT\n"); column+=yyleng; }
"||"                                   { if(flag) print("OR\n"); column+=yyleng; }
"+"                                    { if(flag) print("PLUS\n"); column+=yyleng; }
"}"                                    { if(flag) print("RBRACE\n"); column+=yyleng; }
")"                                    { if(flag) print("RPAR\n"); column+=yyleng; }
";"                                    { if(flag) print("SEMI\n"); column+=yyleng; }


{RESERVED}                             { if(flag) printf("RESERVED(%s)\n", yytext); column+=yyleng; }
{ID}                                   { if(flag) printf("ID(%s)\n", yytext); column+=yyleng; }
{INTLIT}                               { if(flag) printf("INTLIT(%s)\n", yytext); column+=yyleng; }
{REALLIT}                              { if(flag) printf("REALLIT(%s)\n", yytext); column+=yyleng; }

\'{CHRLIT}\'                           { if(flag) printf("CHRLIT(%s)\n", yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*'                 { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

"\/\/".*{END_OF_LINE}                  { line++; column = 1; }
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
