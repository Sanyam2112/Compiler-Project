// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------
#include "parser.h"

int errorflag =0;
size_t strlen(char *p)
{
    unsigned int count = 0;

    while(*p!='\0')
    {
        count++;
        p++;
    }

    return count;
}
int parseIdStr(char *idStr) {
     // For Non - Terminals
    if(strcmp(idStr,"root")==0) return -1;
    if(strcmp(idStr, "program") == 0) return program;
    if(strcmp(idStr, "moduleDeclarations") == 0) return moduleDeclarations;
    if(strcmp(idStr, "moduleDeclaration") == 0) return moduleDeclaration;
    if(strcmp(idStr, "otherModules") == 0) return otherModules;
    if(strcmp(idStr,"driverModule")==0) return driverModule;
    if(strcmp(idStr,"moduleDef")==0) return moduleDef;
    if(strcmp(idStr,"module")==0) return module;
    if(strcmp(idStr,"ret")==0) return ret;
    if(strcmp(idStr,"input_plist")==0) return input_plist;
    if(strcmp(idStr,"N1")==0) return N1;
    if(strcmp(idStr,"output_plist")==0) return output_plist;
    if(strcmp(idStr,"N2")==0) return N2;
    if(strcmp(idStr,"dataType")==0) return dataType;
    if(strcmp(idStr,"type")==0) return type;
    if(strcmp(idStr,"statements")==0) return statements;
    if(strcmp(idStr,"statement")==0) return statement;
    if(strcmp(idStr,"ioStmt")==0) return ioStmt;
    if(strcmp(idStr,"boolConstt")==0) return boolConstt;
    if(strcmp(idStr,"var_id_num")==0) return var_id_num;
    if(strcmp(idStr,"var")==0) return var;
    if(strcmp(idStr,"whichId")==0) return whichId;
    if(strcmp(idStr,"simpleStmt")==0) return simpleStmt;
    if(strcmp(idStr,"assignmentStmt")==0) return assignmentStmt;
    if(strcmp(idStr,"whichStmt")==0) return whichStmt;
    if(strcmp(idStr,"lvalueIDStmt")==0) return lvalueIDStmt;
    if(strcmp(idStr,"lvalueARRStmt")==0) return lvalueARRStmt;
    if(strcmp(idStr,"index")==0) return index;
    if(strcmp(idStr,"moduleReuseStmt")==0) return moduleReuseStmt;
    if(strcmp(idStr,"optional")==0) return optional;
    if(strcmp(idStr,"idList")==0) return idList;
    if(strcmp(idStr,"N3")==0) return N3;
    if(strcmp(idStr,"U")==0) return U;
    if(strcmp(idStr,"new_NT")==0) return new_NT;
    if(strcmp(idStr,"unary_op")==0) return unary_op;
    if(strcmp(idStr,"arithmeticOrBooleanExpr")==0) return arithmeticOrBooleanExpr;
    if(strcmp(idStr,"N7")==0) return N7;
    if(strcmp(idStr,"AnyTerm")==0) return AnyTerm;
    if(strcmp(idStr,"N8")==0) return N8;
    if(strcmp(idStr,"expression")==0) return expression;
    if(strcmp(idStr,"arithmeticExpr")==0) return arithmeticExpr;
    if(strcmp(idStr,"N4")==0) return N4;
    if(strcmp(idStr,"term")==0) return term;
    if(strcmp(idStr,"N5")==0) return N5;
    if(strcmp(idStr,"factor")==0) return factor;
    if(strcmp(idStr,"op1")==0) return op1;
    if(strcmp(idStr,"op2")==0) return op2;
    if(strcmp(idStr,"logicalOp")==0) return logicalOp;
    if(strcmp(idStr,"relationalOp")==0) return relationalOp;
    if(strcmp(idStr,"declareStmt")==0) return declareStmt;
    if(strcmp(idStr,"conditionalStmt")==0) return conditionalStmt;
    if(strcmp(idStr,"caseStmts")==0) return caseStmts;
    if(strcmp(idStr,"N9")==0) return N9;
    if(strcmp(idStr,"value")==0) return value;
    if(strcmp(idStr,"default")==0) return Default;
    if(strcmp(idStr,"iterativeStmt")==0) return iterativeStmt;
    if(strcmp(idStr,"range_arrays")==0) return range_arrays;
    if(strcmp(idStr,"range")==0) return range;

    // For Terminals

    if(strcmp(idStr,"ID")==0) return ID;
    if(strcmp(idStr,"NUM")==0) return NUM;
    if(strcmp(idStr,"RNUM")==0) return RNUM;
    if(strcmp(idStr,"INTEGER")==0) return INTEGER;
    if(strcmp(idStr,"REAL")==0) return REAL;
    if(strcmp(idStr,"BOOLEAN")==0) return BOOLEAN;
    if(strcmp(idStr,"OF")==0) return OF;
    if(strcmp(idStr,"ARRAY")==0) return ARRAY;
    if(strcmp(idStr,"START")==0) return START;
    if(strcmp(idStr,"END")==0) return END;
    if(strcmp(idStr,"DECLARE")==0) return DECLARE;
    if(strcmp(idStr,"MODULE")==0) return MODULE;
    if(strcmp(idStr,"DRIVER")==0) return DRIVER;
    if(strcmp(idStr,"PROGRAM")==0) return PROGRAM;
    if(strcmp(idStr,"GET_VALUE")==0) return GET_VALUE;
    if(strcmp(idStr,"PRINT")==0) return PRINT;
    if(strcmp(idStr,"USE")==0) return USE;
    if(strcmp(idStr,"WITH")==0) return WITH;
    if(strcmp(idStr,"PARAMETERS")==0) return PARAMETERS;
    if(strcmp(idStr,"TRUE")==0) return TRUE;
    if(strcmp(idStr,"FALSE")==0) return FALSE;
    if(strcmp(idStr,"TAKES")==0) return TAKES;
    if(strcmp(idStr,"INPUT")==0) return INPUT;
    if(strcmp(idStr,"RETURNS")==0) return RETURNS;
    if(strcmp(idStr,"AND")==0) return AND;
    if(strcmp(idStr,"OR")==0) return OR;
    if(strcmp(idStr,"FOR")==0) return FOR;
    if(strcmp(idStr,"IN")==0) return IN;
    if(strcmp(idStr,"SWITCH")==0) return SWITCH;
    if(strcmp(idStr,"CASE")==0) return CASE;
    if(strcmp(idStr,"BREAK")==0) return BREAK;
    if(strcmp(idStr,"DEFAULT")==0) return DEFAULT;
    if(strcmp(idStr,"WHILE")==0) return WHILE;
    if(strcmp(idStr,"PLUS")==0) return PLUS;
    if(strcmp(idStr,"MINUS")==0) return MINUS;
    if(strcmp(idStr,"MUL")==0) return MUL;
    if(strcmp(idStr,"DIV")==0) return DIV;
    if(strcmp(idStr,"LT")==0) return LT;
    if(strcmp(idStr,"LE")==0) return LE;
    if(strcmp(idStr,"GE")==0) return GE;
    if(strcmp(idStr,"GT")==0) return GT;
    if(strcmp(idStr,"EQ")==0) return EQ;
    if(strcmp(idStr,"NE")==0) return NE;
    if(strcmp(idStr,"DEF")==0) return DEF;
    if(strcmp(idStr,"ENDEF")==0) return ENDDEF;
    if(strcmp(idStr,"DRIVERDEF")==0) return DRIVERDEF;
    if(strcmp(idStr,"DRIVERENDDEF")==0) return DRIVERENDDEF;
    if(strcmp(idStr,"COLON")==0) return COLON;
    if(strcmp(idStr,"RANGEOP")==0) return RANGEOP;
    if(strcmp(idStr,"SEMICOL")==0) return SEMICOL;
    if(strcmp(idStr,"COMMA")==0) return COMMA;
    if(strcmp(idStr,"ASSIGNOP")==0) return ASSIGNOP;
    if(strcmp(idStr,"SQBO")==0) return SQBO;
    if(strcmp(idStr,"SQBC")==0) return SQBC;
    if(strcmp(idStr,"BO")==0) return BO;
    if(strcmp(idStr,"BC")==0) return BC;
    if(strcmp(idStr,"$")==0) return $;
    if(strcmp(idStr,"eps")==0) return eps;

}

