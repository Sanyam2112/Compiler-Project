// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include "semanticAnalyzer.h"

char sanfunc[100];

void createsymboltable(){
    functable = (struct func_hash_table*)calloc(1,sizeof(struct func_hash_table*));
    int i;
    char *temp = "";
    char *inp = "";
    char *outp = "";
    for(i=0;i<SIZE;i++){
        functable->table[i] = create_function_node(temp,inp,outp);
    }
    ht = (struct hash_of_hash_tables*)calloc(1,sizeof(struct hash_of_hash_tables));
    int j;
    for(j=0;j<HASHSIZE;j++){
        ht->functable[j] = create_hash_table();
        for(i=0;i<SIZE;i++){
            char *key = "";
            char* functionname = "";
            char* type = "";
            char* ifnumval = "";
            int inputvar = 0;
            ht->functable[j]->table[i] = create_node(key, type, functionname, ifnumval , inputvar );

        }
    }
}

void populateFunctionDefinitions(char* funcname, parseTree* ast){
  if (ast == NULL)
  return;

  if(ast->noOfChildren>0){
    populateFunctionDefinitions(funcname, &ast->children[0]);
  }

  if(ast->isTerminal == 0 && (ast->parent)){
    if ((strcmp(idRepr(ast->parent->nonTerminal),"module")==0) && strcmp(funcname,ast->terminal.lexeme)==0){
      parseTree ipList = ast->parent->children[1];
      char inputtype[1000] = {'\0'};
      char outputtype[1000] = {'\0'};

      switch(ipList.children[1].ruleno){
        case 17:
          strcat(inputtype,"INTEGER");
          break;

        case 18:
          strcat(inputtype,"REAL");
          break;

        case 19:
          strcat(inputtype,"BOOLEAN");
          break;

        case 20:{
          parseTree range = ipList.children[1].children[1];
          int num1 = atoi(range.children[0].children[0].terminal.lexeme);
          int num2 = atoi(range.children[1].children[0].terminal.lexeme);
          int r = num2 - num1 +1;
          char size[3];
          sprintf(size,"%d",r);
          char type[100] = {'\0'};
          switch(ipList.children[1].children[2].ruleno){
            case 21:
              strcat(inputtype,"ARRAY(INTEGER, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;

            case 22:
              strcat(inputtype,"ARRAY(REAL, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;

            case 23:
              strcat(inputtype,"ARRAY(BOOLEAN, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;
          }
          break;
        }
      }

      parseTree N1 = ipList.children[2];
       while(N1.ruleno != 13){
         switch(N1.children[1].ruleno){
          case 17:
            strcat(inputtype,"; INTEGER");
            break;

          case 18:
            strcat(inputtype,"; REAL");
            break;

          case 19:
            strcat(inputtype,"; BOOLEAN");
            break;

          case 20:{
            parseTree range = N1.children[1].children[1];
            int num1 = atoi(range.children[0].children[0].terminal.lexeme);
            int num2 = atoi(range.children[1].children[0].terminal.lexeme);
            int r = num2 - num1 +1;
            char size[3];
            sprintf(size,"%d",r);
            char type[100] = {'\0'};
            switch(range.parent->children[(range.childnum)+1].ruleno){
              case 21:
                strcat(inputtype,"; ARRAY(INTEGER, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;

              case 22:
                strcat(inputtype,"; ARRAY(REAL, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;

              case 23:
                strcat(inputtype,"; ARRAY(BOOLEAN, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;
            }
            break;
          }
         }

        N1 = N1.children[2];
      }

      if(ast->parent->children[2].ruleno != 10){
        parseTree opList = ast->parent->children[2].children[0];
        switch(opList.children[1].ruleno){
          case 21:
          strcat(outputtype, "INTEGER");
          break;

          case 22:
          strcat(outputtype, "REAL");
          break;

          case 23:
          strcat(outputtype, "BOOLEAN");
          break;
        }

        parseTree N2 = opList.children[2];
        while(N2.ruleno!=16){
          switch(N2.children[1].ruleno){
            case 21:
              strcat(outputtype, "; INTEGER");
              break;

            case 22:
              strcat(outputtype, "; REAL");
              break;

            case 23:
              strcat(outputtype, "; BOOLEAN");
              break;
          }
          N2 = N2.children[2];
        }
      }

      insert_function_in_hash(funcname,inputtype, outputtype);
      nest(s,funcname);
      return;
    }
  }

  if(ast->parent){
    if(ast->childnum < (ast->parent->noOfChildren)-1){
      parseTree* sibling = &ast->parent->children[(ast->childnum)+1];
      populateFunctionDefinitions(funcname,sibling);
    }
  }
}

int TypeChecker(parseTree* ast, char *scope, FILE *fer){


  int type1, type2;

  int i, error = 0;

 

  if(ast->isTerminal == 0){//Terminals

    if(strcmp(ast->terminal.tokenName,"ASSIGNOP")==0){


      type1 = TypeChecker(&ast->parent->parent->parent->children[0],scope, fer);

 

      if(ast->parent->ruleno == 47){

        type2 = TypeChecker(&ast->parent->children[1],scope, fer);

        if(type1>2 || type2>2){

          if(type1!=type2){

            fprintf(fer, "ERROR 16 :ARRAYS must have same type line no. %u\n",ast->terminal.lineNum);
            errorflag1 = 1;
            return -2;

          }else if(ast->parent->children[1].children[0].children[0].children[0].children[1].ruleno!= 73 || ast->parent->children[1].children[0].children[0].children[0].children[0].children[1].ruleno!=76){

            fprintf(fer, "ERROR 17 :invalid operations on variable of type ARRAY on line no. %d\n",ast->terminal.lineNum);
            errorflag1 = 1;
            return -2;

          }else{

            char* t1 = ast->parent->parent->parent->children[0].terminal.lexeme;

            char* t2 =ast->parent->children[1].children[0].children[0].children[0].children[0].children[0].children[0].children[0].terminal.lexeme;

            if(getfull(t1,scope)->isdynamic == 0 && getfull(t2,scope)->isdynamic == 0){

              if(strcmp(retrievetype(t1,scope),retrievetype(t2,scope))==0){

                return type1;

              }else {

                return -2;

              }

            }else{

              return 0;

            }

          }

        }

      }else if(ast->parent->ruleno == 48){

        type2 = TypeChecker(&ast->parent->children[2],scope, fer);

        if(type1 < 3){

          fprintf(fer, "ERROR 17 : %s is not an array line no. %d\n",ast->parent->parent->parent->children[0].terminal.lexeme,ast->terminal.lineNum);
          errorflag1 = 1;
          return -2;

        }

        type1 = type1 - 4;

        if(ast->parent->children[0].ruleno == 49){//NUM

          int index = atoi(ast->parent->children[0].children[0].terminal.lexeme);

          pNext p =getfull(ast->parent->parent->parent->children[0].terminal.lexeme ,scope);


          if(index < p->r1 || index > p->r2 ){

            fprintf(fer, "ERROR 18:index not in ARRAY RANGE line no %u\n",ast->terminal.lineNum);
            errorflag1 = 1;
            return -2;

          }else if(type1!=type2 || type2 == -2 ){

            fprintf(fer, "ERROR 19:Type mismatch on line no. %d\n",ast->terminal.lineNum);
            errorflag1 = 1;
            return -2;

          }

 

        }else if(ast->parent->children[0].ruleno == 50){//ID

          if(strcmp(retrievetype(ast->parent->children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0){

            fprintf(fer, "ERROR 20:ARRAY index must be an integer line no. %u\n",ast->terminal.lineNum );
            errorflag1 = 1;
            return -2;

          }

        }

      }

      if(type1 > 2 ){

        type1-=3;

      }

      if(type2 > 2 ){

        type2-=3;

      }


      if(type1 == -2 || type1 == -2 || type1 != type2)

        return -2;

      else return type1;

 

    }else if(strcmp(ast->terminal.tokenName,"ID") == 0){


      char* type = retrievetype(ast->terminal.lexeme, scope);

      if(strcmp(type,"")==0){

        return -2;

      }


 

      if(ast->parent->ruleno == 35){


        if(ast->parent->children[1].ruleno == 40){

          char* varidnum = ast->parent->children[1].children[0].children[0].terminal.tokenName;

          if(strcmp(varidnum,"NUM")==0){

            pNext p =getfull(ast->terminal.lexeme ,scope);

            int index = atoi(ast->parent->children[1].children[0].children[0].terminal.lexeme);

            if(index<p->r1 || index>p->r2){

              fprintf(fer, "ERROR:index %d doesn't exist for ARRAY %s line no. %d\n",index,ast->terminal.lexeme,ast->terminal.lineNum);
              errorflag1 = 1;
              return -2;

            }

          }

 

          if(strcmp(varidnum,"ID")==0){

            if(strcmp(retrievetype(ast->parent->children[1].children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0){

                return -2;

            }

          }

 

          if(strncmp(type,"ARRAY",5)!=0){


            return -2;

          }

          if(strncmp(type, "ARRAY(INTEGER",13)==0)

            return 0;

 

          if(strncmp(type, "ARRAY(REAL",10)==0)

            return 1;

 

          if(strncmp(type, "ARRAY(BOOLEAN",13)==0)

            return -1;

        }

      }

      if(strncmp(type, "ARRAY(INTEGER",13)==0)

        return 4;

 

      if(strncmp(type, "ARRAY(REAL",10)==0)

        return 5;

 

      if(strncmp(type, "ARRAY(BOOLEAN",13)==0)

        return 3;

 

        if(strcmp(type, "INTEGER")==0)

          return 0;

 

        if(strcmp(type, "REAL")==0)

          return 1;

 

        if(strcmp(type, "BOOLEAN")==0)

          return -1;

    }else if(strcmp(ast->terminal.tokenName,"NUM") == 0){

      return 0;

    }else if(strcmp(ast->terminal.tokenName,"RNUM") == 0){

      return 1;

    }else if(strcmp(ast->terminal.tokenName,"TRUE") == 0 || strcmp(ast->terminal.tokenName,"FALSE")==0){

      return -1;

    }else if(strcmp(ast->terminal.tokenName,"PLUS") == 0 || strcmp(ast->terminal.tokenName,"MINUS")==0){

      if(ast->parent->ruleno == 60 || ast->parent->ruleno == 61){// +(a+b) or -(a+b)

        return TypeChecker(&ast->parent->parent->children[1],scope, fer);//new_NT

      }

      if(ast->parent->parent->parent->ruleno == 72){//ARTHMETIC2

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[1],scope, fer))==-2)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer))==-2)

          return -2;

      }

      if(ast->parent->parent->parent->ruleno == 71){//ARTHMETIC

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[0],scope, fer))==-2)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1],scope, fer))==-2)

          return -2;

      }

      if(type1 != type2)

        return -2;

 

      if(type1 == -1)

        return -2;

 

      return type1;

    }else if(strcmp(ast->terminal.tokenName,"MUL") == 0 || strcmp(ast->terminal.tokenName,"DIV")==0){

      if(ast->parent->parent->parent->ruleno == 75){//N5

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[1],scope, fer)) == -2)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer))==-2)

          return -2;

      }

 

      if(ast->parent->parent->parent->ruleno == 74){//TERM

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[0],scope, fer)) ==-2)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer)) == -2)

          return -2;

      }

 

      if(type1 != type2)

        return -2;

 

      if(type1 == -1)

        return -2;

 

      return type1;

    }else if(strcmp(ast->terminal.tokenName,"LE") == 0 || strcmp(ast->terminal.tokenName,"LT") == 0 || strcmp(ast->terminal.tokenName,"GE") == 0 || strcmp(ast->terminal.tokenName,"GT") == 0 || strcmp(ast->terminal.tokenName,"EQ") == 0 || strcmp(ast->terminal.tokenName,"NE") == 0){

      if(ast->parent->parent->parent->ruleno == 65){//ANYTERM

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[0],scope, fer))==-2)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer))==-2)

          return -2;

      }

 

      if((type1!=0&&type1!=1)||(type2!=0&&type2!=1))

        return -2;

 

      if(type1!=type2)

        return -2;

 

      return -1;

    }else if(strcmp(ast->terminal.tokenName,"AND") == 0 || strcmp(ast->terminal.tokenName,"OR") == 0){

      if(ast->parent->parent->parent->ruleno == 62)//arithmeticOrBooleanExpr

      {

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[0],scope, fer))!=-1)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer))!=-1)

          return -2;

      }

 

      if(ast->parent->parent->parent->ruleno == 63)//N7

      {

        if((type1 = TypeChecker(&ast->parent->parent->parent->children[1],scope, fer))!=-1)

          return -2;

 

        if((type2 = TypeChecker(&ast->parent->parent->children[1], scope, fer))!=-1)

          return -2;

      }

      return -1;

    }


  }


  if(strcmp(idRepr(ast->nonTerminal),"arithmeticOrBooleanExpr") == 0){

    if(ast->children[1].noOfChildren == 0){//N7 = eps

      return TypeChecker(&ast->children[0],scope, fer);

    }else if(ast->children[1].noOfChildren == 3){

      return TypeChecker(&ast->children[1].children[0].children[0],scope, fer);

    }else{


    }

  }else if(strcmp(idRepr(ast->nonTerminal),"AnyTerm") == 0){

    if(ast->ruleno == 65){

      if (ast->children[1].noOfChildren == 2)

        return TypeChecker(&ast->children[1].children[0].children[0],scope, fer);

      else return TypeChecker(&ast->children[0],scope, fer);

    }else{

      return -1;

    }

  }else if(strcmp(idRepr(ast->nonTerminal),"factor") == 0){

    if(ast->ruleno ==104){

      return TypeChecker(&ast->children[0].children[0],scope, fer);

    }else{

      return TypeChecker(&ast->children[0],scope, fer);

    }

  }else if(strcmp(idRepr(ast->nonTerminal),"term") == 0){

    if(ast->children[1].noOfChildren == 1){//N5 is not eps

      return TypeChecker(&ast->children[1].children[0].children[0],scope, fer);

    }else{

      return TypeChecker(&ast->children[0],scope, fer);

    }

  }else if(strcmp(idRepr(ast->nonTerminal),"new_NT") == 0){

    if(ast->ruleno == 58){

      return TypeChecker(&ast->children[0],scope, fer);

    }else{//rule 59

      return TypeChecker(&ast->children[0].children[0],scope, fer);

    }

  }if(strcmp(idRepr(ast->nonTerminal),"arithmeticExpr") == 0){

    if (ast->children[1].noOfChildren == 3)

     return TypeChecker(&ast->children[1].children[0].children[0],scope, fer);

    else return TypeChecker(&ast->children[0],scope, fer);

   }if(strcmp(idRepr(ast->nonTerminal),"value") == 0){

 

    char* type = retrievetype(ast->children[0].terminal.lexeme, scope);

    if(type == NULL){

      fprintf(fer, "Identifier %s not declared before use line %u",ast->children[0].terminal.lexeme,ast->children[0].terminal.lineNum);
      errorflag1 = 1;
    }

 

    if(strcmp(type, "INTEGER")==0)

      return 0;

 

    if(strcmp(type, "REAL")==0)

      return 1;

 

    if(strcmp(type, "BOOLEAN")==0)

      return -1;

  }if(strcmp(idRepr(ast->nonTerminal),"expression") == 0){

    return TypeChecker(&ast->children[0],scope, fer);

  }if(strcmp(idRepr(ast->nonTerminal),"U") == 0){

    return TypeChecker(&ast->children[1],scope, fer);

  }

 

}




