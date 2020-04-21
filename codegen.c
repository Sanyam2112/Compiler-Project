// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include "codegen.h"



void declareidentifiers(parseTree* head, FILE* fap){
    int i;
    char ds[] = "section .data\n\tnumber_input:\tdb \"%d\",0\n\n\tnumber_output:\tdb \"%d\",10,0\n";
    fprintf(fap, "%s", ds);
    fprintf(fap, "section .bss\n");

    char *functionname = "driver";
    int k = get_function_value(functionname);

    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[k]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"")!=0){
            char* temp = "ARRAY";
            if(strncmp(iter->type,temp,5)!=0){
                fprintf(fap, "\t%s:\t resd %d\n",iter->name, 1);
            }
            else{
                char* mytype = iter->type;
                char* token = NULL;
                token = strtok(iter->type, "(");
                if(token != NULL){
                    strcpy(mytype, token);
                }
                int range = atoi(mytype);
                fprintf(fap,"\t%s:\t resd %d\n",iter->name,range);
            }
        }
    }
}

void codegeneration(parseTree* head, FILE* fap){
    declareidentifiers(head, fap);
    fprintf(fap, "\nsection .text\n");
    fprintf(fap, "global main\n");
    fprintf(fap, "extern scanf\n");
    fprintf(fap, "extern printf\n");
    fprintf(fap,"\nmain :\n");
}

