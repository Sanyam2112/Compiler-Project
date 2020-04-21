
compiler: driver.o codegen.o semanticAnalyzer.o symboltable.o parser.o getgrammar.o lexer.o
	gcc driver.o codegen.o semanticAnalyzer.o symboltable.o parser.o getgrammar.o lexer.o -o compiler

driver.o: driver.c
	gcc -w -c driver.c

codegen.o: codegen.c codegen.h
	gcc -w -c codegen.c		

semanticAnalyzer.o: semanticAnalyzer.c semanticAnalyzer.h
	gcc -w -c semanticAnalyzer.c	

symboltable.o: symboltable.c symboltable.h
	gcc -w -c symboltable.c	

parser.o: parser.c parser.h parserDef.h
	gcc -c parser.c	

getgrammar.o: getgrammar.c getgrammar.h
	gcc -c getgrammar.c	

lexer.o: lexer.c lexer.h lexerDef.h
	gcc -c lexer.c

clean:
	rm -f *.o compiler