int idbatao(char *idStr) {
     // For Non - Terminals
    if(strcmp(idStr, "program") == 0) return 0;
    if(strcmp(idStr, "moduleDeclarations") == 0) return 1;
    if(strcmp(idStr, "moduleDeclaration") == 0) return 3;
    if(strcmp(idStr, "otherModules") == 0) return 4;
    if(strcmp(idStr,"driverModule")==0) return 6;
    if(strcmp(idStr,"moduleDef")==0) return 7;
    if(strcmp(idStr,"module")==0) return 8;
    if(strcmp(idStr,"ret")==0) return 9;
    if(strcmp(idStr,"input_plist")==0) return 11;
    if(strcmp(idStr,"N1")==0) return 12;
    if(strcmp(idStr,"output_plist")==0) return 14;
    if(strcmp(idStr,"N2")==0) return 15;
    if(strcmp(idStr,"dataType")==0) return 17;
    if(strcmp(idStr,"type")==0) return 21;
    if(strcmp(idStr,"statements")==0) return 24;
    if(strcmp(idStr,"statement")==0) return 26;
    if(strcmp(idStr,"ioStmt")==0) return 31;
    if(strcmp(idStr,"boolConstt")==0) return 33;
    if(strcmp(idStr,"var_id_num")==0) return 35;
    if(strcmp(idStr,"var")==0) return 38;
    if(strcmp(idStr,"whichId")==0) return 40;
    if(strcmp(idStr,"simpleStmt")==0) return 42;
    if(strcmp(idStr,"assignmentStmt")==0) return 44;
    if(strcmp(idStr,"whichStmt")==0) return 45;
    if(strcmp(idStr,"lvalueIDStmt")==0) return 47;
    if(strcmp(idStr,"lvalueARRStmt")==0) return 48;
    if(strcmp(idStr,"index")==0) return 49;
    if(strcmp(idStr,"moduleReuseStmt")==0) return 51;
    if(strcmp(idStr,"optional")==0) return 52;
    if(strcmp(idStr,"idList")==0) return 54;
    if(strcmp(idStr,"N3")==0) return 55;
    if(strcmp(idStr,"U")==0) return 57;
    if(strcmp(idStr,"new_NT")==0) return 58;
    if(strcmp(idStr,"unary_op")==0) return 60;
    if(strcmp(idStr,"arithmeticOrBooleanExpr")==0) return 62;
    if(strcmp(idStr,"N7")==0) return 63;
    if(strcmp(idStr,"AnyTerm")==0) return 65;
    if(strcmp(idStr,"N8")==0) return 67;
    if(strcmp(idStr,"expression")==0) return 69;
    if(strcmp(idStr,"arithmeticExpr")==0) return 71;
    if(strcmp(idStr,"N4")==0) return 72;
    if(strcmp(idStr,"term")==0) return 74;
    if(strcmp(idStr,"N5")==0) return 75;
    if(strcmp(idStr,"factor")==0) return 77;
    if(strcmp(idStr,"op1")==0) return 78;
    if(strcmp(idStr,"op2")==0) return 80;
    if(strcmp(idStr,"logicalOp")==0) return 82;
    if(strcmp(idStr,"relationalOp")==0) return 84;
    if(strcmp(idStr,"declareStmt")==0) return 90;
    if(strcmp(idStr,"conditionalStmt")==0) return 91;
    if(strcmp(idStr,"caseStmts")==0) return 92;
    if(strcmp(idStr,"N9")==0) return 93;
    if(strcmp(idStr,"value")==0) return 95;
    if(strcmp(idStr,"default")==0) return 98;
    if(strcmp(idStr,"iterativeStmt")==0) return 100;
    if(strcmp(idStr,"range_arrays")==0) return 102;
    if(strcmp(idStr,"range")==0) return 103;
}