void newfunction(parseTree *head, char *scope, FILE *fer){

    if(head==NULL)
       return;

    if((head->isTerminal==0) && strcmp(head->terminal.tokenName,"ID")==0)
    {
                if(strcmp(idRepr(head->parent->nonTerminal),"moduleDeclaration")==0)
                {
                    
                    if(if_func_present(head->terminal.lexeme))
                        fprintf(fer,"ERROR 1: Function %s already Defined, Erroneous declaration, line number %d\n", head->terminal.lexeme,head->terminal.lineNum);
                    else{
                        parseTree *root = head;
                        while(strcmp(idRepr(root->nonTerminal),"program")!=0)
                            root = root->parent;

                        populateFunctionDefinitions(head->terminal.lexeme , root);
                    }
                }

                if(strcmp(idRepr(head->parent->nonTerminal),"module")==0)
                {
                  
                    if(!if_func_present(head->terminal.lexeme)){
                        populateFunctionDefinitions(head->terminal.lexeme ,head );
                        
                    }
                }

                //Changes scope
                if(strcmp(idRepr(head->parent->nonTerminal),"module")==0)
                {
                   
                  strcpy(scope, head->terminal.lexeme);
                  strcpy(sanfunc,scope);
                }

                //Declare Statements
                if(strcmp(idRepr(head->parent->nonTerminal),"idList")==0 && strcmp(idRepr(head->parent->parent->nonTerminal),"declareStmt")==0)
                {
                    if(ifsymbolpresent(head->terminal.lexeme, scope)== 1)
                     {
                         fprintf(fer, "ERROR 9: Redeclaration of variable %s in the same scope, line number %d\n", head->terminal.lexeme, head->terminal.lineNum);
                     }
                    else if (ifsymbolpresent(head->terminal.lexeme, scope)== 2)
                    {
                            
                            int presentchildnum = head->parent->childnum;
                            switch( head->parent->parent->children[presentchildnum +1].ruleno)
                            {
                                case 17: overwrite(head->terminal.lexeme,"INTEGER",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                       
                                    break;
                                case 18: overwrite(head->terminal.lexeme,"REAL",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                        
                                    break;
                                case 19: overwrite(head->terminal.lexeme,"BOOLEAN",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                        
                                    break;
                                case 20:
                                    {
                                    int vari = head->parent->childnum;

                                    parseTree range = head->parent->parent->children[vari + 1].children[1];

                                    //cases will start from here.....

                                    if(range.children[0].ruleno == 49 && range.children[1].ruleno == 49)
                                    {
                                            int r1 = atoi(range.children[0].children[0].terminal.lexeme);

                                            int r2 = atoi(range.children[1].children[0].terminal.lexeme);

                                            int r = r2 -r1 +1;

                                            char size[3];
                                            sprintf(size,"%d",r);

                                         
                                            char type[100] = {'\0'};

                                            switch(range.parent->children[range.childnum + 1].ruleno){
                                                case 21: strcat(type, "ARRAY(INTEGER, ");
                                                        
                                                        strcat(type, size);
                                                        strcat(type, ")");
                                                        overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                        insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 22:strcat(type, "ARRAY(REAL, ");
                                                        
                                                        strcat(type, size);
                                                        strcat(type, ")");
                                                        overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                        insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                       
                                                        strcat(type, size);
                                                        strcat(type, ")");
                                                        overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                        insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                    }
                                    }
                                    else
                                    {
                                        int r1 = -1;
                                        int r2 = -1;

                                        //this ection has to be copied.....
                                        if(range.children[0].ruleno == 49)
                                            r1 = atoi(range.children[0].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR:%s is not integer declared at line number %d \n",range.children[0].children[0].terminal.lexeme,range.children[0].children[0].terminal.lineNum );
                                            }

                                        if(range.children[1].ruleno == 49)
                                            r2 = atoi(range.children[1].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer ,"ERROR:%s is not integer declared at line number %d \n", range.children[1].children[0].terminal.lexeme, range.children[1].children[0].terminal.lineNum );
                                            }

                                        char size[3];
                                        
                                        sprintf(size,"---");
                                        char type[100] = {'\0'};

                                        switch(range.parent->children[range.childnum + 1].ruleno){
                                            case 21: strcat(type, "ARRAY(INTEGER, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                    
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 22:strcat(type, "ARRAY(REAL, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                                }
                                    }


                                }
                                break;
                                }
                    }
                    else
                    {
                           
                    int presentchildnum = head->parent->childnum;
                    switch( head->parent->parent->children[presentchildnum +1].ruleno)
                    {
                        case 17: insertinhash(head->terminal.lexeme,"INTEGER",scope,"___",0);
                                insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                             
                            break;
                        case 18: insertinhash(head->terminal.lexeme,"REAL",scope,"___",0);
                                insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                
                            break;
                        case 19: insertinhash(head->terminal.lexeme,"BOOLEAN",scope,"___",0);
                                insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                               
                            break;
                        case 20:
                            {
                                int vari = head->parent->childnum;

                            parseTree range = head->parent->parent->children[vari + 1].children[1];

                            if(range.children[0].ruleno == 49 && range.children[1].ruleno == 49)
                                    {
                                            int r1 = atoi(range.children[0].children[0].terminal.lexeme);

                                            int r2 = atoi(range.children[1].children[0].terminal.lexeme);

                                            int r = r2 -r1 +1;

                                            char size[3];
                                            sprintf(size,"%d",r);

                                            char type[100] = {'\0'};

                                            switch(range.parent->children[range.childnum + 1].ruleno){
                                                case 21: strcat(type, "ARRAY(INTEGER, ");
                                                       
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                        
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 22:strcat(type, "ARRAY(REAL, ");
                                                        
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                        
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                        
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                    }
                                    }
                                    else
                                    {
                                        int r1 = -1;
                                        int r2 = -1;

                                        if(range.children[0].ruleno == 49)
                                            r1 = atoi(range.children[0].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR:%s is not integer declared at line number %d \n",range.children[0].children[0].terminal.lexeme,range.children[0].children[0].terminal.lineNum );
                                            }

                                        if(range.children[1].ruleno == 49)
                                            r2 = atoi(range.children[1].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR:%s is not integer declared at line number %d \n", range.children[1].children[0].terminal.lexeme, range.children[1].children[0].terminal.lineNum );
                                            }


                                        char size[3];
                                       
                                        sprintf(size,"---");
                                        char type[100] = {'\0'};

                                        switch(range.parent->children[range.childnum + 1].ruleno){
                                            case 21: strcat(type, "ARRAY(INTEGER, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 22:strcat(type, "ARRAY(REAL, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                                }
                                    }

                        }
                        break;
                        }
                    }
                }

                if(strcmp(idRepr(head->parent->nonTerminal),"N3")==0)
                {
                        parseTree *temphead = head;
                        while(strcmp(idRepr(temphead->parent->nonTerminal),"idList")!=0)
                            temphead = temphead->parent;

                    if(strcmp(idRepr(temphead->parent->nonTerminal),"idList")==0 && strcmp(idRepr(temphead->parent->parent->nonTerminal),"declareStmt")==0)
                    {
                         if(ifsymbolpresent(head->terminal.lexeme, scope) == 1 )
                         {
                         fprintf(fer, "ERROR 9: Redeclaration of variable %s in the same scope, line number %d\n", head->terminal.lexeme, head->terminal.lineNum);
                         }
                         else if(ifsymbolpresent(head->terminal.lexeme, scope) == 2)
                         {
                            int presentchildnum = temphead->parent->childnum;
                            switch( temphead->parent->parent->children[presentchildnum +1].ruleno)
                            {
                                case 17: overwrite(head->terminal.lexeme,"INTEGER",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                        
                                        break;
                                case 18: overwrite(head->terminal.lexeme,"REAL",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                        
                                        break;
                                case 19: overwrite(head->terminal.lexeme,"BOOLEAN",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                        
                                        break;
                                case 20:
                                    { 
                                    int vari = temphead->parent->childnum;

                                    parseTree range = temphead->parent->parent->children[vari + 1].children[1];

                                    if(range.children[0].ruleno == 49 && range.children[1].ruleno == 49)
                                    {
                                            int r1 = atoi(range.children[0].children[0].terminal.lexeme);

                                            int r2 = atoi(range.children[1].children[0].terminal.lexeme);

                                            int r = r2 -r1 +1;

                                            char size[3];
                                            sprintf(size,"%d",r);

                                           
                                            char type[100] = {'\0'};

                                            switch(range.parent->children[range.childnum + 1].ruleno){
                                                case 21: strcat(type, "ARRAY(INTEGER, ");
                                                   
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                        
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 22:strcat(type, "ARRAY(REAL, ");
                                                      
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                       
                                                         overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                      
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                        
                                                         overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                    }
                                    }
                                    else
                                    {
                                        int r1 = -1;
                                        int r2 = -1;

                                        if(range.children[0].ruleno == 49)
                                            r1 = atoi(range.children[0].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer,"ERROR:%s is not integer declared at line number %d \n",range.children[0].children[0].terminal.lexeme,range.children[0].children[0].terminal.lineNum );
                                            }

                                        if(range.children[1].ruleno == 49)
                                            r2 = atoi(range.children[1].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer,"ERROR:%s is not integer declared at line number %d \n", range.children[1].children[0].terminal.lexeme, range.children[1].children[0].terminal.lineNum );
                                            }


                                        char size[3];
                                        sprintf(size,"---");
                                        char type[100] = {'\0'};

                                        switch(range.parent->children[range.childnum + 1].ruleno){
                                            case 21: strcat(type, "ARRAY(INTEGER, ");
                                                  
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                    
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 22:strcat(type, "ARRAY(REAL, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     overwrite(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                                }
                                    }
                                }
                                break;
                            }

        

                         }
                         else
                         {
                           
                            int presentchildnum = temphead->parent->childnum;
                            switch( temphead->parent->parent->children[presentchildnum +1].ruleno)
                            {
                                case 17: insertinhash(head->terminal.lexeme,"INTEGER",scope,"___",0);
                                       insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                                      
                                    break;
                                case 18: insertinhash(head->terminal.lexeme,"REAL",scope,"___",0);
                                insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                              
                                    break;
                                case 19: insertinhash(head->terminal.lexeme,"BOOLEAN",scope,"___",0);
                                        insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", findScope(s,scope)->depth );
                              
                                    break;
                                case 20:
                                    { 
                                    int vari = temphead->parent->childnum;

                                    parseTree range = temphead->parent->parent->children[vari + 1].children[1];

                                    if(range.children[0].ruleno == 49 && range.children[1].ruleno == 49)
                                    {
                                            int r1 = atoi(range.children[0].children[0].terminal.lexeme);

                                            int r2 = atoi(range.children[1].children[0].terminal.lexeme);

                                            int r = r2 -r1 +1;

                                            char size[3];
                                            sprintf(size,"%d",r);

                                   
                                            char type[100] = {'\0'};

                                            switch(range.parent->children[range.childnum + 1].ruleno){
                                                case 21: strcat(type, "ARRAY(INTEGER, ");
                                                      
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                      
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 22:strcat(type, "ARRAY(REAL, ");
                                                        
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                        
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                         
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                        
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", findScope(s,scope)->depth );
                                                        break;
                                                    }
                                    }
                                    else
                                    {
                                        int r1 = -1;
                                        int r2 = -1;

                                        if(range.children[0].ruleno == 49)
                                            r1 = atoi(range.children[0].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer,"ERROR:%s is not integer declared at line number %d \n",range.children[0].children[0].terminal.lexeme,range.children[0].children[0].terminal.lineNum );
                                            }

                                        if(range.children[1].ruleno == 49)
                                            r2 = atoi(range.children[1].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR:%s is not integer declared at line number %d \n", range.children[1].children[0].terminal.lexeme, range.children[1].children[0].terminal.lineNum );
                                            }


                                        char size[3];
                                  
                                        sprintf(size,"---");
                                        char type[100] = {'\0'};

                                        switch(range.parent->children[range.childnum + 1].ruleno){
                                            case 21: strcat(type, "ARRAY(INTEGER, ");
                                                   
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                  
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 22:strcat(type, "ARRAY(REAL, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                            case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                               
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", findScope(s,scope)->depth );
                                                    break;
                                                }
                                    }
                                }
                                break;
                            }

                     

                      }
                    }
                }

                if(strcmp(idRepr(head->parent->nonTerminal),"input_plist")==0 || strcmp(idRepr(head->parent->nonTerminal),"N1")==0)
                {
                     
                        switch( head->parent->children[head->childnum +1].ruleno)
                        {
                            case 17: insertinhash(head->terminal.lexeme,"INTEGER",scope,"___",1);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                    
                                break;
                            case 18: insertinhash(head->terminal.lexeme,"REAL",scope,"___",1);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                   
                                break;
                            case 19: insertinhash(head->terminal.lexeme,"BOOLEAN",scope,"___",1);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                   
                                break;
                            case 20:
                                {
                                    int vari = head->childnum;
                                    
                                    parseTree range = head->parent->children[vari + 1].children[1];
                                  

                                    if(range.children[0].ruleno == 49 && range.children[1].ruleno == 49)
                                    {
                                            int r1 = atoi(range.children[0].children[0].terminal.lexeme);

                                            int r2 = atoi(range.children[1].children[0].terminal.lexeme);

                                            int r = r2 -r1 +1;

                                            char size[3];
                                            sprintf(size,"%d",r);

                                         
                                            char type[100] = {'\0'};

                                            switch(range.parent->children[range.childnum + 1].ruleno){
                                                case 21: strcat(type, "ARRAY(INTEGER, ");
                                                      
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                       
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", 0 );
                                                        break;
                                                case 22:strcat(type, "ARRAY(REAL, ");
                                                       
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                         
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", 0 );
                                                        break;
                                                case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                         
                                                         strcat(type, size);
                                                         strcat(type, ")");
                                                        
                                                         insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                         insertrange(head->terminal.lexeme,scope,r1 , r2 , 0 );
                                                         insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","static", 0 );
                                                        break;
                                                    }
                                    }
                                   else
                                    {
                                        int r1 = -1;
                                        int r2 = -1;

                                        if(range.children[0].ruleno == 49)
                                            r1 = atoi(range.children[0].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR%s is not integer declared at line number %d \n",range.children[0].children[0].terminal.lexeme,range.children[0].children[0].terminal.lineNum );
                                            }

                                        if(range.children[1].ruleno == 49)
                                            r2 = atoi(range.children[1].children[0].terminal.lexeme);
                                        else
                                            if(strcmp(retrievetype(range.children[0].children[0].terminal.lexeme,scope),"INTEGER")!=0)
                                            {
                                                fprintf(fer, "ERROR%s is not integer declared at line number %d \n", range.children[1].children[0].terminal.lexeme, range.children[1].children[0].terminal.lineNum );
                                            }


                                        char size[3];
                                  
                                        sprintf(size,"---");
                                        char type[100] = {'\0'};

                                        switch(range.parent->children[range.childnum + 1].ruleno){
                                            case 21: strcat(type, "ARRAY(INTEGER, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                    
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", 0 );
                                                    break;
                                            case 22:strcat(type, "ARRAY(REAL, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                    
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", 0 );
                                                    break;
                                            case 23:strcat(type, "ARRAY(BOOLEAN, ");
                                                 
                                                     strcat(type, size);
                                                     strcat(type, ")");
                                                   
                                                     insertinhash(head->terminal.lexeme, type ,scope, "___",0);
                                                     insertrange(head->terminal.lexeme,scope,r1 , r2 , 1 );
                                                     insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"yes","dynamic", 0 );
                                                    break;
                                                }
                                    }


                            }
                            break;
                        }
                       
                }//end of this currenr if

                if(strcmp(idRepr(head->parent->nonTerminal),"output_plist" )==0 || strcmp(idRepr(head->parent->nonTerminal),"N2")==0)
                {
  
                    //printf("name =  %s and %d  \n", idRepr(head->parent->children[head->childnum +1].nonTerminal), head->parent->children[head->childnum +1].ruleno );
                    switch( head->parent->children[head->childnum +1].ruleno)
                        {
                            case 21: insertinhash(head->terminal.lexeme,"INTEGER",scope,"___",0);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                   
                                break;
                            case 22: insertinhash(head->terminal.lexeme,"REAL",scope,"___",0);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                 
                                break;
                            case 23: insertinhash(head->terminal.lexeme,"BOOLEAN",scope,"___",0);
                                    insertvalues(head->terminal.lexeme, scope , findScope(s,scope)->modulescope , findScope(s,scope)->startline , findScope(s,scope)->endline ,"no","---", 0 );
                                  
                                break;
                        }

                }

                if(strcmp(idRepr(head->parent->nonTerminal),"module")!=0 && strcmp(idRepr(head->parent->nonTerminal),"moduleDeclaration")!=0 && strcmp(idRepr(head->parent->nonTerminal),"moduleReuseStmt")!=0 && (!ifsymbolpresent(head->terminal.lexeme, scope)) )
                 {
                   int notpresent = 1;
                   scopeTree* tempscope = findScope(s,scope);
                   
                   while(strcmp(tempscope->scopename,"root")!=0){
                     if(ifsymbolpresent(head->terminal.lexeme, tempscope->scopename)){
                       notpresent = 0;
                     }
                     tempscope = tempscope->parent;
                   }
                   if (notpresent)
                   {
                 
                     fprintf(fer, "ERROR 2: identifier %s not declared, line number %d\n", head->terminal.lexeme, head->terminal.lineNum);
                   }
                 }


                if(strcmp(idRepr(head->parent->nonTerminal),"moduleReuseStmt")==0 ){
                     

                    if(!if_func_present(head->terminal.lexeme))
                        fprintf(fer, "ERROR 3: Function definition for %s not found, line number %d\n", head->terminal.lexeme, head->terminal.lineNum);
                    else{

                            if(strcmp(sanfunc,head->terminal.lexeme)==0)
                            {
                                fprintf(fer, "ERROR 15: Function can not be called recursevily in line %d\n", head->terminal.lineNum);
                            }
                            else
                            {
                                    char inputtype[1000] = {'\0'};
                                    char outputtype[1000] = {'\0'};
                                  
                                    if(head->parent->children[0].ruleno == 52)
                                    {
                                       
                                        parseTree outlist = head->parent->children[0].children[0];
                                        strcat(outputtype, retrievetype(outlist.children[0].terminal.lexeme, scope));
                                        parseTree outlistprime = outlist.children[1];
                                        
                                        while(outlistprime.ruleno != 56){
                                            
                                            strcat(outputtype, "; ");
                                            if(retrievetype(outlistprime.children[0].terminal.lexeme , scope )!= NULL )
                                            {
                                                
                                                strcat(outputtype, retrievetype(outlistprime.children[0].terminal.lexeme, scope));
                                            }
                                            else
                                            {
                                                fprintf(fer, "ERROR : %s variable is not declared at line no %d...",outlistprime.children[0].terminal.lexeme , outlistprime.children[0].terminal.lineNum );
                                            }
                                           
                                            outlistprime = outlistprime.children[1];
                                        }
                                    }
                                               
                                        parseTree inputlist = head->parent->children[2];
                                                
                                    strcat(inputtype, retrievetype(inputlist.children[0].terminal.lexeme, scope));
                                                   
                                   parseTree inputlistprime = inputlist.children[1];
                                               

                                        while(inputlistprime.ruleno != 56){
                                                 
                                            strcat(inputtype, "; ");
                                                    
                                            strcat(inputtype, retrievetype(inputlistprime.children[0].terminal.lexeme, scope));
                                            inputlistprime = inputlistprime.children[1];
                                                  
                                        }
                                                


                                 

                                   if(strcmp(inputtype, get_input_type(head->terminal.lexeme))!=0){
                                            
                                        fprintf(fer,"ERROR 4: input types do not match at line number %d \n", head->terminal.lineNum);
                                      
                                    }
                                     
                                    if(strcmp(outputtype, get_output_type(head->terminal.lexeme))!=0){
                                        fprintf(fer, "ERROR 5: output types do not match at line number %d\n", head->terminal.lineNum);
                                       
                                    }
                            }



                  }

            }

                 //Check that array index is always integer or ID(requires attention)
                 //incomplete
                if(strcmp(idRepr(head->parent->nonTerminal), "index")==0  &&  strcmp(idRepr(head->parent->parent->nonTerminal), "whichId")==0 ){
                  
                    if(strcmp(retrievetype(head->terminal.lexeme, scope), "INTEGER")!=0)
                        fprintf(fer, "ERROR 6: Array index should be of type integer but here, %s has type %s, line number %d\n", head->terminal.lexeme, retrievetype(head->terminal.lexeme, scope), head->terminal.lineNum);
                    }


                if(strcmp(idRepr(head->parent->nonTerminal),"var_id_num")==0 && strcmp(idRepr(head->parent->parent->nonTerminal),"var")==0 && head->parent->children[1].ruleno == 40 )
                {
                    char *token = NULL;
                    char typ[50];
                    strcpy(typ,retrievetype(head->terminal.lexeme , scope));
                   
                   
                    token = strtok(typ, "(");
                   
                    if(token==NULL)
                        fprintf(fer, "ERROR 7: Indexing cannot be done on %s which is not an array, but of type %s , line number %d\n", head->terminal.lexeme, retrievetype(head->terminal.lexeme, scope), head->terminal.lineNum);
                    if(strcmp(token,"ARRAY")!=0){
                        fprintf(fer, "ERROR 8: Indexing cannot be done on %s which is not an array, but of type %s , line number %d\n",head->terminal.lexeme, retrievetype(head->terminal.lexeme, scope), head->terminal.lineNum);
                    }
                  }

    }

    if( (head->isTerminal==0) && (strcmp(head->terminal.tokenName,"ASSIGNOP")==0) && ( strcmp(idRepr(head->parent->nonTerminal),"lvalueIDStmt")==0 || strcmp(idRepr(head->parent->nonTerminal),"lvalueARRStmt")==0 ) )
    {
        int err = TypeChecker(head, scope, fer);
        if(err == -2)
        {
   
        }

    }

    if( head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"conditionalStmt")==0)
    {
       
        int type2, error = 0;
        int type = TypeChecker(&(head->children[0]), scope, fer);
       
        parseTree caseStmts = head->children[2];


        if(type==1)
            fprintf(fer, "ERROR 9: The switch statement cannot have identifier of type real, line number %d\n", head->children[0].terminal.lineNum);
        else{
           
            if(type==0 && head->children[3].ruleno == 99)
                fprintf(fer, "ERROR 10: The switch statement has identifier of type integer but no default statement, line number %d\n", head->children[0].terminal.lineNum);

            if(type==-1 && head->children[3].ruleno == 98)
                fprintf(fer, "ERROR 11: The switch statement has identifier of type boolean cannot have default statement, line number %d\n", head->children[0].terminal.lineNum);


            while(caseStmts.ruleno != 94)
            {
                type2 = TypeChecker(&(caseStmts.children[0].children[0]), scope, fer);
                

                if(type == type2){
                    caseStmts = caseStmts.children[2];
                }
                else
                {   
                    error = 1;
                    break;
                }
            }



        }

        if(error){

            fprintf(fer, "ERROR 12: The type of identifier of switch statement is different from the types of case labels, line number %d\n", caseStmts.children[0].children[0].terminal.lineNum);
        }
    }

    if(head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"iterativeStmt")==0 && head->ruleno==100)
    {
        int type = TypeChecker(&(head->children[1]), scope, fer);
        
        if(type!=0)
            fprintf(fer, "ERROR 13: The identifier in FOR loop has to be integer, line number %d\n", head->children[1].terminal.lineNum);

    }

    if(head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"iterativeStmt")==0 && head->ruleno==101)
    {
        
        int type = TypeChecker(&(head->children[1]), scope, fer);
    
        if(type!=-1)
            fprintf(fer, "ERROR 14: The expression in WHILE loop has to be of type boolean, line number %d\n", head->children[1].terminal.lineNum);
    }


    //return;
}//end function

	
	
	




void populateSymbolTable(parseTree *head, char *scope, FILE *fer){

    if(head==NULL)
       return;

    if(strcmp(idRepr(head->nonTerminal),"driverModule")==0){
        insert_function_in_hash("driver","", "");
        nest(s,"driver");
        strcpy(scope, "driver");
        strcpy(sanfunc,"driver");
        }

    int chill = head-> noOfChildren;

    if(chill > 0)
    {
         for(int j=0; j < chill; j++)
        {
            populateSymbolTable(&head->children[j],scope,fer);
        }

        newfunction(head,scope,fer);


    }
    else
    {
      if(head->isTerminal == 0)
      {
        if(strcmp(head->terminal.tokenName,"START")==0){
           
          if(strcmp(idRepr(head->parent->nonTerminal),"moduleDef")!=0){
           
            char prevscope[25];
            strcpy(prevscope,scope);
            scope = strcat(scope,my_itoa(findScope(s,scope)->numNested+1));
            nest(findScope(s,prevscope),scope);
            insert_function_in_hash(scope,"", "");
          }
            findScope(s,scope)->startline = head->terminal.lineNum;

        }else if(strcmp(head->terminal.tokenName,"END")==0){
            if(strcmp(idRepr(head->parent->nonTerminal),"moduleDef")!=0){
              findScope(s,scope)->endline = head->terminal.lineNum;
             strcpy(scope,findScope(s,scope)->parent->scopename);
             
           }else{
             findScope(s,scope)->endline = head->terminal.lineNum;
           }

        }
        
         newfunction(head,scope,fer);

      }
      else
     {
        //printf("NO NT ---             \n");

        }
    }

}





