// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include "symboltable.h"


int count, funcnum = 0;
char array[100][100];

char* my_itoa(int number) {
   char* str = calloc(3,sizeof(char));
   sprintf(str, "%d", number);
   return str;
}



char* strcat(char* destination, const char* source){

char* ptr = destination + strlen(destination);

while (*source != '\0')
*ptr++ = *source++;
*ptr = '\0';


return destination;
}


void *memset(void *blk, int c, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i)
        ((unsigned char *) blk)[i] = c;

    return blk;
}

int strncmp( const char * s1, const char * s2, size_t n )
{
    while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}

char* strtok(char *str, const char* delim) {
    static char* _buffer;
    if(str != NULL) _buffer = str;
    if(_buffer[0] == '\0') return NULL;

    char *ret = _buffer, *b;
    const char *d;

    for(b = _buffer; *b !='\0'; b++) {
        for(d = delim; *d != '\0'; d++) {
            if(*b == *d) {
                *b = '\0';
                _buffer = b+1;

                // skip the beginning delimiters
                if(b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }

    return ret;
}

struct hash_table* create_hash_table(){
    struct hash_table *node = (struct hash_table *)calloc(1,sizeof(struct hash_table));
    return node;
}

struct tokNode* create_node(char *key, char *type, char* funcname, char* ifnumval , int inputtvar){
    struct tokNode *node = (struct tokNode *)calloc(1,sizeof(struct tokNode));
    strcpy(node->name, key);
    strcpy(node->ifnumvalue, ifnumval);
    strcpy(node->scope, funcname);
    strcpy(node->type, type);
    node->offset = 0;
    node->width = 0;
    node->next = NULL;
    node->inputvar = inputtvar;
    node->r1 = -1;
    node->r2 = -1;
    node->isdynamic = 0;

    strcpy(node->parentscope,"");
    strcpy(node->isarray,"no");
    strcpy(node->isstatic,"");
    node->stline = 0;
    node->endline = 0;
    node->depthlevel = 0;

    return node;
}

struct functionNode* create_function_node(char *funcname, char *inparam, char *outparam){
    struct functionNode *node = (struct functionNode *)calloc(1,sizeof(struct functionNode));
    strcpy(node->name, funcname);
    strcpy(node->input, inparam);
    strcpy(node->output, outparam);
    return node;
}

int hash(char *key){
    int value = 0;
    int i;
    for(i = 0; i < strlen(key); i++){
        value += (int)key[i];
    }
    return (value % SIZE);
}

int insert_function_in_hash(char *key, char* inparam, char* outparam){
    
    int value = hash(key);
    struct functionNode* iter = create_function_node(key, inparam, outparam);
    if(iter == NULL){
        return 0;
    }
    while(functable->table[value]->next != NULL){
        value++;
    }
    functable->table[value]->next = iter;
    strcpy(array[funcnum++], key);

    return value;
}


int get_function_value(char* funcname){
    int value = hash(funcname);
    while(functable->table[value]->next != NULL){
        if(strcmp(functable->table[value]->next->name, funcname) == 0){
            return value;
        }
        value++;
    }
    return -1;
}

void func_display(){
    int m;
    int j = 1;
    fnode* iter;
    for(m = 0; m < SIZE; m++){
        if(functable->table[m]->next != NULL && ((int)(functable->table[m]->next->name) < 100000000)){
            iter = functable->table[m]->next;
           
        }
    }
}

char* get_input_type(char* functionname){

    int i;
    //char intype[1000] = {'\0'};
    char * intype = malloc(1000);
    int j = 1;

    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(intype, functable->table[i]->next->input);
            }
        }
    }
    return intype;
}


char* get_output_type(char* functionname){
    int i;
    int j=1;
    char *outtype = malloc(1000);
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(outtype, functable->table[i]->next->output);
            }
        }
    }
    return outtype;
}

int if_func_present(char* funcname){
    int i;
    int j = 1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,funcname) == 0){
               return 1;
            }
        }
    }
    return 0;
}

