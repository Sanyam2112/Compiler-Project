// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include "lexer.h"
#include "getgrammar.h"

int isNT = 0;
int bufferSize = -1;
int arraySize = 50;

void showfirstfollow (unit *head){
  unit *ptr = head;
  char* str = head->term;
  printf(" of %s -> ",ptr -> term);
  ptr = ptr -> next;
  while(ptr -> next){
      printf(" %s %u",ptr -> term,ptr->terminal);
      ptr = ptr -> next;
      str = ptr -> term;
  }
  printf(" %s %u;\n\n",ptr -> term,ptr->terminal);
}

void showfollow(){
  char* prevterm="";
  printf("List of Follow Set: \n\n");
  for(int i = 0; i<arraySize; i++){
    printf("Follow ");
    showfirstfollow(followarray[i]);
    prevterm = followarray[i]->term;
  }
}

void showgrammar(){
  printf("Grammar: \n\n");
  for(int i = 0; i<arraySize; i++){
    printf("Definition ");
    showfirstfollow(grammararray[i]);
  }
}

void showfirst(){
  char* prevterm="";
  printf("List of First Set: \n\n");
  for(int i = 0; i<arraySize; i++){
    if(strcmp(prevterm,firstarray[i]->term)==0){
      continue;
    }
    printf("First ");
    showfirstfollow(firstarray[i]);
    prevterm = firstarray[i]->term;
  }
}

void showlist (unit *head, int index){
  printf("showlist of %s",head->term);
    unit *ptr = head;
    while(ptr -> next){
        printf("term:%s\nterminal: %u \ncount: %u\n",ptr -> term, ptr -> terminal,countarray[index]);
        ptr = ptr -> next;
    }
    printf("term:%s\nterminal: %u \ncount: %u\n",ptr -> term, ptr -> terminal,countarray[index]);
}

char getnextcharacter(FILE *fp){
  if(bufferSize == -1 || bufferPosition == bufferSize){// first call to getCharacter or end of buffer has been reached
      bufferSize = fread(buffer, sizeof(char), (size_t)MAX_BUFFER_SIZE, fp);
      bufferPosition = 1;
      if(bufferSize == 0)
          return 26; // eof
      else
          return buffer[0];
  }
  if(bufferSize == 0) // eof has been reached
      return 26;
  else
      return buffer[bufferPosition++];
}

void addunit(unit *head, char* value1, int is){
  if(head -> term == NULL){
      head -> term = value1;
      head-> terminal = is;
      return;
  }
  unit *new = calloc(1,sizeof(unit));
  unit *ptr = head;
  new -> term = value1;
  new -> terminal = is;
  new -> next = NULL;
  while (ptr -> next){
    ptr = ptr -> next;
  }
  ptr -> next = new;
  return;
}

char* getnextterm(FILE *fp){
  char str[100];
  int count = 0;
  while(1){
    char nextChar = getnextcharacter(fp);
    isNT = 0;
    switch(nextChar){
      case '-':
      case '>':
      case '<':
      isNT = 1;
      case ' ':
      if (count){
        str[count] = '\0';
        char *ret = (char *)calloc(count+2,sizeof(char));
        int i = 0;
        while(i < count+1){
          ret[i] = str[i];
          i++;
        }
        ret[count+1] = '\0';
        return ret ;
      }
      break;

      case '\n':
      if (count){
        str[count] = '\0';
        char *ret = (char *)calloc(count+2,sizeof(char));
        int i = 0;
        while(i < count + 1){
          ret[i] = str[i];
          i++;
        }
        ret[count + 1] = '\0';
        return ret ;
      }
      case 26:
      return NULL;

      default:
      str[count] = nextChar;
      count++;
    }
  }
}

void getnextrule(FILE *fp, unit* head,int index){
  char next;
  int counter = 0;
	do{
    char *nextterm = getnextterm(fp);
    if (nextterm != NULL){
      addunit(head, nextterm, isNT);
      counter++;
    }
    bufferPosition--;
    next = getnextcharacter(fp);
	} while( next != '\n' && next != 26);
  countarray[index] = counter;
}

unit** initializearray(unit** array){
  array = (unit **)calloc(arraySize,sizeof(unit));
  for(int i = 0; i < arraySize; i++){
    array[i] = calloc(1,sizeof(unit));
  }
  return array;
}

unit** resizearray(unit** array){
  arraySize = arraySize + 10;
  array = (unit**)realloc(array, arraySize*sizeof(unit));
  countarray = (int*)realloc(countarray, arraySize*sizeof(int));
  for(int i = arraySize - 10; i < arraySize; i++){
    array[i] = calloc(1, sizeof(unit));
  }
  return array;
}

void getgrammar(){
	  FILE* fp = fopen("grammar.txt", "r");
    countarray = (int*)calloc(1, arraySize*sizeof(int));
    grammararray=initializearray(grammararray);
    char next;
    int index = 0;
    do {
      if(index == arraySize){
        grammararray=resizearray(grammararray);
      }
      getnextrule(fp, grammararray[index], index);
      next = getnextcharacter(fp);
      //showlist(grammararray[index]);
      index++;
  	} while( next != 26 );
    int i = 0;
    while(grammararray[i]->term != NULL){
      i++;
    }
    arraySize = i;
}