void findfirstofstring(unit * ptr , int * array,int k)
{
    unit * temp = ptr;
    int index = 0;
    int count = 0;
    int flag= 0;
    while(ptr != NULL)
    {
       

        if(ptr->terminal == 1)
        {   
            unit * temp = firstarray[idbatao(ptr->term)];
           
            flag =0;
            while(temp->next != NULL)
            {
               
                array[count] = parseIdStr(temp->next->term);
                temp = temp ->next;
                if(array[count] == 57)
                {
                    flag = 1;
                    
                }
                count++;
            }
        }
        else
        {
            array[count++] = parseIdStr(ptr->term);
            break;
        }

        if(flag == 0 )
        {   
            break;
        }
        ptr = ptr->next;
    }
}

void createParseTable()
{

    int leftid;
    for(int i=0; i<57; i++)
    {
      for(int j=0; j<57; j++)
      {
        table[i][j] = -1;
      }
    }

    int rightside[30] ;
    int firstarr[30] ;
    int followarr[30];

    for(int k = 0 ; k < arraySize ; k++)
    {

        for(int i = 0; i < 30;i++)
        {
            rightside[i] = -1;
            firstarr[i] = -1;
            followarr[i] = -1;
        }

        leftid = parseIdStr(grammararray[k] -> term);
        

        unit* ptr = grammararray[k];

          int countg =0;
          unit *ptr1 = ptr->next;
          unit *ptr2 = ptr1;
          int flag = 0;
          while(ptr2 !=NULL)
          {
            if(strcmp(ptr2->term,"eps")==0)
            {
              flag = 1;
            }
            ptr2 = ptr2 ->next;
          }

      if(flag == 1)
      {
        unit * adv = followarray[idbatao(grammararray[k]->term)];
        int countadv = 0;
        while(adv->next != NULL)
        {
            followarr[countadv++] = parseIdStr(adv->next->term);
            adv = adv ->next;
        }
       
        for(int f =0;f<30;f++)
        {
            if(followarr[f] != 57 && followarr[f] != -1)
            {
                table[leftid][followarr[f]] = k;
                
            }
        }
        
      }
      else
      {
        findfirstofstring(ptr1 , firstarr , k);

        

        for(int f =0;f<30;f++)
        {
            if(firstarr[f] != -1 && firstarr[f] != 57)
            {
                table[leftid][firstarr[f]] = k;
            }
            else if(firstarr[f] == 57)
            {
                unit * ful = followarray[leftid];

                while(ful->next != NULL)
                {
                    if(strcmp(ful->next->term,"eps")!=0)
                    {
                        table[leftid][parseIdStr(ful->next->term)] = k;
                    }

                    ful = ful->next;
                }
            }
        }
    }

}
}

