%x COMMENTS1 COMMENTS2
ID                  [a-zA-Z][a-zA-Z0-9_]*
INTLIT              [0-9]+
CHRLIT              '([a-zA-Z]|"\\n"|"\\t"|"\\"|"\'"|"\""|"\\"[0-7]{1,3})'
REALLIT             [0-9]+"."[0-9]+([eE][+-]?[0-9]+)?
RESERVED            ("auto"|"long"|"switch"|"break"|"enum"|"register"|"typedef"|"case"|"extern"|"union"|"unsigned"|"union"|"unsigned"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"volatile"|"default"|"static"|"do"|"struct"|"_Packed"|"++"|"--"|"\["|"\]")

%{
  int line = 1;
  int column = 1;
%}

%%

"char"          { printf("CHAR\n"); column+=strlen(yytext); }
"else"          { printf("ELSE\n"); column+=strlen(yytext); }
"while"         { printf("WHILE\n"); column+=strlen(yytext); }
"if"            { printf("IF\n"); column+=strlen(yytext); }
"int"           { printf("INT\n"); column+=strlen(yytext); }
"short"         { printf("SHORT\n"); column+=strlen(yytext); }
"double"        { printf("DOUBLE\n"); column+=strlen(yytext); }
"return"        { printf("RETURN\n"); column+=strlen(yytext); }
"void"          { printf("VOID\n"); column+=strlen(yytext); }
"&"             { printf("BITWISEAND\n"); column+=strlen(yytext); }
"|"             { printf("BITWISEOR\n"); column+=strlen(yytext); }
"^"             { printf("BITWISEXOR\n"); column+=strlen(yytext); }
"&&"            { printf("AND\n"); column+=strlen(yytext); }
"="             { printf("ASSIGN\n"); column+=strlen(yytext); }
"*"             { printf("MUL\n"); column+=strlen(yytext); }
","             { printf("COMMA\n"); column+=strlen(yytext); }
"/"             { printf("DIV\n"); column+=strlen(yytext); }
"=="            { printf("EQ\n"); column+=strlen(yytext); }
">="            { printf("GE\n");column+=strlen(yytext); }
">"             { printf("GT\n"); column+=strlen(yytext); }
"{"             { printf("LBRACE\n"); column+=strlen(yytext); }
"<="            { printf("LE\n"); column+=strlen(yytext); }
"("             { printf("LPAR\n"); column+=strlen(yytext); }
"<"             { printf("LT\n"); column+=strlen(yytext); }
"-"             { printf("MINUS\n"); column+=strlen(yytext); }
"%"             { printf("MOD\n"); column+=strlen(yytext); }
"!="            { printf("NE\n"); column+=strlen(yytext); }
"!"             { printf("NOT\n"); column+=strlen(yytext); }
"||"            { printf("OR\n"); column+=strlen(yytext); }
"+"             { printf("PLUS\n"); column+=strlen(yytext); }
"}"             { printf("RBRACE\n"); column+=strlen(yytext); }
")"             { printf("RPAR\n"); column+=strlen(yytext); }
";"             { printf("SEMI\n"); column+=strlen(yytext); }

{RESERVED}      { printf("RESERVED(%s)\n", yytext); column+=strlen(yytext); }
{ID}            { printf("ID(%s)\n", yytext); column+=strlen(yytext); }
{INTLIT}        { printf("INTLIT(%s)\n", yytext); column+=strlen(yytext); }
{CHRLIT}        { printf("CHRLIT(%s)\n", yytext); column+=strlen(yytext); }
{REALLIT}       { printf("REALLIT(%s)\n", yytext); column+=strlen(yytext); }

"//"            { BEGIN COMMENTS1; }
"/*"            { BEGIN COMMENTS2; }

<COMMENTS1>\n    { BEGIN 0; }
<COMMENTS1>.     { ; }

<COMMENTS2>.     { ; }
<COMMENTS2>"*/" { BEGIN 0; }


" "+    ;
\n  {line++; column = 1;}
.   ;


%%
int main()
{
  yylex();
  return 0;
}
int yywrap()
{
  return 1;
}
