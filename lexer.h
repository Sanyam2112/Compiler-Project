// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef LEXER
#define LEXER
#include "lexerDef.h"


void addnode (node *head, char* value1, char *value2);

int strcmp(const char *X, const char *Y);

char *strcpy(char *destination, char *source);

char* searchInHASH(char *str);

void addKeyToken(char *keyword,char* token);

void createHASH();

char getCharacter(FILE *fp);

tokenInfo* getnexttoken(FILE *fp, tokenInfo* temp);

void commentremove(FILE *fp);

void printToken(tokenInfo* t);

#endif