void printScope(scopeTree* scope){
    if(scope == NULL){
        return;
    }
    printf("%s %s %u start:%u end:%u\n",scope->scopename,scope->modulescope,scope->depth,scope->startline,scope->endline);
    for(int i = 0; i < scope->numNested; i++){
        printScope(&scope->children[i]);
    }
}

scopeTree* findScope(scopeTree* scope, char* name){
    if(scope == NULL){
        return NULL;
    }

    if(strcmp(scope->scopename,name)==0){
        return scope;
    }

    scopeTree* temp;

    for(int i = 0; i < scope->numNested; i++){
        temp = findScope(&scope->children[i],name);
        if(temp!=NULL){
            return temp;
        }
    }
    return NULL;
}

void nest(scopeTree*s,char* child){
    int n = s->numNested;
    s->numNested++;
    s->children = realloc(s->children,sizeof(scopeTree)*(s->numNested+1));
    strcpy(s->children[n].scopename,child);
    s->children[n].numNested = 0;
    s->children[n].children = NULL;
    s->children[n].parent = s;
    s->children[n].depth = s->depth+1;
    if(s->parent == NULL){
      strcpy(s->children[n].modulescope,child);
    }else{
      strcpy(s->children[n].modulescope,s->modulescope);
    }
}

char *idRepr(int id) {
    // returns the printable representation of an id
        if(id == program) return "program";
        if(id == moduleDeclarations) return "moduleDeclarations";
        if(id == moduleDeclaration) return "moduleDeclaration";
        if(id == otherModules) return "otherModules";
    if(id == driverModule) return "driverModule";
    if(id == moduleDef) return "moduleDef";
    if(id == module) return "module";
    if(id == ret) return "ret";
    if(id == input_plist) return "input_plist";
    if(id == N1) return "N1";
    if(id == output_plist) return "output_plist";
    if(id == N2) return "N2";
    if(id == dataType) return "dataType";
    if(id == type) return "type";
    if(id == statements) return "statements";
    if(id == statement) return "statement";
    if(id == ioStmt) return "ioStmt";
    if(id == boolConstt) return "boolConstt";
    if(id == var_id_num) return "var_id_num";
    if(id == var) return "var";
    if(id == whichId) return "simpleStmt";
    if(id == simpleStmt) return "simpleStmt";
    if(id == assignmentStmt) return "assignmentStmt";
    if(id == whichStmt) return "whichStmt";
    if(id == lvalueIDStmt) return "lvalueIDStmt";
    if(id == lvalueARRStmt) return "lvalueARRStmt";
    if(id == index) return "index";
    if(id == moduleReuseStmt) return "moduleReuseStmt";
    if(id == optional) return "optional";
    if(id == idList) return "idList";
    if(id == N3) return "N3";
    if(id == U) return "U";
    if(id == new_NT) return "new_NT";
    if(id == unary_op) return "unary_op";
    if(id == arithmeticOrBooleanExpr) return "arithmeticOrBooleanExpr";
    if(id == N7) return "N7";
    if(id == AnyTerm) return "AnyTerm";
    if(id == N8) return "N8";
    if(id == expression) return "expression";
    if(id == arithmeticExpr) return "arithmeticExpr";
    if(id == N4) return "N4";
    if(id == term) return "term";
    if(id == N5) return "N5";
    if(id == factor) return "factor";
    if(id == op1) return "op1";
    if(id == op2) return "op2";
    if(id == logicalOp) return "logicalOp";
    if(id == relationalOp) return "relationalOp";
    if(id == declareStmt) return "declareStmt";
    if(id == conditionalStmt) return "conditionalStmt";
            if(id == caseStmts) return "caseStmts";
        if(id == N9) return "N9";
       if(id == value) return "value";
       if(id == Default) return "default";
            if(id == iterativeStmt) return "iterativeStmt";
       if(id == range_arrays) return "range_arrays";
       if(id == range) return "range";
       return "root";
}