void code_for_operations(parseTree *head, FILE *fp, char *scope, FILE *fer){

   int field1,field2,field3,i;



    if(head==NULL)
    return;

    int chill = head-> noOfChildren;
    for(int j=0; j < chill; j++)
    { 
        code_for_operations(&(head->children[j]), fp, scope, fer);
    }

    if(head->isTerminal == 0)
    { //printf("yaha |%s|\n",idRepr(head->parent->nonTerminal));
        //printf("************** Hi Terminal %s %s ****************\n",head->terminal.tokenName,head->terminal.lexeme);
        if(strcmp(head->terminal.tokenName,"NUM") == 0)
        {          //printf("________________________________ INSIDE NUM ______________________________________\n ");
                  if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"term") == 0 /*term*/ && expstate == 0){
                    if(head->parent->parent->parent->children[1].ruleno == 76 && head->parent->parent->parent->parent->children[1].ruleno == 73){
                      fprintf(fp,"mov eax,%s\npush eax\n",head->terminal.lexeme);
                      return;
                    }
                  }

                  if(expstate == 1){
                    opcount++;
                    if(opcount <= 2){
                      fprintf(fp,"mov eax,%s\npush eax\n",head->terminal.lexeme);
                      return;
                    }
                  }
        }
        else if(strcmp(head->terminal.tokenName,"ID") == 0)
        {  //printf("________________________________ INSIDE ID ______________________________________\n ");
              if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"term") == 0){//term
                if(TypeChecker(head, scope, fer) == 0 && head->parent->parent->parent->children[1].ruleno == 76 && head->parent->parent->parent->parent->children[1].ruleno == 73 && expstate == 0){
                  fprintf(fp,"mov eax,%s\npush eax\n",head->terminal.lexeme);
                    return;
                }
              }

              if(TypeChecker(head, scope, fer) == 0 && expstate ==1){
                opcount++;
                if(opcount <= 2){
                  fprintf(fp,"push dword[%s]\n",head->terminal.lexeme);
                  return;
                }
              }
            }else if(strcmp(head->terminal.tokenName,"PLUS") == 0){
              //printf("________________________________ INSIDE PLUS ______________________________________\n ");
              if(strcmp(idRepr(head->parent->nonTerminal),"U") == 0){//U
                code_for_operations(&head->parent->parent->children[1], fp, scope, fer);
                fprintf(fp,"pop ebx\nmov eax,0\nadd eax,ebx\npush eax\n");
                    return;
              }else{
                if(!expstate){
                  if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N4") == 0){//N4
                    expstate = 1;
                    code_for_operations(&head->parent->parent->parent->children[1],fp,scope, fer);
                    
                    code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                    expstate = 0;
                    opcount = 0;
                  }else if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"arithmeticExpr") == 0){//arithmeticExpr
                    expstate = 1;
                    
                    code_for_operations(&head->parent->parent->parent->children[0],fp,scope, fer);
                    
                    code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                    expstate = 0;
                    opcount = 0;
                  }
                  fprintf(fp,"pop ebx\npop eax\nadd eax,ebx\npush eax\n");
                }
                return;
              }
            }else if(strcmp(head->terminal.tokenName,"MINUS") == 0){
              //printf("________________________________ INSIDE MINUS ______________________________________\n ");
              if(strcmp(idRepr(head->parent->nonTerminal),"U") == 0){//U
              
                code_for_operations(&head->parent->parent->children[1], fp, scope, fer);
                
                fprintf(fp,"pop ebx\nmov eax,0\nsub eax,ebx\npush eax\n");
                return;
              }else{
                if(!expstate){
                  if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N4") == 0){//N4
                    expstate = 1;
                    
                    code_for_operations(&head->parent->parent->parent->children[1],fp,scope, fer);
                  
                    code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                    expstate = 0;
                    opcount = 0;
                  }else if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"arithmeticExpr") == 0){//arithmeticExpr
                    expstate = 1;
                    
                    code_for_operations(&head->parent->parent->parent->children[0],fp,scope, fer);
                    
                    code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                    expstate = 0;
                    opcount = 0;
                  }
                  fprintf(fp,"pop ebx\npop eax\nsub eax,ebx\npush eax\n");
                }
                return;
              }
            }else if(strcmp(head->terminal.tokenName,"MUL") == 0){
              //printf("________________________________ INSIDE MUL ______________________________________\n ");
              if(!expstate){
                if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N5") == 0){//N5
                  expstate = 1;
                  
                  code_for_operations(&head->parent->parent->parent->children[1],fp,scope, fer);
                  
                  code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                  expstate = 0;
                  opcount = 0;
                }else if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"term") == 0){//term
                  expstate = 1;
                  
                  code_for_operations(&head->parent->parent->parent->children[0],fp,scope, fer);
                  
                  code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                  expstate = 0;
                  opcount = 0;
                }
                fprintf(fp,"pop ebx\npop eax\nimul ebx\npush eax\n");
              }
              return;
            }else if(strcmp(head->terminal.tokenName,"DIV") == 0){
              //printf("________________________________ INSIDE DIV ______________________________________\n ");
              if(!expstate){
                if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N5") == 0){//N5
                  expstate = 1;
                  
                  code_for_operations(&head->parent->parent->parent->children[1],fp,scope, fer);
                  
                  code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                  expstate = 0;
                  opcount = 0;
                }else if(strcmp(idRepr(head->parent->parent->parent->nonTerminal),"term") == 0){//term
                  expstate = 1;
                  
                  code_for_operations(&head->parent->parent->parent->children[0],fp,scope, fer);
                  
                  code_for_operations(&head->parent->parent->children[1],fp,scope, fer);
                  expstate = 0;
                  opcount = 0;
                }
                fprintf(fp,"pop ebx\npop eax\npush edx\nmov edx,0\nidiv ebx\npop edx\npush eax\n");
              }
              return;
            }else if(strcmp(head->terminal.tokenName,"AND") == 0){
              //printf("________________________________ INSIDE AND ______________________________________\n ");
              if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"arithmeticOrBooleanExpr")==0)
              {
                  code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
                  code_for_operations(&(head->parent->parent->children[head->parent->childnum + 1]),fp,scope, fer);
              }


              if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N7")==0)
              {//N7
                      code_for_operations(&(head->parent->parent->parent->children[1]),fp,scope, fer);
                      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
              }
              fprintf(fp,"pop ebx\npop eax\nor eax, ebx\npush eax\n");
              return;
            }else if(strcmp(head->terminal.tokenName,"OR") == 0){
              //printf("_________________________________________INSIDE OR_______________________________________\n");

              if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"arithmeticOrBooleanExpr")==0)
              {
                  code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
                  code_for_operations(&(head->parent->parent->children[head->parent->childnum + 1]),fp,scope, fer);
              }


              if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N7")==0)
              {//N7
                      code_for_operations(&(head->parent->parent->parent->children[1]),fp,scope, fer);
                      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
              }
              fprintf(fp,"pop ebx\npop eax\nor eax, ebx\npush eax\n");
              return;
            }else if(strcmp(head->terminal.tokenName,"LT") == 0){
              //printf("________________________________ INSIDE LT ______________________________________\n ");
            if(!expstate)
            {
                    //assert(0);
      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0)
                      {//AnyTerm
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0)
                      { //N8
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

                    fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njl .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                    relnum++;
          }
             return;
           }else if(strcmp(head->terminal.tokenName,"LE") == 0){
             //printf("________________________________ INSIDE LE ______________________________________\n ");
             if(!expstate)
            {
                //assert(0);
      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0)
                      {//AnyTerm
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0)
                      { //N8
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

                 fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njle .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                relnum++;
        }
           return;
         }else if(strcmp(head->terminal.tokenName,"GT") == 0){
           //printf("________________________________ INSIDE GT ______________________________________\n ");
            if(!expstate)
            {
                //assert(0);
      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0)
                      {//AnyTerm
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0)
                      { //N8
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

                fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njg .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                relnum++;
              }
              return;
            }else if(strcmp(head->terminal.tokenName,"GE") == 0){
              //printf("________________________________ INSIDE GE ______________________________________\n ");

            if(!expstate)
            {
      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0)
                      {//AnyTerm
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0)
                      { //N8
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

                fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njge .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                relnum++;
            }
            return;
          }else if(strcmp(head->terminal.tokenName,"EQ") == 0){
            //printf("________________________________ INSIDE EQ ______________________________________\n ");

            if(!expstate)
            {
                //assert(0);
      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0)
                      {//AnyTerm
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

      if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0)
                      { //N8
      expstate = 1;
      code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
      code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
      expstate = 0;
      opcount = 0;
      }

                fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\nje .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                relnum++;
       }
          return;
        }else if(strcmp(head->terminal.tokenName,"NE") == 0){
          //printf("________________________________ INSIDE NE ______________________________________\n ");

                if(!expstate)
             {
                //assert(0);
        if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"AnyTerm")==0){//AnyTerm
        expstate = 1;
        code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
        code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
        expstate = 0;
        opcount = 0;
        }

        if(head->parent->parent->parent->isTerminal== 1 && strcmp(idRepr(head->parent->parent->parent->nonTerminal),"N8")==0){ //N8
        expstate = 1;
        code_for_operations(&(head->parent->parent->parent->children[0]),fp,scope, fer);
        code_for_operations(&(head->parent->parent->children[1]),fp,scope, fer);
        expstate = 0;
        opcount = 0;
        }

                fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njne .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
                relnum++;
            }
            return;
          }
          else printf("CASE MISSED %s\n",head->terminal.tokenName);
        }else{
          //printf("__________________________________________________________NON TERMINAL %s\n",idRepr(head->nonTerminal));
        }

}