fnode* functionpointer(char* funcname){
    int a;
    for(a=0;a<SIZE;a++){
        if(functable->table[a]->next != NULL && ((int)(functable->table[a]->next->name) < 100000000)){
            if(strcmp(functable->table[a]->next->name,funcname) == 0){
               return functable->table[a]->next;
            }
        }
    }
    return NULL;
}

int offseter = 0;
int sequencenum = 1;
int offset = 0;

int insertinhash(char* key, char* type, char* functionname, char* ifnumvalue, int inputvar)
{
    
    int j = get_function_value(functionname);
    int value = hash(key);
    struct tokNode* iter = create_node(key, type, functionname, ifnumvalue , inputvar );
    if(iter == NULL){
        return 0;
    }
    
    while(ht->functable[j]->table[value]->next != NULL){
             
        value++;
    }
     
    ht->functable[j]->table[value]->next = iter;
    int width =0;
       if(strcmp(ht->functable[j]->table[value]->next->type,"INTEGER") ==0){
        width = 2;
       }
       if(strcmp(ht->functable[j]->table[value]->next->type,"REAL") ==0){
        width = 4;
       }
       if(strcmp(ht->functable[j]->table[value]->next->type,"BOOLEAN") ==0){
           width = 1;
       }
        
       if(strncmp(ht->functable[j]->table[value]->next->type,"ARRAY",5) ==0){
        char type[50];
        memset(type, '\0', sizeof(type));
        strcpy(type, ht->functable[j]->table[value]->next->type);
        int range = 0;

                char *tok = NULL;
                    tok = strtok(type, "(");
                    if(tok!=NULL){
                        tok = strtok(NULL, ",");

                        if(strcmp(tok, "INTEGER")==0)
                            width = 2;
                        if(strcmp(tok, "REAL")==0)
                            width = 4;
                        if(strcmp(tok, "BOOLEAN")==0)
                            width = 1;

                        tok = strtok(NULL, ")");
                        if(tok!=NULL){
                            range = atoi(tok);

                        }}


                // assert(0);

        width = width*range+1;
       }
        ht->functable[j]->table[value]->next->width = width;

        ht->functable[j]->table[value]->next->offset = offset;
        offset += width;
        
    return 1;
}

int ifsymbolpresent(char *key, char* funcname){
    int a = get_function_value(funcname);
    int value = hash(key);
    if(ht->functable[a]->table[value]==NULL){
        return 0;
    }

    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0)
        {
            if(ht->functable[a]->table[value]->next->inputvar == 1 )
                return 2;
            else
                return 1;
        }
        value++;
    }

    return 0;
}

int overwrite(char *key, char* type, char* funcname, char* ifnumvalue, int inputvar){
    int a = get_function_value(funcname);
    int value = hash(key);
    if(ht->functable[a]->table[value]==NULL){
        return 0;
    }
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0)
        {
            if(ht->functable[a]->table[value]->next->inputvar == 1)
            {
                strcpy(ht->functable[a]->table[value]->next->name , key);
                strcpy(ht->functable[a]->table[value]->next->type , type);
                strcpy(ht->functable[a]->table[value]->next->scope , funcname);
                strcpy(ht->functable[a]->table[value]->next->ifnumvalue , ifnumvalue);
                ht->functable[a]->table[value]->next->inputvar = inputvar;

                int width =0;
                   if(strcmp(ht->functable[a]->table[value]->next->type,"INTEGER") ==0){
                    width = 2;
                   }
                   if(strcmp(ht->functable[a]->table[value]->next->type,"REAL") ==0){
                    width = 4;
                   }
                   if(strcmp(ht->functable[a]->table[value]->next->type,"BOOLEAN") ==0){
                       width = 1;
                   }
                
                   if(strncmp(ht->functable[a]->table[value]->next->type,"ARRAY",5) ==0)
                    {
                        char type[50];
                        memset(type, '\0', sizeof(type));
                        strcpy(type, ht->functable[a]->table[value]->next->type);
                        int range = 0;

                                char *tok = NULL;
                                    tok = strtok(type, "(");
                                    if(tok!=NULL){
                                        tok = strtok(NULL, ",");

                                        if(strcmp(tok, "INTEGER")==0)
                                            width = 2;
                                        if(strcmp(tok, "REAL")==0)
                                            width = 4;
                                        if(strcmp(tok, "BOOLEAN")==0)
                                            width = 1;


                                        tok = strtok(NULL, ")");
                                        if(tok!=NULL){
                                            range = atoi(tok);

                                        }}
                        width = width*range+1;
                   }
                    ht->functable[a]->table[value]->next->width = width;
                    ht->functable[a]->table[value]->next->offset = offset;
                    offset += width;
                    return 1;
            }
            else
                return 0;
        }
        value++;
    }
    return 0;
}