void push(char* term, int termin){
  struct unit* temp = (unit*)malloc(sizeof(unit));
  if (!temp){
    exit(1);
  }
  temp->term = term;
  temp->terminal = termin;
  temp->next = top;
  top = temp;
}

int isEmpty(){
  return top == NULL;
}

unit* peek(){
  if (!isEmpty()){
    struct unit* temp;
    temp = top;
    return temp;
  }
  else{
    exit(1);
  }
}

void pop(){
  struct unit* temp;
  if (top == NULL) {
    exit(1);
  }
  else{
    temp = top;
    top = top->next;
    temp->next = NULL;
    free(temp);
  }
}

void display(){
  struct unit* temp;
  if (top == NULL) {
    exit(1);
  }else{
    temp = top;
    while (temp != NULL){
      printf("%s\n",temp->term);
      temp = temp->next;
    }
  }
  printf("\n");
}

void reversepush(struct unit* head){
  if (head == NULL || head->term == "eps")
  return;

  reversepush(head->next);
  push(head->term , head-> terminal);
}

void parse( FILE *fg, parseTree *p )
{
    if(strcmp(temp->tokenName,"EOF")==0)
    {  
        temp->tokenName = "$";
    }
    
    int columnid = parseIdStr(temp->tokenName);

    unit * piku = peek();
    if(strcmp(piku->term,"$")==0)
    {
        return;
    }
    int rowid = parseIdStr(piku ->term);


    if(piku->terminal == 1)
    {

    
      int grammarno =  table[rowid][columnid];

          if(grammarno >= 0 )
          {     
                unit * gru = grammararray[grammarno];
                unit * gram = gru;
                unit * gram1 = gru;
                unit * gggg = gru;
                pop();
                reversepush(gru->next);

                int child = 0;
                while(gram->next!=NULL)
                {
                  child++;
                  gram = gram->next;
                }

                p->noOfChildren = child;
                p->children = (parseTree *)calloc(p->noOfChildren , sizeof(parseTree));
                p->ruleno = grammarno;
                int count = 0;

                while(gru ->next != NULL)
                {
                      unit* temp1 = gru->next;
                      if(temp1->terminal == 0)
                      {

                        p->children[count].isTerminal = 0;
                        p->children[count].terminal.tokenName = temp1->term;
                        p->children[count].noOfChildren = 0;
                        p->children[count].ruleno = -1;
                        p->children[count].parent = p;
                        p->children[count].childnum = count;
                        p->children[count].generated = 0;
                        
                      }
                     else
                      {
                        p->children[count].isTerminal = 1;
                        p->children[count].nonTerminal = parseIdStr(temp1->term);
                        p->children[count].noOfChildren = 0;
                        p->children[count].ruleno = -1;
                        p->children[count].parent = p;
                        p->children[count].childnum = count;
                        p->children[count].generated = 0;
                        
                      }
                       gru = gru ->next;
                       count++;
                  }

                  for(int j = 0; j < p->noOfChildren; j++)
                  {
                      if(p->children[j].isTerminal == 0)
                      {
                          if(strcmp(p->children[j].terminal.tokenName , "eps")==0)
                          {
                              pop();
                              return;
                          }
                          else
                          {
                              parse(fg, &p->children[j]);
                              
                          }

                      }
                      else
                      {
                            parse(fg, &p->children[j]);
                            
                      }



                  }

            }
        else
            {
                if(grammarno == -1)
                {
                    printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
                      errorflag =1;
                      int flag = 1;
                      unit * teemp;
                      while(flag == 1)
                      {
                        teemp = peek();
                        if(teemp->terminal==0)
                        {
                            pop();
                        }
                        else
                        {
                            flag = 0;
                        }
                      }
                      temp = getnexttoken(fg,temp);

                      int colno = parseIdStr(temp->tokenName);
                      int rowno = parseIdStr(teemp -> term);

                      int grano =  table[rowno][colno];

                      int flaggy = 1;
                      while(flaggy == 1)
                      {
                        if(grano >= 0 || grano == -200)
                        {
                            flaggy = 0;
                            if(grano == -200)
                            {
                                  pop();
                                  //parse( fg, p);
                                  //return;
                            }
                        }
                        else
                        {
                            unit * sany = firstarray[idbatao(teemp->term)];

                            while(sany->next != NULL)
                            {
                                if(strcmp(sany->next->term,temp->tokenName)==0)
                                {
                                    flaggy = 0;
                                    break;
                                }
                                sany = sany->next;
                            }

                            if(flaggy != 0)
                            {
                                temp = getnexttoken(fg,temp);
                                grano =  table[rowno][parseIdStr(temp->tokenName)];
                            }

                        }
                      }

                    parse( fg, p);
                    return;

                    }
              else
              {
                /*if(grammarno == -200)
                {
                      //pop();
                      parse( fg, p);
                      return;
                }*/
              }
        }
    }
    else
    {  
            if(p->isTerminal == 0){
              if(strcmp(p->terminal.tokenName,"eps")==0)
              {   
                  pop();
                  display();
                  return;
              }
            }

            if(strcmp(temp->tokenName ,"EOF")==0)
            {
            
              return;
            }
            else if(strcmp(piku->term , temp->tokenName)!=0)
            {
              printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
              errorflag =1;
              int flag = 1;
              unit * teemp;
              while(flag == 1)
              {
                teemp = peek();
                if(teemp->terminal==0)
                {
                    pop();
                }
                else
                {
                    flag = 0;
                }
              }
              
                      int colno = parseIdStr(temp->tokenName);
                      int rowno = parseIdStr(teemp -> term);

                      int grano =  table[rowno][colno];

                      int flaggy = 1;

                      while(flaggy == 1)
                      {
                        if(grano >= 0 || grano == -200)
                        {
                            flaggy = 0;
                            if(grano == -200)
                            {
                                  pop();
                                  //parse( fg, p);
                                  //return;
                            }
                        }
                        else
                        {
                            unit * sany = firstarray[idbatao(teemp->term)];

                            while(sany->next != NULL)
                            {
                                if(strcmp(sany->next->term,temp->tokenName)==0)
                                {
                                    flaggy = 0;
                                    break;
                                }
                                sany = sany->next;
                            }

                            if(flaggy != 0)
                            {
                                temp = getnexttoken(fg,temp);
                                grano =  table[rowno][parseIdStr(temp->tokenName)];
                            }

                        }
                      }


              //temp = getnexttoken(fg,temp);
              
              
              //parse( fg, p);
              return;
            }
            else
            {
              
              p->terminal.lineNum = temp->lineNum;
              strcpy(p->terminal.lexeme ,temp->lexeme);
              p->terminal.tokenName = temp->tokenName;
          
              pop();
              
              temp = getnexttoken(fg,temp);
              
              return;
            }
            
        }
}


