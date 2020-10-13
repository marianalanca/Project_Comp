%x COMMENTS CHRLIT_STATE
ID                  [a-zA-Z_][a-zA-Z0-9_]*
INTLIT              [0-9]+
CHRLIT              ([a-zA-Z0-9]|"\""|"\\n"|"\\t"|"\\\\"|"\\\'"|"\\\""|"\\"[0-7]{1,3}|\t)
REALLIT             (([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+))([eE][+-]?[0-9]+)?
RESERVED            ("auto"|"long"|"switch"|"break"|"enum"|"float"|"register"|"typedef"|"case"|"extern"|"union"|"unsigned"|"union"|"unsigned"|"const"|"for"|"signed"|"continue"|"goto"|"sizeof"|"volatile"|"default"|"static"|"do"|"struct"|"_Packed"|"++"|"--"|"\["|"\]")
OTHER               ";"|" "|\t

%{
  int line = 1;
  int column = 1;
  int flag = 0;
  int errorC, errorL;

  void print(char* string, int type)
  {
    if (flag == 1){
        printf("%s", string);
    }
  }
%}

%%

"char"          { print("CHAR\n", flag); column+=yyleng; }
"else"          { print("ELSE\n", flag); column+=yyleng; }
"while"         { print("WHILE\n", flag); column+=yyleng; }
"if"            { print("IF\n", flag); column+=yyleng; }
"int"           { print("INT\n", flag); column+=yyleng; }
"short"         { print("SHORT\n", flag); column+=yyleng; }
"double"        { print("DOUBLE\n", flag); column+=yyleng; }
"return"        { print("RETURN\n", flag); column+=yyleng; }
"void"          { print("VOID\n", flag); column+=yyleng; }
"&"             { print("BITWISEAND\n", flag); column+=yyleng; }
"|"             { print("BITWISEOR\n", flag); column+=yyleng; }
"^"             { print("BITWISEXOR\n", flag); column+=yyleng; }
"&&"            { print("AND\n", flag); column+=yyleng; }
"="             { print("ASSIGN\n", flag); column+=yyleng; }
"*"             { print("MUL\n", flag); column+=yyleng; }
","             { print("COMMA\n", flag); column+=yyleng; }
"/"             { print("DIV\n", flag); column+=yyleng; }
"=="            { print("EQ\n", flag); column+=yyleng; }
">="            { print("GE\n", flag);column+=yyleng; }
">"             { print("GT\n", flag); column+=yyleng; }
"{"             { print("LBRACE\n", flag); column+=yyleng; }
"<="            { print("LE\n", flag); column+=yyleng; }
"("             { print("LPAR\n", flag); column+=yyleng; }
"<"             { print("LT\n", flag); column+=yyleng; }
"-"             { print("MINUS\n", flag); column+=yyleng; }
"%"             { print("MOD\n", flag); column+=yyleng; }
"!="            { print("NE\n", flag); column+=yyleng; }
"!"             { print("NOT\n", flag); column+=yyleng; }
"||"            { print("OR\n", flag); column+=yyleng; }
"+"             { print("PLUS\n", flag); column+=yyleng; }
"}"             { print("RBRACE\n", flag); column+=yyleng; }
")"             { print("RPAR\n", flag); column+=yyleng; }
";"             { print("SEMI\n", flag); column+=yyleng; }

{RESERVED}      { if(flag ==1 ) printf("RESERVED(%s)\n", yytext); column+=yyleng; }
{ID}            { if(flag ==1 ) printf("ID(%s)\n", yytext); column+=yyleng; }
{INTLIT}        { if(flag ==1 ) printf("INTLIT(%s)\n", yytext); column+=yyleng; }
{REALLIT}       { if(flag ==1 ) printf("REALLIT(%s)\n", yytext); column+=yyleng; }
"\'"            { BEGIN CHRLIT_STATE; errorC = column; errorL = line; }

"//".*\n        { line++; column = 1; }
"/*"            { BEGIN COMMENTS; errorC = column; errorL = line; }

<CHRLIT_STATE>{CHRLIT}'      { if (flag == 1) printf("CHRLIT('%s)\n", yytext); column+=yyleng; column+=2; BEGIN 0; }
<CHRLIT_STATE>{CHRLIT}*'     { printf("Line %d, col %d: invalid char constant ('%s)\n", errorL, errorC , yytext); column+=yyleng + 1; BEGIN 0; }
<CHRLIT_STATE>.+'            { printf("Line %d, col %d: illegal character ('%s)\n", errorL, errorC , yytext); column+=yyleng + 1; BEGIN 0; }
<CHRLIT_STATE>\n | <<EOF>>   { printf("Line %d, col %d:unterminated char constant\n", errorL, errorC); return 1; }
<CHRLIT_STATE>.              { column+=yyleng; }

<COMMENTS>.     { column++; }
<COMMENTS>\n    { line++; column = 1; }
<COMMENTS>"*/"  { BEGIN 0; }
<COMMENTS><<EOF>>  { printf("Line %d, col %d: unterminated comment\n", errorL, errorC); BEGIN 0; }


\n  {line++; column = 1;}
{OTHER} { column+= yyleng; }
.   { printf("Line %d, col %d: illegal character ('%s')\n", line, column , yytext); column++; }


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