int insertrange(char *key,char* funcname, int r1,int r2,int isdynamic ){
    int a = get_function_value(funcname);
    int value = hash(key);
    if(ht->functable[a]->table[value]==NULL){
        return 0;
    }
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0)
        {
            ht->functable[a]->table[value]->next->r1 = r1;
            ht->functable[a]->table[value]->next->r2 = r2;
            ht->functable[a]->table[value]->next->isdynamic = isdynamic;
            return 1;
        }
        value++;
    }
    return 0;
}

int insertvalues(char *key,char* funcname, char *parentscope , int stline , int endline ,char * isarray , char * isstatic , int depthlevel ){
    int a = get_function_value(funcname);
    int value = hash(key);
    if(ht->functable[a]->table[value]==NULL){
        return 0;
    }
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0)
        {
            strcpy(ht->functable[a]->table[value]->next->parentscope , parentscope  );
            strcpy(ht->functable[a]->table[value]->next->isarray , isarray  );
            strcpy(ht->functable[a]->table[value]->next->isstatic , isstatic  );

            ht->functable[a]->table[value]->next->stline = stline;
            ht->functable[a]->table[value]->next->endline = endline;
            ht->functable[a]->table[value]->next->depthlevel = depthlevel;
            return 1;
        }
        value++;
    }
    return 0;
}

int offsetinTable(char* key, char* funcname){
    int a = get_function_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return ht->functable[a]->table[value]->next->offset;
        }
        value++;
    }
    return -1;
}

char* retrievetype(char* key, char* funcname){
    char *sanyam = "";
    scopeTree *funcscope = findScope(s,funcname);
    while(strcmp(funcscope->scopename,"root")!=0){
      funcname = funcscope->scopename;
      //printf("SEARCHING FOR %s IN %s PARENT:%s\n",key,funcscope->scopename,funcscope->parent->scopename);
      int a = get_function_value(funcname);
      int value = hash(key);
      while(ht->functable[a]->table[value]->next != NULL){
          if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
              return ht->functable[a]->table[value]->next->type;
          }
          value++;
      }
      funcscope = funcscope->parent;
    }
    return sanyam;
}

void offsetAutomation(char* funcname){
    int i;
    int a = get_function_value(funcname);
    int offset = 0;
    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"") != 0){
            if(strcmp(ht->functable[a]->table[i]->next->type,"INTEGER") == 0){
                offset += 4;
            }
            if(strcmp(ht->functable[a]->table[i]->next->type,"REAL") == 0){
                offset += 8;
            }
            if(strcmp(ht->functable[a]->table[i]->next->type,"ARRAY") == 0){
                offset += 0;
            }
            ht->functable[a]->table[i]->next->offset = offset;
        }
    }
}

pNode* directpointer(char* key, char* funcname){
    int a = get_function_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return ht->functable[a]->table[value]->next;
        }
        value++;
    }
    return NULL;
}