void printParseTree(parseTree *p )
{
  if(errorflag ==1)
  {
    printf("SYNTACTIC error \n");
  }
  else{

      int chill = p->noOfChildren;

  if(chill > 0)
  {
    printParseTree(&p->children[0] );
      int j;
      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
            printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("%s",idRepr(p->parent->nonTerminal));
      for(j=strlen(idRepr(p->parent->nonTerminal));j<=25;j++)
            printf(" ");


      printf("NO");
      for(j=0;j<=6;j++)
            printf(" ");


      printf("%s",idRepr(p->nonTerminal));
      for(j=strlen(idRepr(p->nonTerminal));j<=20;j++)
            printf(" ");

      printf("\n");

      for(int j=1; j < chill; j++)
      printParseTree(&p->children[j] );

  }
  else
  {
      if(p->isTerminal == 0)
      {
        int j;
        printf("%s",p->terminal.lexeme);
        for(j=strlen(p->terminal.lexeme);j<=19;j++)
            printf(" ");

        printf("%d",p->terminal.lineNum);
        for(j=0;j<=19;j++)
            printf(" ");

        printf("%s",p->terminal.tokenName);
        for(j=strlen(p->terminal.tokenName);j<=20;j++)
            printf(" ");

        printf("%s",p->terminal.lexeme);
        for(j=strlen(p->terminal.lexeme);j<=20;j++)
            printf(" ");


        printf("%s",idRepr(p->parent->nonTerminal));
        for(j=strlen(idRepr(p->parent->nonTerminal));j<=25;j++)
            printf(" ");

        printf("YES");
        for(j=0;j<=5;j++)
            printf(" ");

        printf(" ----");
        for(j=0;j<=16;j++)
            printf(" ");
        printf("\n");

      }
      else{
        return;
      }
  }

}
}



