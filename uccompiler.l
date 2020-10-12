%x COMMENTS CHRLIT_STATE
ID                  [a-zA-Z][a-zA-Z0-9_]*
INTLIT              [0-9]+
CHRLIT              ([a-zA-Z]|"\""|"|"\\n"|"\\t"|"\\"|"\\'"|"\\""|"\\"[0-7]{1,3})
REALLIT             [0-9]+"."[0-9]+([eE][+-]?[0-9]+)?
RESERVED            ("auto"|"long"|"switch"|"break"|"enum"|"register"|"typedef"|"case"|"extern"|"union"|"unsigned"|"union"|"unsigned"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"volatile"|"default"|"static"|"do"|"struct"|"_Packed"|"++"|"--"|"\["|"\]")

%{
  int line = 1;
  int column = 1;
  int errorC, errorL;

  /*void print(char* string, int flag){
    if (flag==flag){

    }
    else {
      if (flag==0){

      }else {

      }
    }
  }*/
%}

%%

"char"          { printf("CHAR\n"); column+=yyleng; }
"else"          { printf("ELSE\n"); column+=yyleng; }
"while"         { printf("WHILE\n"); column+=yyleng; }
"if"            { printf("IF\n"); column+=yyleng; }
"int"           { printf("INT\n"); column+=yyleng; }
"short"         { printf("SHORT\n"); column+=yyleng; }
"double"        { printf("DOUBLE\n"); column+=yyleng; }
"return"        { printf("RETURN\n"); column+=yyleng; }
"void"          { printf("VOID\n"); column+=yyleng; }
"&"             { printf("BITWISEAND\n"); column+=yyleng; }
"|"             { printf("BITWISEOR\n"); column+=yyleng; }
"^"             { printf("BITWISEXOR\n"); column+=yyleng; }
"&&"            { printf("AND\n"); column+=yyleng; }
"="             { printf("ASSIGN\n"); column+=yyleng; }
"*"             { printf("MUL\n"); column+=yyleng; }
","             { printf("COMMA\n"); column+=yyleng; }
"/"             { printf("DIV\n"); column+=yyleng; }
"=="            { printf("EQ\n"); column+=yyleng; }
">="            { printf("GE\n");column+=yyleng; }
">"             { printf("GT\n"); column+=yyleng; }
"{"             { printf("LBRACE\n"); column+=yyleng; }
"<="            { printf("LE\n"); column+=yyleng; }
"("             { printf("LPAR\n"); column+=yyleng; }
"<"             { printf("LT\n"); column+=yyleng; }
"-"             { printf("MINUS\n"); column+=yyleng; }
"%"             { printf("MOD\n"); column+=yyleng; }
"!="            { printf("NE\n"); column+=yyleng; }
"!"             { printf("NOT\n"); column+=yyleng; }
"||"            { printf("OR\n"); column+=yyleng; }
"+"             { printf("PLUS\n"); column+=yyleng; }
"}"             { printf("RBRACE\n"); column+=yyleng; }
")"             { printf("RPAR\n"); column+=yyleng; }
";"             { printf("SEMI\n"); column+=yyleng; }

{RESERVED}      { printf("RESERVED(%s)\n", yytext); column+=yyleng; }
{ID}            { printf("ID(%s)\n", yytext); column+=yyleng; }
{INTLIT}        { printf("INTLIT(%s)\n", yytext); column+=yyleng; }
{REALLIT}       { printf("REALLIT(%s)\n", yytext); column+=yyleng; }
"\'"            { BEGIN CHRLIT_STATE; errorC = column; errorL = line; }

"//".*\n        { line++; }
"/*"            { BEGIN COMMENTS; }

<CHRLIT_STATE>{CHRLIT}'      { yytext[yyleng - 1] = '\0'; printf("CHRLIT(%s)\n", yytext); column+=yyleng; column+=2; BEGIN 0; }
<CHRLIT_STATE>{CHRLIT}*'     { yytext[yyleng - 1] = '\0'; printf("Line %d, col %d: invalid char constant (%s)\n", errorL, errorC , yytext); column+=yyleng + 1; BEGIN 0; }
<CHRLIT_STATE>.+'            { yytext[yyleng - 1] = '\0'; printf("Line %d, col %d: illegal character (%s)\n", errorL, errorC , yytext); column+=yyleng + 1; BEGIN 0; }
<CHRLIT_STATE><<EOF>>        { printf("Line %d, col %d:unterminated char constant\n", errorL, errorC); BEGIN 0;}
<CHRLIT_STATE>.              { column+=yyleng; }
<CHRLIT_STATE>\n             { line++; column = 1; }

<COMMENTS>.     { column+=yyleng; }
<COMMENTS>\n    { line++; column = 1; }
<COMMENTS>"*/"  { BEGIN 0; }
<COMMENTS><<EOF>>  { printf("Line %d, col %d: unterminated comment\n", line, column); BEGIN 0; }




\n  {line++; column = 1;}
.   { column++; }


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
