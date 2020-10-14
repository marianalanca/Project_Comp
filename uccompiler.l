%x COMMENTS
ID                  [a-zA-Z\_][a-zA-Z0-9\_]*
INTLIT              [0-9]
EXCEPTIONS          [^\'\\\n]
EXPONENT            [eE][+-]?{INTLIT}
REALLIT             ((({INTLIT}+"."?{INTLIT}*)|({INTLIT}*"."?{INTLIT}+))([eE][+-]?{INTLIT}+)?)
RESERVED            ("auto"|"long"|"switch"|"break"|"enum"|"float"|"register"|"typedef"|"case"|"extern"|"union"|"unsigned"|"union"|"unsigned"|"restrict"|"inline"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"volatile"|"default"|"static"|"do"|"struct"|"_Packed"|"_Bool"|"_Complex"|"_Imaginary"|"++"|"--"|"\["|"\]")
OTHER               " "|\t

%{
  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;

  void print(char* string)
  {
    if (flag == 1){
        printf("%s", string);
    }
  }
%}

%%

"char"                                 { print("CHAR\n"); column+=yyleng; }
"else"                                 { print("ELSE\n"); column+=yyleng; }
"while"                                { print("WHILE\n"); column+=yyleng; }
"if"                                   { print("IF\n"); column+=yyleng; }
"int"                                  { print("INT\n"); column+=yyleng; }
"short"                                { print("SHORT\n"); column+=yyleng; }
"double"                               { print("DOUBLE\n"); column+=yyleng; }
"return"                               { print("RETURN\n"); column+=yyleng; }
"void"                                 { print("VOID\n"); column+=yyleng; }
"&"                                    { print("BITWISEAND\n"); column+=yyleng; }
"|"                                    { print("BITWISEOR\n"); column+=yyleng; }
"^"                                    { print("BITWISEXOR\n"); column+=yyleng; }
"&&"                                   { print("AND\n"); column+=yyleng; }
"="                                    { print("ASSIGN\n"); column+=yyleng; }
"*"                                    { print("MUL\n"); column+=yyleng; }
","                                    { print("COMMA\n"); column+=yyleng; }
"/"                                    { print("DIV\n"); column+=yyleng; }
"=="                                   { print("EQ\n"); column+=yyleng; }
">="                                   { print("GE\n");column+=yyleng; }
">"                                    { print("GT\n"); column+=yyleng; }
"{"                                    { print("LBRACE\n"); column+=yyleng; }
"<="                                   { print("LE\n"); column+=yyleng; }
"("                                    { print("LPAR\n"); column+=yyleng; }
"<"                                    { print("LT\n"); column+=yyleng; }
"-"                                    { print("MINUS\n"); column+=yyleng; }
"%"                                    { print("MOD\n"); column+=yyleng; }
"!="                                   { print("NE\n"); column+=yyleng; }
"!"                                    { print("NOT\n"); column+=yyleng; }
"||"                                   { print("OR\n"); column+=yyleng; }
"+"                                    { print("PLUS\n"); column+=yyleng; }
"}"                                    { print("RBRACE\n"); column+=yyleng; }
")"                                    { print("RPAR\n"); column+=yyleng; }
";"                                    { print("SEMI\n"); column+=yyleng; }

{RESERVED}                             { if(flag ==1 ) printf("RESERVED(%s)\n", yytext); column+=yyleng; }
{ID}                                   { if(flag ==1 ) printf("ID(%s)\n", yytext); column+=yyleng; }
{INTLIT}+                              { if(flag ==1 ) printf("INTLIT(%s)\n", yytext); column+=yyleng; }
{REALLIT}                              { if(flag ==1 ) printf("REALLIT(%s)\n", yytext); column+=yyleng; }

\'{CHRLIT}\'                           { if(flag ==1 ) printf("CHRLIT(%s)\n", yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*\'                { printf("Line %d, col %d: invalid char constant (%s)\n", line, column , yytext); column+=yyleng; }
\'({EXCEPTIONS}|\\.)*(\\)?             { printf("Line %d, col %d: unterminated char constant\n", line, column); column+= yyleng; }

"\/\/".*(\n|\r\n)                      { line++; column = 1; }
"\/\*"                                 { BEGIN COMMENTS; errorC = column; errorL = line; }

<COMMENTS><<EOF>>                      { printf("Line %d, col %d: unterminated comment\n", errorL, errorC + 2); BEGIN 0; }
<COMMENTS>"\*\/"                       { BEGIN 0; column += yyleng; }
<COMMENTS>\n                           { line++; column = 1; }
<COMMENTS>.                            { column++; }

{OTHER}                                { column+= yyleng; }
\n|\r\n                                { line++; column = 1; }
.                                      { printf("Line %d, col %d: illegal character (%s)\n", line, column , yytext); column++; }

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
