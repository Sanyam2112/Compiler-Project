// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef PARSER
#define PARSER

#include "parserDef.h"

size_t strlen(char *p);
int parseIdStr(char *idStr);
int idbatao(char *idStr);
void findfirstofstring(unit * ptr , int * array,int k);
void createParseTable();
void printScope(scopeTree* scope);
scopeTree* findScope(scopeTree* scope, char* name);
void nest(scopeTree*s,char* child);
char *idRepr(int id);
void push(char* term, int termin);
int isEmpty();
unit* peek();
void pop();
void display();
void reversepush(struct unit* head);
void parse( FILE *fg, parseTree *p );
void printParseTree(parseTree *p );
void printastree(parseTree *pt );
int isUseful(char * idStr);
void createAbstractSyntaxTree(parseTree *p, parseTree *ast);
int length(parseTree *tree);

#endif