// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef LEXERDEF
#define LEXERDEF

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 1024

union number{
	float f;
	int i;
};

typedef struct symbols {
	char *tokenName;
	unsigned int lineNum;
	char lexeme[100];
	union number val;
}tokenInfo;

typedef struct node{
    char* keyword;
    char* token;
    struct node *next;
} node;

char buffer1[MAX_BUFFER_SIZE]; // the input buffer
char buffer2[100];
node* HASH[26];
int bufferPosition1; // indicates the current character to be read from the buffer
int bufferSize1; // the number of characters stored in the buffer (-1 indicates first use)
int line_num;

#endif