void display1(char* funcname){
    int i;
    int a = get_function_value(funcname);

    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"")!=0){

            //if(strncmp( ht->functable[a]->table[i]->next->type,"ARRAY",5)==0)
                //printf("%-5d %-20s %-22s %-20s %d %d\n",(sequencenum++),ht->functable[a]->table[i]->next->name,"ARRAY",ht->functable[a]->table[i]->next->scope,ht->functable[a]->table[i]->next->width,offseter);
           // else
                printf("%-3d %-17s %-22s %-20s %-11d %-11d %-5d %-6d [%-4d,%4d] %-10d %-15d %-10s %-10s\n",(sequencenum++),ht->functable[a]->table[i]->next->name,ht->functable[a]->table[i]->next->type, ht->functable[a]->table[i]->next->parentscope , ht->functable[a]->table[i]->next->stline  , ht->functable[a]->table[i]->next->endline  ,ht->functable[a]->table[i]->next->width,offseter,ht->functable[a]->table[i]->next->r1,ht->functable[a]->table[i]->next->r2,ht->functable[a]->table[i]->next->isdynamic, ht->functable[a]->table[i]->next->depthlevel , ht->functable[a]->table[i]->next->isarray , ht->functable[a]->table[i]->next->isstatic );

            offseter += ht->functable[a]->table[i]->next->width;
        }
    }

}
void update(char* funcname){
  int i;
  int a = get_function_value(funcname);

  for(i=0;i<SIZE;i++){
      pNode* iter = ht->functable[a]->table[i]->next;
      scopeTree* sc;
      if(iter != NULL && strcmp(iter->name,"")!=0){
        sc = findScope(s,ht->functable[a]->table[i]->next->scope);
        ht->functable[a]->table[i]->next->endline = sc->endline;
        ht->functable[a]->table[i]->next->stline = sc->startline;;
      }
  }
}
void updateSymbolTable(){
  for(int i=0;i<funcnum;i++){
      update(array[i]);
  }
}
void displaySymbolTable(){
    int i;
    printf("\t\t\t------------------------------- Symbol Table ------------------------------\n\n");
    printf("%-3s %-17s %-22s %-20s %-11s %-11s %-5s %-6s %-11s %-10s %-15s %-10s %-10s\n","No.","Identifier name","Type", "Module Scope", "START_SCOPE","END_SCOPE" ,"Width","Offset","range","isdynamic" , "nesting_level" ,"isarray" ,"isstatic");
    for(i=0;i<funcnum;i++){
        display1(array[i]);
    }

}
pNext getfull(char* key, char* funcname){
    struct tokNode *node1 = (struct tokNode *)calloc(1,sizeof(struct tokNode));
    int a = get_function_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return ht->functable[a]->table[value]->next;
        }
        value++;
    }
    return node1;
}

void displayarrays(char* funcname){
    int i;
    int a = get_function_value(funcname);

    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"")!=0){

            
           if(strncmp( ht->functable[a]->table[i]->next->type,"ARRAY",5)==0){
                printf("%-3d %-16s %-20s %-20s %-11d %-11d [%-3d,%3d] %-10d %-10s\n",(sequencenum++),ht->functable[a]->table[i]->next->name,ht->functable[a]->table[i]->next->type, ht->functable[a]->table[i]->next->parentscope , ht->functable[a]->table[i]->next->stline  , ht->functable[a]->table[i]->next->endline,ht->functable[a]->table[i]->next->r1,ht->functable[a]->table[i]->next->r2,ht->functable[a]->table[i]->next->isdynamic, ht->functable[a]->table[i]->next->isstatic );
           }
           
        }
    }

}

void displayArrayTable(){
    int i;
    printf("\t\t\t---- Static and Dynamic Arrays ----\n");
    printf("%-3s %-16s %-20s %-20s %-11s %-11s %-8s %-10s %-10s\n","No.","Identifier name", "Type with size", "Module Scope", "START_SCOPE","END_SCOPE","range","isdynamic","isstatic");
    for(i=0;i<funcnum;i++){
        displayarrays(array[i]);
    }

}

int calculate(char* funcname){
    int i;
    int offs = 0;
    int a = get_function_value(funcname);

    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"")!=0){
            offs += ht->functable[a]->table[i]->next->width;
        }
    }
    return offs;

}


void printactivation(){
    int i;
    int offs;
    printf("\t\t\t---- Activation Record ----\n");
    printf("%-17s %s \n","Identifier name","Size");
    for(i=0;i<funcnum;i++){
        offs = calculate(array[i]);
        printf("%-17s %d \n",array[i] , offs);
    }

}






