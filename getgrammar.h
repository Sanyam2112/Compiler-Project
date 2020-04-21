// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef GETGRAMMAR
#define GETGRAMMAR

#include<stdio.h>
#include<stdlib.h>
#include "lexer.h"

typedef struct unit {
    char* term;//ntot
    struct unit *next;
    int terminal;
} unit;

int isNT;
int bufferSize;
int arraySize;
char buffer[MAX_BUFFER_SIZE];
int bufferPosition;
int* countarray;
unit** grammararray;
unit** firstarray;
unit** followarray;

void showfirstfollow (unit *head);
void showfollow();
void showgrammar();
void showfirst();
void showlist (unit *head, int index);
char getnextcharacter(FILE *fp);
void addunit(unit *head, char* value1, int is);
char* getnextterm(FILE *fp);
void getnextrule(FILE *fp, unit* head,int index);
unit** initializearray(unit** array);
unit** resizearray(unit** array);
void getgrammar();
void addtoarray(unit* head, unit* nextunit);
void mergelist(unit* list1,unit* list2);
int canbeEpsilon(unit* ptr);
void first(unit* input, unit* new);
void follow(unit* input, unit* new1);
void createfirst();
void createfollow();

#endif