void addtoarray(unit* head, unit* nextunit){
  unit *ptr = head;
  if(ptr -> term == NULL){
    ptr -> term = nextunit -> term;
    ptr -> terminal = nextunit->terminal;
    ptr -> next = NULL;
    return;
  }
  do{
    if(strcmp(ptr -> term, nextunit->term) == 0)
    return;

    if(ptr->next == NULL){
      break;
    }
    ptr = ptr -> next;

    if(strcmp(ptr -> term, nextunit->term) == 0)
    return;
  }while(ptr -> next);

  unit *new = calloc(1,sizeof(unit));
  new -> term = nextunit->term;
  new -> terminal = nextunit->terminal;
  new -> next = NULL;
  ptr -> next = new;
}

void mergelist(unit* list1,unit* list2){//list1 added to list2
    if(list1 == NULL){
      return;
    }
    if(list1->term == NULL){
      return;
    }
    unit* str = list1;
    do{
      addtoarray(list2,str);
      if(str->next ==NULL){
        break;
      }
      str = str->next;
    }while(str->term != NULL);
}

int canbeEpsilon(unit* ptr){
  if (strcmp("eps",ptr->term) == 0){
    return 1;
  }
  if(ptr->terminal == 0){
    return 0;
  }
  unit* new;//= calloc(1,sizeof(unit));
  for(int i=0;i<arraySize;i++){
      if(strcmp(grammararray[i] -> term,ptr->term) == 0){
      int counter = countarray[i] -1;
      new = grammararray[i]->next;
      int j;
      for(j=0;j<counter;j++){
        if(!canbeEpsilon(new))
        break;
        new = new->next;
      }
      if(counter == j){
        return 1;
      }
    }
  }
  return 0;
}

void first(unit* input, unit* new){
  if(strcmp(input->term,"eps") == 0){
    new->term = "eps";
    new->terminal = 0;
    return;
  }else if(input->terminal == 0){
    new->term = input->term;
    new->terminal = input->terminal;
    return;
  }else{
    for(int j = 0; j < arraySize; j++){
      if(strcmp(grammararray[j] -> term,input -> term) == 0){
        unit* new2 = grammararray[j] -> next;
        int counter = countarray[j] -1;
        for(int i=0;i<counter-1;i++){
          if(!canbeEpsilon(new2))
          break;
          unit * temp = calloc(1,sizeof(unit));
          first(new2,temp);
          mergelist(temp,new);
          free(temp);
          new2 = new2->next;if(new2==NULL){break;}
        }
        unit * temp = calloc(1,sizeof(unit));
        first(new2,temp);
        mergelist(temp,new);
        free(temp);        }
      }
    }
    return;
  }

void follow(unit* input, unit* new1){
  if(strcmp("program",input -> term) == 0){
    unit * temp = calloc(1,sizeof(unit));
    temp->term = "$";
    temp->terminal = 0;
    mergelist(temp,new1);
    free(temp);
    return;
  }
  for(int j = 0; j < arraySize; j++){
    unit* new2 = grammararray[j] -> next;
    int counter = countarray[j] -1;
      for(int i=0;i<counter;i++){
        if(strcmp(new2 -> term,input -> term) == 0){//found it
          unit* new=new2;
          if(new->next == NULL){
            if(strcmp(input -> term,grammararray[j]->term) != 0){
              follow(grammararray[j],new1);
            }//otherwise let it go
          }else{
            new = new->next;
            if(strcmp(input -> term,new -> term) != 0){
              unit * temp = calloc(1,sizeof(unit));
              first(new,temp);
              mergelist(temp,new1);
              free(temp);
              while(canbeEpsilon(new)){
                if(new->next==NULL){
                  if(strcmp(input -> term,grammararray[j]->term) != 0){
                    follow(grammararray[j],new1);
                  }
                  break;
                }
                else{
                  unit * temp = calloc(1,sizeof(unit));
                  first(new->next,temp);
                  mergelist(temp,new1);
                  free(temp);
                  new = new->next;
                }
              }
            }
          }
        }
        new2 = new2->next;
      }
  }
  return;
}

void createfirst(){
  firstarray = initializearray(firstarray);
  for(int j = 0; j < arraySize; j++){
    firstarray[j] -> term = grammararray[j] -> term;
    firstarray[j] -> terminal = grammararray[j] -> terminal;
    firstarray[j] -> next = NULL;
  }
  for(int i = 0; i<arraySize; i++){
    unit* new1= calloc(1,sizeof(unit));
    first(grammararray[i], new1);
    mergelist(new1,firstarray[i]);
    free(new1);
    //showfirst(firstarray[i]);
    //printf("------------------------\n");
  }
}

void createfollow(){
  followarray = initializearray(followarray);
  for(int j = 0; j < arraySize; j++){
    followarray[j] -> term = grammararray[j] -> term;
    followarray[j] -> terminal = grammararray[j] -> terminal;
    followarray[j] -> next = NULL;
  }
  int i;
  for(i = 0; i<arraySize; i++){
    unit* new1= calloc(1,sizeof(unit));
    follow(grammararray[i], new1);
    mergelist(new1,followarray[i]);
    free(new1);
    //showfollow(followarray[i]);
    //printf("------------------------\n");
  }
}

