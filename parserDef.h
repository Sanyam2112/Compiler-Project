// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef PARSERDEF
#define PARSERDEF

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "getgrammar.h"

typedef enum
  {program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, moduleDef, module, ret, input_plist, N1, output_plist, N2, dataType, type, statements, statement, ioStmt, boolConstt, var_id_num, var, whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, index, moduleReuseStmt, optional, idList, N3, U, new_NT, unary_op, arithmeticOrBooleanExpr, N7, AnyTerm, N8, expression, arithmeticExpr, N4, term, N5, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, Default, iterativeStmt, range_arrays, range}nonTermIds;

enum Terminals
  {ID, NUM, RNUM, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC,  $, eps };

#define NO_OF_TERMINALS 57
#define NO_OF_NONTERMINALS 57

int table[57][57];
int errorflag;
int arraySize;

typedef struct parseTree {
    int isTerminal;
    union {
        nonTermIds nonTerminal;
        tokenInfo terminal;
    };
    struct parseTree *children;
    struct parseTree *parent;
    int noOfChildren;
    int ruleno;
    int childnum;
    int generated;
} parseTree;

typedef struct scopeTree{
  char scopename[25];
  char modulescope[25];
  int numNested;
  int depth;
  int startline;
  int endline;
  struct scopeTree *children;
  struct scopeTree *parent;
} scopeTree;

parseTree p,ast;
struct unit* top;
tokenInfo * temp;

#endif