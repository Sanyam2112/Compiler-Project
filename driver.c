// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "lexer.h"
#include "getgrammar.h"
#include "parser.h"
#include "symboltable.h"
#include "semanticAnalyzer.h"
#include "codegen.h"

int main(int argc, char** argv){

    tokenInfo* temp1;
	createHASH();
    getgrammar();
    createfirst();
    createfollow();
    createParseTable();
    
    int choice;
    int i = 1;
    
    printf("\n\n   LEVEL 3 : Symbol table / AST Generation / Type Checker / Semantic Rules / Code Generation implemented, but generating wrong output for some cases\n\n");

    while(i){
        FILE* fp ;
        FILE *fer;
        FILE* fap ;
        char scope[100];
        memset(scope, '\0', sizeof(scope));
        s = calloc(1,sizeof(scopeTree));
        strcpy(s->scopename,"root");
        s->numNested = 0;
        s->children = NULL;
        s->parent = NULL;
        printf("\nOPTIONS :  \n");
        printf("Option 0 : Exit the console\n");
        printf("Option 1 : Printing the token list\n");
        printf("Option 2 : Parsing and Printing parse tree on console\n");
        printf("Option 3 : Printing Abstract Syntax tree\n");
        printf("Option 4 : Printing Memory allocated\n");
        printf("Option 5 : Printing Symbol Table\n");
        printf("Option 6 : Printing Activation Record Size\n");
        printf("Option 7 : Printing static and dynamic arrays\n");
        printf("Option 8 : Printing errors along with compile time\n");
        printf("Option 9 : Producing assembly code file\n");

        printf("\n--------------ENTER THE OPTION BETWEEN 0-9 -----------------------\n");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 0 :
                i = 0;
                printf("============================BYE==============================\n");
                break;

            case 1:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
				fp = fopen(argv[1],"r");
				temp1 = (tokenInfo*)calloc(1,sizeof(struct symbols));
				printf("-----------------------LIST OF TOKENS-----------------------\n");
				do {
			 		getnexttoken(fp,temp1);
				 	printToken(temp1);
				} while(strcmp(temp1 -> tokenName,"EOF")!=0);
				free(temp1);
				fclose(fp);
			    printf("------------------------------------------------------------\n");
                break;

            case 2:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                errorflag = 0;
			    fp = fopen(argv[1], "r");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                if(errorflag == 0){
                printf("-------------------- PRINTING PARSE TREE ------------------- \n\n");
                printf("Order of traversal is in-order traversal\n");
                printf("%s %18s %20s %20s %30s %20s %10s\n", "lexeme", "lineo", "token_name", "lexeme", "parentNodeSymbol", "isLeafNode", "NodeSymbol");
               
                printParseTree(&p);
                }

                 break;         
            case 3:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                errorflag = 0;
			    fp = fopen(argv[1], "r");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                if(errorflag == 0){
                printf("\n-------------------- PRINTING ABSTRACT SYNTAX TREE---------------\n\n");
                printf("Order of traversal is pre-order traversal\n");
                printf("%s %18s %20s %20s %30s %20s %10s\n", "lexeme", "lineo", "token_name", "lexeme", "parentNodeSymbol", "isLeafNode", "NodeSymbol");
                printastree(&ast);
                }
                break;
            case 4:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                errorflag = 0;
			    fp = fopen(argv[1], "r");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                printf("No. of nodes in parsetree = %d\n", length(&p));
                printf("Size of parse tree = %llu\n", length(&p)*sizeof(p));
                printf("No of nodes in AST = %d\n", length(&ast));
                printf("Size of AST = %llu\n", length(&ast)*sizeof(ast));
                printf("Compression percentage = %lf\n", (length(&p)-length(&ast))*100.0/length(&p));
                
                break;
            case 5:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                errorflag = 0;
                //  s = calloc(1,sizeof(scopeTree));
                // strcpy(s->scopename,"root");
                // s->numNested = 0;
                // s->children = NULL;
                // s->parent = NULL;
			    fp = fopen(argv[1], "r");
                fer = fopen("errorfile.txt", "w");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                createsymboltable();
                populateSymbolTable(&ast, scope,fer);
                updateSymbolTable();
                if(errorflag1 == 0 && errorflag == 0){
                    printf("Code compiles successfully..........................\n ");
                }
                else{
                    printf("There are errors in code : use option 8 to see errors\n");
                }
                displaySymbolTable();
                fclose(fer);
                break;
            case 6:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                //  s = calloc(1,sizeof(scopeTree));
                // strcpy(s->scopename,"root");
                // s->numNested = 0;
                // s->children = NULL;
                // s->parent = NULL;
                errorflag = 0;
			    fp = fopen(argv[1], "r");
                fer = fopen("errorfile.txt", "w");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                createsymboltable();
                populateSymbolTable(&ast, scope,fer);
                updateSymbolTable();
                fclose(fer);
                printactivation();
                break;
            case 7:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                //  s = calloc(1,sizeof(scopeTree));
                // strcpy(s->scopename,"root");
                // s->numNested = 0;
                // s->children = NULL;
                // s->parent = NULL;
                errorflag = 0;
			    fp = fopen(argv[1], "r");
                fer = fopen("errorfile.txt", "w");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                createsymboltable();
                populateSymbolTable(&ast, scope,fer);
                updateSymbolTable();
                displayArrayTable();
                fclose(fer);
                break;
            case 8:
            
                printf("-----------------------PRINT TIME TAKEN FOR COMPILATION AND ERRORS IF EXIST-----------------------\n");

                clock_t    start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
			    fp = fopen(argv[1], "r");
                fer = fopen("errorfile.txt", "w");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                createsymboltable();
                
                populateSymbolTable(&ast, scope,fer);
                //displaySymbolTable();
                fclose(fer);
                FILE *ferr = fopen("errorfile.txt", "r");
                if(errorflag1 == 0 && errorflag == 0){
                    printf("Code compiles successfully..........................\n ");
                }
                char s;
                while((s=fgetc(ferr))!=EOF){
                    printf("%c",s);
                }
                fclose(ferr);
                end_time = clock();

                total_CPU_time  =  (double) (end_time - start_time);

                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
                
                
                printf("\n\n\nStart time = %ld\n", start_time);

                printf("End time = %ld\n", end_time);

                printf("Total time taken in seconds = %lf\n", total_CPU_time_in_seconds);

                printf("Total CPU time = %lf\n", total_CPU_time);
    
                printf("\n");
                break;
            case 9:
                line_num = 1;
				bufferSize1 = -1;
				bufferPosition1 = -1;
                expstate=0;
                opcount=0;
                whilenum=0;
                conum=0;
                relnum=0; 
                fornum=0;
                errorflag = 0;
                errorflag1 = 0;
			    fp = fopen(argv[1], "r");
                fer = fopen("errorfile.txt", "w");
                fap = fopen(argv[2], "w");
                push("$",0);
                push("program",1);
                temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
                temp = getnexttoken(fp,temp);
                p.parent = (parseTree *)calloc(1,sizeof(parseTree));
                p.parent->nonTerminal = parseIdStr("root");
                p.isTerminal = 1;

                parse(fp, &p);
                
                ast.isTerminal = 1;
                ast.nonTerminal = parseIdStr("program");
                ast.parent = (parseTree *)calloc(1,sizeof(parseTree));
                ast.parent->nonTerminal = parseIdStr("root");
                createAbstractSyntaxTree(&p, &ast);
                
                createsymboltable();
                populateSymbolTable(&ast, scope,fer);
                updateSymbolTable();
                //displaySymbolTable();
                fclose(fer);
                if(errorflag == 1 || errorflag1 == 1){
                    printf("There are errors in the code : Cannot generate code\n\n");
                }
                else{
                printf("Code compiles successfully..........................\n ");
                fap = fopen("code.asm", "w");
                codegeneration(&ast, fap);

                char scope1[100];
                memset(scope, '\0', sizeof(scope1));

                GenerateCodes(&ast, fap, scope1, fer);
                fprintf(fap, "\nint 80h\n");
                fclose(fap);
                printf("Code Generation Completed\n\n");    
                }
                break;
            default:
                  printf("--------------------ENTER VALID CHOICE------------------------\n");  
        }
    }
    return 0;
}