void printastree(parseTree *pt )
{if(pt == NULL)
  {
      printf("\nTree is empty\n");
      return;
  }
  if(errorflag ==1)
  {
    printf("SYNTACTIC error\n");
    return;
  }
  else
  {

    int chill = pt-> noOfChildren;

    if(chill > 0)
    {
      int j;
      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
            printf(" ");

      printf("----");
      for(j=0;j<=16;j++)
      printf(" ");

      printf("%s",idRepr(pt->parent->nonTerminal));
      for(j=strlen(idRepr(pt->parent->nonTerminal));j<=25;j++)
            printf(" ");


      printf("NO");
      for(j=0;j<=6;j++)
            printf(" ");


      printf("%s",idRepr(pt->nonTerminal));
      for(j=strlen(idRepr(pt->nonTerminal));j<=20;j++)
            printf(" ");

      printf("\n");



        printastree(&pt->children[0]);



        for(int j=1; j < chill; j++)
        {
            printastree(&pt->children[j]);
        }

    }
    else
    {
      if(pt->isTerminal == 0)
      {
        int j;
        printf("%s",pt->terminal.lexeme);
        for(j=strlen(pt->terminal.lexeme);j<=19;j++)
            printf(" ");

        printf("%d",pt->terminal.lineNum);
        for(j=0;j<=19;j++)
            printf(" ");

        printf("%s",pt->terminal.tokenName);
        for(j=strlen(pt->terminal.tokenName);j<=20;j++)
            printf(" ");

        printf("%s",pt->terminal.lexeme);
        for(j=strlen(pt->terminal.lexeme);j<=20;j++)
            printf(" ");


        printf("%s",idRepr(pt->parent->nonTerminal));
        for(j=strlen(idRepr(pt->parent->nonTerminal));j<=25;j++)
            printf(" ");

        printf("YES");
        for(j=0;j<=5;j++)
            printf(" ");

        printf(" ----");
        for(j=0;j<=16;j++)
            printf(" ");
        printf("\n");
      }
      else
     {
          int j;
          printf("----");
          for(j=0;j<=16;j++)
          printf(" ");

          printf("----");
          for(j=0;j<=16;j++)
          printf(" ");

          printf("----");
          for(j=0;j<=16;j++)
                printf(" ");

          printf("----");
          for(j=0;j<=16;j++)
          printf(" ");

          printf("%s",idRepr(pt->parent->nonTerminal));
          for(j=strlen(idRepr(pt->parent->nonTerminal));j<=25;j++)
                printf(" ");


          printf("NO");
          for(j=0;j<=6;j++)
                printf(" ");


          printf("%s",idRepr(pt->nonTerminal));
          for(j=strlen(idRepr(pt->nonTerminal));j<=20;j++)
                printf(" ");

          printf("\n");
        }
    }

}
}








