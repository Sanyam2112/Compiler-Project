// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef CODEGEN
#define CODEGEN

#include "semanticAnalyzer.h"

void declareidentifiers(parseTree* head, FILE* fap);
void codegen(parseTree* head, FILE* fap);
void code_for_operations(parseTree *head, FILE *fp, char *scope, FILE *fer);
void switone(parseTree *head, FILE *fp, char *scope, FILE *fer);
void swittwo(parseTree *head, FILE *fp, char *scope, FILE *fer);
void GenerateCodes(parseTree *head, FILE *fp, char *scope, FILE *fer);
int expstate, opcount;
int whilenum, conum, relnum, fornum;

#endif