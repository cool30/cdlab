#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*

Program  --->  main(){ declarations statement-list }
Declarations --->  data-type identifier-list; declarations | null
data-type ---> int | char

id, is alpha  id is beta
identifier-list ---> id identifier-list'
identifier-list' ---> id, identifier-list' | null

id[number], is alpha  id[number] is beta
identifier-list ---> id[number] identifier-list''
identifier-list'' ---> id[number], identifier-list'' | null

statement_list ---> statement statement_list | null
statement  --->  assign-stat; | decision_stat
assign_stat --->  id = expn
expn --->  simple-expn eprime
eprime ---> relop simple-expn | null
simple-exp --->  term seprime
seprime ---> addop term seprime | null 
term  --->  factor tprime
tprime ---> mulop factor tprime | null
factor --->  id | num
decision-stat --->  if (expn) {statement_list} dprime
dprime ---> else {statement_list} | null
relop ---> == | != | <= | >= | > | <
addop --->  + | -
mulop ---> * | / | %
*/

void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void Program()
{

}

void main()
{
    char word[128];
    printf("Enter the word: ");
    scanf("%s", word);
    Program();
}