void switone(parseTree *head, FILE *fp, char *scope, FILE *fer)
{
    //printf("inside switone\n");

    if( head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"driverModule")==0)//driverModule
{
   strcpy(scope, "driver");
   //printf("_________________________________________________________scope driver\n");
}


if( (head->isTerminal==0) && (strcmp(head->terminal.tokenName,"ID")==0) && strcmp(idRepr(head->parent->nonTerminal),"module")==0)
    {
        //printf("_________________________________________________________scope module\n");
strcpy(scope, head->terminal.lexeme);
    }

    if( head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"iterativeStmt")==0)
    {   
        if(head->generated != 1)
        {

            if(head->ruleno == 101){

                    expstate = 0;
                    fprintf(fp,".while%d:\n", whilenum);
                    code_for_operations(&(head->children[1]) ,fp,scope, fer);
                    fprintf(fp,"pop eax\ncmp eax,0000h\nje .endwhile%d\n", whilenum);

                    GenerateCodes(&(head->children[2]), fp, scope, fer);
                    fprintf(fp,"jmp .while%d\n", whilenum);
                    fprintf(fp,".endwhile%d:\n", whilenum);
                    whilenum++;
            }

if(head->ruleno == 100)
{
                expstate = 0;
fprintf(fp, ".for%d\n", fornum);
parseTree *id = &(head->children[1]) ;

fprintf(fp,"push dword[%s]\n",id->terminal.lexeme);
fprintf(fp, "pop eax\n");


int start = atoi(head->children[2].children[0].terminal.lexeme);
int end = atoi(head->children[2].children[1].terminal.lexeme);
fprintf(fp, "mov ecx, %d\n", start);
fprintf(fp, "cmp eax, ecx\n");
fprintf(fp, "jl .endfor%d\n", fornum);
fprintf(fp, "mov ecx, %d\n", end);
fprintf(fp, "cmp eax, ecx\n");
fprintf(fp, "jg .endfor%d\n", fornum);
GenerateCodes(&(head->children[3]), fp, scope, fer);
fprintf(fp,"jmp .for%d\n", fornum);
fprintf(fp,".endfor%d:\n", fornum);
fornum++;

            }
        }
        head->generated = 1;
    }

    if( head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"ioStmt")==0)
    {  
        if(head->generated != 1)
        {
if(head->ruleno == 31) //GET_VALUE
            {
                fprintf(fp,"\n\tpush %s\n\tcall scanf\n",head->children[1].terminal.lexeme );
            }
else
            {
              
                if(head->ruleno == 32)
                {
                    if(head->children[1].ruleno == 38)
                    {
                        if(head->children[1].children[0].ruleno == 35)
                        {
                            
                            fprintf(fp,"\n\tpush %s\n\tpush number_input\n\tcall printf\n",head->children[1].children[0].children[0].terminal.lexeme);
                            
                        }
                        else
                        {
                            fprintf(fp,"\n\tpush %s\n\tpush number_input\n\tcall printf\n",head->children[1].children[0].children[0].terminal.lexeme);
                        }
                    }

                    if(head->children[1].ruleno == 39)
                    {
                        fprintf(fp,"\n\tpush %s\n\tpush number_input\n\tcall printf\n",head->children[1].children[0].children[0].terminal.lexeme);
                    }

                }

            }
        }

        head->generated = 1;
    }



}

