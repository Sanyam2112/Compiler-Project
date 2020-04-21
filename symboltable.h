// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef _SYMBOL_TABLES_H_
#define _SYMBOL_TABLES_H_
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#define SIZE 150
#define HASHSIZE 150



struct functionNode{
    char name[30];
    char input[100];
    char output[100];
    struct functionNode* next;
};

typedef struct functionNode fnode;
typedef struct functionNode *fnext;


struct func_hash_table{
    fnode* table[SIZE];
};

struct tokNode{
    char name[50];
    char ifnumvalue[10];
    char scope[50];
    char type[50];
    int offset;
    int width;
    int inputvar;
    int r1;
    int r2;
    int isdynamic;

    char parentscope[50];
    int stline;
    int endline;
    char isarray[5];
    char isstatic[10];
    int depthlevel;

    struct tokNode* next;
};

typedef struct tokNode pNode;
typedef struct tokNode *pNext;

struct hash_table
{
    pNode *table[SIZE];
};

struct hash_of_hash_tables{
    struct hash_table *functable[HASHSIZE];
};

scopeTree* s;
struct hash_of_hash_tables *ht;
struct func_hash_table *functable;

struct hash_table* create_hash_table();
struct tokNode* create_node(char *key, char *type, char* funcname, char* ifnumval , int inputtvar);
struct functionNode* create_function_node(char *funcname, char *inparam, char *outparam);
int hash(char *key);
char* my_itoa(int number);
char* strcat(char* destination, const char* source);
void *memset(void *blk, int c, size_t n);
int strncmp( const char * s1, const char * s2, size_t n );
char* strtok(char *str, const char* delim);
int insert_function_in_hash(char *key, char* inparam, char* outparam);
int get_function_value(char* funcname);
void func_display();
char* get_input_type(char* functionname);
char* get_output_type(char* functionname);
int if_func_present(char* funcname);
fnode* functionpointer(char* funcname);
int insertinhash(char* key, char* type, char* functionname, char* ifnumvalue, int inputvar);
int ifsymbolpresent(char *key, char* funcname);
int overwrite(char *key, char* type, char* funcname, char* ifnumvalue, int inputvar);
int insertrange(char *key,char* funcname, int r1,int r2,int isdynamic );
int insertvalues(char *key,char* funcname, char *parentscope , int stline , int endline ,char * isarray , char * isstatic , int depthlevel );
int offsetinTable(char* key, char* funcname);
char* retrievetype(char* key, char* funcname);
void offsetAutomation(char* funcname);
pNode* directpointer(char* key, char* funcname);
void display1(char* funcname);
void update(char* funcname);
void updateSymbolTable();
void displaySymbolTable();
pNext getfull(char* key, char* funcname);
void displayarrays(char* funcname);
void displayArrayTable();
int calculate(char* funcname);
void printactivation();


#endif