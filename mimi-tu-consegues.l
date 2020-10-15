%{
    /*
        João Alexandre Santos Cruz 2018288464
        André Cristóvão Ferreira da Silva  2018277921
    */

    #include <stdio.h>
    #include <stdlib.h>
    int linha=1;
    int coluna=1;
    int flag=0,printM=0;
    int flagError=0;
    int erroC = 0, erroL =0;
%}
%X COMMENT
INTLIT         [0-9]+
signal        [+-]
exp [eE]
nExp    {exp}{signal}?{INTLIT}
SPACE           ([ ]|"\t")
ENTER   \\n 
ASPAS           \\\"
BARRA       \\\\
PLICA           \\\'
SEQUENCIA       \\[0-7]{1,3}
TAB             \\t
REALLIT        (({INTLIT}".")|({INTLIT}"."{INTLIT})|{INTLIT}"."{INTLIT}{nExp}|{INTLIT}"."{nExp}|"."{INTLIT}{nExp}|{INTLIT}{nExp}|"."{INTLIT})
CHRLIT     ([^\n\'\\]|{ENTER}|{ASPAS}|{PLICA}|{SEQUENCIA}|{TAB}|{BARRA})
ENDOFFILE   <<EOF>>
RESERVED        "auto"|"break"|"const"|"continue"|"asm"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"register"|"long"|"signed"|"unsigned"|"sizeof"|"static"|"struct"|"switch"|"case"|"default"|"typedef"|"union"|"volatile"|"break"|"_Bool"|"_Imaginary"|"restrict"|"inline"|"_Complex"|"["|"]"|"++"|"--"
ID                  [a-zA-Z_][a-zA-Z0-9_]*
LPAR                "("
LT                  "<"
MINUS               "-"
MOD                 "%"
NE                  "!="
NOT                 "!"
OR                  "||"
PLUS                "+"
RBRACE              "}"
RPAR                ")"
SEMI                ";"
ELSE                "else"
IF      "if"
CHAR                "char"
WHILE      "while"
INT         "int"
SHORT   "short"
DOUBLE  "double"
RETURN  "return"
VOID    "void"
BAND "&"
BOR  "|"
BXOR "^"
AND "&&"
ASSIGN  "="
MUL "*"
COMMA   ","
DIV "/"
EQ  "=="
GE  ">="
GT  ">"
LBRACE  "{"
LE  "<="
%%
\/\*              {BEGIN COMMENT;erroC=coluna;erroL=linha;coluna+=yyleng;}
\/\/.*            {coluna+=yyleng;}         
<COMMENT>.        {coluna+=yyleng;}
<COMMENT>\n       {linha++;coluna=1;}
<COMMENT>\*\/     {BEGIN 0;coluna+=yyleng;}
<COMMENT><<EOF>>   {if(flagError)printf("Line %d, col %d: unterminated comment\n",erroL,erroC); BEGIN 0;}
{CHAR}  {if(flag)printf("CHAR\n");coluna+=yyleng;}
{ELSE} {if(flag)printf("ELSE\n");coluna+=yyleng;}
{IF} {if(flag)printf("IF\n");coluna+=yyleng;}
{WHILE} {if(flag)printf("WHILE\n");coluna+=yyleng;}
{INT}   {if(flag)printf("INT\n");coluna+=yyleng;}
{DOUBLE}   {if(flag)printf("DOUBLE\n");coluna+=yyleng;}
{SHORT} {if(flag)printf("SHORT\n");coluna+=yyleng;}
{RETURN}   {if(flag)printf("RETURN\n");coluna+=yyleng;}
{VOID} {if(flag)printf("VOID\n");coluna+=yyleng;}
{BAND} {if(flag)printf("BITWISEAND\n");coluna+=yyleng;}
{BOR} {if(flag)printf("BITWISEOR\n");coluna+=yyleng;}
{BXOR} {if(flag)printf("BITWISEXOR\n");coluna+=yyleng;}
{AND}    {if(flag)printf("AND\n");coluna+=yyleng;}
{ASSIGN} {if(flag)printf("ASSIGN\n");coluna+=yyleng;}
{MUL}   {if(flag)printf("MUL\n");coluna+=yyleng;}
{COMMA} {if(flag)printf("COMMA\n");coluna+=yyleng;}
{DIV} {if(flag)printf("DIV\n");coluna+=yyleng;}
{EQ}   {if(flag)printf("EQ\n");coluna+=yyleng;}
{GE}    {if(flag)printf("GE\n");coluna+=yyleng;}
{GT} {if(flag)printf("GT\n");coluna+=yyleng;}
{LBRACE} {if(flag)printf("LBRACE\n");coluna+=yyleng;}
{LE} {if(flag)printf("LE\n");coluna+=yyleng;}
{LPAR}  {if(flag)printf("LPAR\n");coluna+=yyleng;}
{LT}    {if(flag)printf("LT\n");coluna+=yyleng;}
{MINUS} {if(flag)printf("MINUS\n");coluna+=yyleng;}
{MOD}               {if(flag)printf("MOD\n");coluna+=yyleng;}
{NE}                  {if(flag)printf("NE\n");coluna+=yyleng;}
{NOT}                 {if(flag)printf("NOT\n");coluna+=yyleng;}
{OR}                  {if(flag)printf("OR\n");coluna+=yyleng;}
{PLUS}               {if(flag)printf("PLUS\n");coluna+=yyleng;}
{RBRACE}             {if(flag)printf("RBRACE\n");coluna+=yyleng;}
{RPAR}                {if(flag)printf("RPAR\n");coluna+=yyleng;}
{SEMI}  {if(flag)printf("SEMI\n");coluna+=yyleng;}
{RESERVED}  {if(flag)printf("RESERVED(%s)\n",yytext);coluna+=yyleng;}
{ID}    {if(flag)printf("ID(%s)\n",yytext);coluna+=yyleng;}
{INTLIT}  {if(flag)printf("INTLIT(%s)\n",yytext);coluna+=yyleng;}
{REALLIT}   {if(flag)printf("REALLIT(%s)\n",yytext);coluna+=yyleng;} 
\'{CHRLIT}\'    {if(flag)printf("CHRLIT(%s)\n",yytext);coluna+=yyleng;} 
\'([^\n\'\\]|\\.)*\'  {printf("Line %d, col %d: invalid char constant (%s)\n",linha,coluna,yytext);coluna+=yyleng;}
\'([^\n\'\\]|\\.)*(\\)?    {printf("Line %d, col %d: unterminated char constant\n",linha,coluna);coluna+=yyleng;}
\n|"\r\n"|"\r"    {linha++;coluna=1;}
{SPACE} {coluna+=yyleng;}
.   {if(flagError)printf("Line %d, col %d: illegal character (%s)\n",linha,coluna,yytext);coluna+=yyleng;}
%%                  
int main(int argc, char **argv)
{
    if(argc>1){
        if (argv[1][0]=='-' && argv[1][1]=='l'){
            flag=1;
            printM=1;
            flagError=1;
        }
    }
    flagError=1;
yylex();
return 0;
}

int yywrap()
{
return 1;
}