void swittwo(parseTree *head, FILE *fp, char *scope, FILE *fer)
{
    

    if( head->isTerminal== 1 && strcmp(idRepr(head->nonTerminal),"driverModule")==0)
    {
        strcpy(scope, "driver");
    }

    if( (head->isTerminal==0) && (strcmp(head->terminal.tokenName,"ID")==0) && strcmp(idRepr(head->parent->nonTerminal),"module")==0)
    {
        strcpy(scope, head->terminal.lexeme);
      
    }
    if( (head->isTerminal==0) && (strcmp(head->terminal.tokenName,"ASSIGNOP")==0))
    {
        
        if(head->generated != 1){

//if(head->parent->value==28){//lvalueIDStmt
            if(head->parent->isTerminal== 1 && strcmp(idRepr(head->parent->nonTerminal),"lvalueIDStmt")==0){
parseTree *id = &(head->parent->parent->parent->children[0]);
int type = TypeChecker(id, scope, fer);


if(type==0){
code_for_operations(&(head->parent->children[1]), fp, scope, fer);

fprintf(fp,"pop eax\nmov dword[%s],eax\n",id->terminal.lexeme);
//assert(0);

}

head->generated = 1;

}


}
    }

}

void GenerateCodes(parseTree *head, FILE *fp, char *scope, FILE *fer){

    if(head==NULL)
    return;

    switone(head, fp, scope, fer);

    int chill = head-> noOfChildren;
    for(int j=0; j < chill; j++)
    {
        GenerateCodes(&(head->children[j]), fp, scope, fer);
    }

    swittwo(head, fp, scope, fer);

}