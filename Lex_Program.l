%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int lineno = 1;
    void ret_print(char *token_type);
    void yyerror();
	
%}
%x ML_COMMENT
preprocessor_directives #.*
alpha       [a-zA-Z]
digit       [0-9]
alnum       {alpha}|{digit}
print       [ -~]
ARRAY       ({alpha}+{alnum}*"[".+"]")|({alpha}+{alnum}*"["+"]")

ICONST      "0"|[0-9]{digit}*
FCONST      "0"|{digit}*"."{digit}+
CCONST      (\'{print}\')|(\'\\[nftrbv]\')
STRING      \"{print}*\"
%%
"//".*                  { printf("Eat up comment at line %d\n", lineno); } 
"/*"                    { printf("Eat up comment from line %d ", lineno); BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"        { printf("to line %d\n", lineno); BEGIN(INITIAL); }
<ML_COMMENT>[^*\n]+     
<ML_COMMENT>"*"         
<ML_COMMENT>"\n"        { lineno += 1; }
"char"|"CHAR"           { ret_print("KEYWORD_CHAR"); }
"int"|"INT"             { ret_print("KEYWORD_INT"); }
"float"|"FLOAT"         { ret_print("KEYWORD_FLOAT"); }
"double"|"DOUBLE"       { ret_print("KEYWORD_DOUBLE"); }
"if"|"IF"               { ret_print("KEYWORD_IF"); }
"else"|"ELSE"           { ret_print("KEYWORD_ELSE"); }
"while"|"WHILE"         { ret_print("KEYWORD_WHILE"); }
"for"|"FOR"             { ret_print("KEYWORD_FOR"); }
"continue"|"CONTINUE"   { ret_print("KEYWORD_CONTINUE"); }
"break"|"BREAK"         { ret_print("KEYWORD_BREAK"); }
"void"|"VOID"           { ret_print("KEYWORD_VOID"); }
"return"|"RETURN"       { ret_print("KEYWORD_RETURN"); }
"+"|"-"                 { ret_print("ADDOP"); }
"*"                     { ret_print("MULOP"); }
"/"                     { ret_print("DIVOP"); }
"++"|"--"               { ret_print("INCR"); }
"||"                    { ret_print("OROP"); }
"&&"                    { ret_print("ANDOP"); }
"!"                     { ret_print("NOTOP"); }
"=="|"!="               { ret_print("EQUOP"); }
">"|"<"|">="|"<="       { ret_print("RELOP"); }
"("             { ret_print("LPAREN"); }
")"             { ret_print("RPAREN"); }
"["             { ret_print("LBRACK"); }
"]"             { ret_print("RBRACK"); }
"{"             { ret_print("LBRACE"); }
"}"             { ret_print("RBRACE"); }
";"             { ret_print("SEMI"); }
"."             { ret_print("DOT"); }
","             { ret_print("COMMA"); }
"="             { ret_print("ASSIGN"); }
"&"             { ret_print("REFER"); }
{preprocessor_directives} { ret_print("PREPROCESSOR DIRECTIVES"); }
{ARRAY}         { ret_print("ARRAY"); }
{ICONST}        { ret_print("ICONST"); }
{FCONST}        { ret_print("FCONST"); }
{CCONST}        { ret_print("CCONST"); }
{STRING}        { ret_print("STRING"); }
"main"          {ret_print("MAIN");}
"printf"        {ret_print("PRINTF function");}
"scanf"         {ret_print("SCANF function");}
"\n"            { lineno += 1; }
[ \t\r\f]+          /* eat up whitespace */

.               { yyerror("Unrecognized character"); }

%%
int a;
void ret_print(char *token_type){
    a++;
    printf("yytext: %s\ttoken: %s\tlineno: %d\n", yytext, token_type, lineno);
	fprintf(yyout,"%s\n",yytext);
}
 
void yyerror(char *message){
    printf("Error: \"%s\" in line %d. Token = %s\n", message, lineno, yytext);
    
    exit(1);
}
 
int main(int argc, char *argv[]){
    
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");
    yylex();
    fclose(yyin);
    fclose(yyout);
    printf("Total Lexemes %d", a);
    return 0;
}