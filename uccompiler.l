%x COMMENTS
ID                  [a-zA-Z][a-zA-Z0-9_]*
INTLIT              [0-9]+
CHRLIT              '([a-zA-Z]|"\\n"|"\\t"|"\\"|"\'"|"\""|"\\"[0-7]{1,3})'
REALLIT             [0-9]+"."[0-9]+([eE][+-]?[0-9]+)?
%%

"char"          { printf("CHAR\n"); }
"else"          { printf("ELSE\n"); }
"while"         { printf("WHILE\n"); }
"if"            { printf("IF\n"); }
"int"           { printf("INT\n"); }
"short"         { printf("SHORT\n"); }
"double"        { printf("DOUBLE\n"); }
"return"        { printf("RETURN\n");}
"void"          { printf("VOID\n");}
"&"             { printf("BITWISEAND\n");}
"|"             { printf("BITWISEOR\n");}
"^"             { printf("BITWISEXOR\n"); }
"&&"            { printf("AND\n"); }
"="             { printf("ASSIGN\n"); }
"*"             { printf("MUL\n"); }
","             { printf("COMMA\n"); }
"/"             { printf("DIV\n"); }
"=="            { printf("EQ\n"); }
">="            { printf("GE\n");}
">"             { printf("GT\n");}
"{"             { printf("LBRACE\n");}
"<="            { printf("LE\n");}
"("             { printf("LPAR\n"); }
"<"             { printf("LT\n"); }
"-"             { printf("MINUS\n"); }
"%"             { printf("MOD\n"); }
"!="            { printf("NE\n"); }
"!"             { printf("NOT\n"); }
"||"            { printf("OR\n"); }
"+"             { printf("PLUS\n"); }
"}"             { printf("RBRACE\n"); }
")"             { printf("RPAR\n"); }
";"             { printf("SEMI\n"); }
{ID}            {printf("ID(%s)\n", yytext); }
{INTLIT}        {printf("INTLIT(%s)\n", yytext); }
{CHRLIT}        {printf("CHRLIT(%s)\n", yytext); }
{REALLIT}       {printf("REALLIT(%s)\n", yytext); }
"//"            { BEGIN COMMENTS; }

<COMMENTS>\n    { BEGIN 0; }
<COMMENTS>.    { ; }


" "+    ;
\n ; //nao faz nada
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
