// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef SEMANTICANALYZER
#define SEMANTICANALYZER

#include "symboltable.h"
int errorflag1;
void createsymboltable();
void populateFunctionDefinitions(char* funcname, parseTree* ast);
int TypeChecker(parseTree* ast, char *scope, FILE *fer);
void newfunction(parseTree *head, char *scope, FILE *fer);
void populateSymbolTable(parseTree *head, char *scope, FILE *fer);

#endif