int isUseful(char * idStr) {
    if(strcmp(idStr, "PRINT") == 0) return 1;
    if(strcmp(idStr, "AND") == 0) return 1;
    if(strcmp(idStr, "EQ") == 0) return 1;
    if(strcmp(idStr, "GE") == 0) return 1;
    if(strcmp(idStr, "NE") == 0) return 1;
    if(strcmp(idStr, "LE") == 0) return 1;
    if(strcmp(idStr, "GT") == 0) return 1;
    if(strcmp(idStr, "LT") == 0) return 1;
    if(strcmp(idStr, "DIV") == 0) return 1;
    if(strcmp(idStr, "MUL") == 0) return 1;
    if(strcmp(idStr, "MINUS") == 0) return 1;
    if(strcmp(idStr, "PLUS") == 0) return 1;
    if(strcmp(idStr, "RNUM") == 0) return 1;
    if(strcmp(idStr, "NUM") == 0) return 1;
    if(strcmp(idStr, "ID") == 0) return 1;
    if(strcmp(idStr, "WHILE") == 0) return 1;
    if(strcmp(idStr, "FALSE") == 0) return 1;
    if(strcmp(idStr, "TRUE") == 0) return 1;
    if(strcmp(idStr, "GET_VALUE") == 0) return 1;
    if(strcmp(idStr, "ARRAY") == 0) return 1;
    if(strcmp(idStr, "BOOLEAN") == 0) return 1;
    if(strcmp(idStr, "REAL") == 0) return 1;
    if(strcmp(idStr, "INTEGER") == 0) return 1;
    if(strcmp(idStr, "FOR") == 0) return 1;
    if(strcmp(idStr, "OR") == 0) return 1;
    if(strcmp(idStr, "ASSIGNOP")==0) return 1;
    if(strcmp(idStr, "START")==0) return 1;
    if(strcmp(idStr, "END")==0) return 1;
    else return 0;
}

void createAbstractSyntaxTree(parseTree *p, parseTree *ast)
{

    int i, j, usefulChildrenCount = 0;

    for(i = 0; i < p->noOfChildren; i++)
        // all nonterminals are useful
        if(p->children[i].isTerminal == 1 || isUseful(p->children[i].terminal.tokenName))
            usefulChildrenCount++;

    ast->noOfChildren = usefulChildrenCount;
    ast->ruleno = p->ruleno;

    ast->children = (parseTree *)calloc(ast->noOfChildren , sizeof(parseTree));
  

    i = 0, j = 0;
    while(i < p->noOfChildren) {
        if(p->children[i].isTerminal == 0) {
            if(isUseful(p->children[i].terminal.tokenName)) {
                // copy ith node of p to jth node of ast
                
                ast->children[j].isTerminal = 0;
               
                ast->children[j].terminal.tokenName = p->children[i].terminal.tokenName;
              
                strcpy(ast->children[j].terminal.lexeme, p->children[i].terminal.lexeme);
                ast->children[j].terminal.lineNum = p->children[i].terminal.lineNum;
                ast->children[j].ruleno = p->children[i].ruleno;
                ast->children[j].noOfChildren = 0;
                ast->children[j].parent = ast;
                ast->children[j].childnum = j;
                ast->children[j].generated = p->children[i].generated;
                
                j++;
            }
        }
        else {
            // recursively construct the ast rooted here
           
            if(p->children[i].noOfChildren > 0)
            {
                ast->children[j].nonTerminal = p->children[i].nonTerminal;
                ast->children[j].isTerminal = 1;
                ast->children[j].ruleno = p->children[i].ruleno;
                ast->children[j].noOfChildren = 0;
                ast->children[j].parent = ast;
                ast->children[j].childnum = j;
                ast->children[j].generated = p->children[i].generated;
                
                createAbstractSyntaxTree(&p->children[i], &ast->children[j]);
                j++;
            }
            else
            {
                return;
            }
        }
        i++;
    }
}

int length(parseTree *tree){
  if(tree == NULL){
    return 0;
  }
  int len = 1;
  for(int a=0;a<tree->noOfChildren;a++){
    len += length(&tree->children[a]);
  }
  return len;
}