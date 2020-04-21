// GROUP NO 36
// 2017A7PS0009 RITIK KANDORIA
// 2017A7PS0014 SANYAM JAIN
// 2017A7PS0155 DESHMUKH ADVAIT MAHESH
//-------------------------------------------------------------------------------------------------------------------------------------------

#include "lexer.h"

char *strcpy(char *destination, char *source)
{
    char *start = destination;

    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0'; // add '\0' at the end
    return start;
}

int strcmp(const char *X, const char *Y){
  while (*X) {
    if (*X != *Y)
    break;
    X++;
    Y++;
  }

	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

void addnode (node *head, char* value1, char *value2) {
    node *new = malloc(sizeof(node)), *ptr = head;
    new -> keyword = value1;
    new -> token = value2;

    new -> next = NULL;
    while (ptr -> next) ptr = ptr -> next;
    ptr -> next = new;
}

char* searchInHASH(char *str){
  int index = (int) str[0];
  if (index > 96){
    index = index - 97;
  }
  else if (index == 65){
          index = 0;
  }
  else if (index == 79){
    index = 14;
  }
  else return NULL;

  node *ptr = HASH[index];
  if(ptr -> keyword == NULL){
     return NULL;
  }

  while (ptr -> next) {
    if(strcmp(ptr -> keyword, str) == 0){
      return ptr -> token;
    }
    ptr = ptr -> next;
  }

  if(strcmp(ptr -> keyword, str) == 0){
    return ptr -> token;
  }
  else{
    return NULL;
  }

}

void addKeyToken(char *keyword,char* token){
  int index = (int) keyword[0];

  if (index > 96){
    index = index - 97;
  }
  else if (index == 65){
    index = 0;
  }
  else if (index == 79){
    index = 14;
  }else return;

  node *ptr = HASH[index];

  if(ptr -> keyword == NULL){
    HASH[index] -> keyword = keyword;
    HASH[index] -> token = token;
  }
  else{
    addnode(HASH[index], keyword, token);
  }
}

void createHASH(){
  for(int i = 0; i < 26; i++){
    HASH[i] = malloc(sizeof(node));
  }
  addKeyToken("AND", "AND");
  addKeyToken("array", "ARRAY");
  addKeyToken("break", "BREAK");
  addKeyToken("boolean", "BOOLEAN");
  addKeyToken("case", "CASE");
  addKeyToken("declare", "DECLARE");
  addKeyToken("default", "DEFAULT");
  addKeyToken("driver", "DRIVER");
  addKeyToken("end", "END");
  addKeyToken("false", "FALSE");
  addKeyToken("for", "FOR");
  addKeyToken("get_value", "GET_VALUE");
  addKeyToken("input", "INPUT");
  addKeyToken("integer", "INTEGER");
  addKeyToken("in", "IN");
  addKeyToken("module", "MODULE");
  addKeyToken("OR", "OR");
  addKeyToken("of", "OF");
  addKeyToken("parameters", "PARAMETERS");
  addKeyToken("program", "PROGRAM");
  addKeyToken("print", "PRINT");
  addKeyToken("real", "REAL");
  addKeyToken("returns", "RETURNS");
  addKeyToken("start","START");
  addKeyToken("switch", "SWITCH");
  addKeyToken("true", "TRUE");
  addKeyToken("takes", "TAKES");
  addKeyToken("use","USE");
  addKeyToken("with","WITH");
  addKeyToken("while", "WHILE");
}

char getCharacter(FILE *fp) {

	if(bufferSize1 == -1 || bufferPosition1 == bufferSize1) {
        // first call to getCharacter or end of buffer has been reached
        bufferSize1 = fread(buffer1, sizeof(char), (size_t)MAX_BUFFER_SIZE, fp);
				//printf("\n buffer size=%lu\n",(size_t)MAX_BUFFER_SIZE);
        bufferPosition1 = 1;
        if(bufferSize1 == 0)
            return 26; // eof
        else
            return buffer1[0];
    }

    if(bufferSize1 == 0) // eof has been reached
        return 26;
    else
        return buffer1[bufferPosition1++];
}

tokenInfo* getnexttoken(FILE *fp,tokenInfo* temp){
    int state = 0;
    int idcount = 0;
    char nextChar;
    unsigned count = 0;
		for(int c=0;c<100;c++){buffer2[c]='\0';}

	while(1){
		nextChar = getCharacter(fp);
		buffer2[count++] = nextChar;
		temp -> lineNum = line_num;
		switch(state){
			case 0:
			switch (nextChar){
				case ' ':
				case '\t':
				case '\r':
				count=0;
				break;

				case ';':
				temp -> tokenName = "SEMICOL";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ':':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "ASSIGNOP";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					bufferPosition1--;//retracting

					temp -> tokenName = "COLON";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case ',':
				temp -> tokenName = "COMMA";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '[':
				temp -> tokenName = "SQBO";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ']':
				temp -> tokenName = "SQBC";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '(':
				temp -> tokenName = "BO";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ')':
				temp -> tokenName = "BC";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '+':
				temp -> tokenName = "PLUS";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '-':
				temp -> tokenName = "MINUS";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '/':
				temp -> tokenName = "DIV";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '*':
				nextChar = getCharacter(fp);
				int commentline = line_num;
				buffer2[count++] = nextChar;
				if (nextChar == '*'){
					int starCount = 0;
					buffer2[count-1]='\0';
					buffer2[count-2]='\0';
					int i = 1;
					while(i){
						//printf("stuck %c %s\n",nextChar,temp -> lexeme);
						nextChar = getCharacter(fp);
						switch (nextChar){
							case '*':
							starCount++;
							if (starCount == 2){
								//temp -> lineNum = line_num; // yaha kuch changes karna hai.......
								i = 0;
							}
							count = 0;
							break;

							case '\n':
							line_num++;
							starCount = 0;
							break;

							default:
							if (nextChar == 26){
								printf("Comment starting on line %u not finished.\n",commentline);
								i=0;
							}
							starCount = 0;
							break;
						}
					}
				}
				else{
					bufferPosition1--;
					temp -> tokenName = "MUL";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '=':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "EQ";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					bufferPosition1--;
					state=11;
				}
				break;

				case '!':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "NE";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					state=11;
					bufferPosition1--;
				}
				break;

				case '.':
				nextChar = getCharacter(fp);
				if (nextChar == '.'){
					buffer2[count++] = nextChar;
					temp -> tokenName = "RANGEOP";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}else{
					bufferPosition1--;
					state=11;
				}
				break;


				case '<':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					buffer2[count++] = nextChar;
					temp -> tokenName = "LE";
					strcpy(temp->lexeme,buffer2);
					return temp;

					case '<':
					buffer2[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '<'){
						buffer2[count++] = nextChar;
						temp -> tokenName = "DRIVERDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}
					else{
						bufferPosition1--;
						temp -> tokenName = "DEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}

					default:
					bufferPosition1--;
					temp -> tokenName = "LT";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '>':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					buffer2[count++] = nextChar;
					temp -> tokenName = "GE";
					strcpy(temp->lexeme,buffer2);
					return temp;

					case '>':
					buffer2[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '>'){
						buffer2[count++] = nextChar;
						temp -> tokenName = "DRIVERENDDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}
					else{
						bufferPosition1--;
						temp -> tokenName = "ENDDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}

					default:
					bufferPosition1--;
					temp -> tokenName = "GT";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '\n':
				line_num++;
				count--;
				temp -> lineNum = line_num;
				break;

				case '0'...'9':
				state = 5;
				break;

				case 'a'...'z':
				case 'A'...'Z':
				state = 1;
				break;

				default:
				if(nextChar != 26){
					printf("Character not allowed: %c\n",nextChar);
					count--;
				}
				break;
			}
			break;

			case 5:
				switch(nextChar){
					case '0'...'9':
					state = 5;
					break;

					case '.':
					state = 6;
					break;

					default:
					bufferPosition1--;
					temp -> tokenName = "NUM";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
			break;

			case 6:
			switch(nextChar){
				case '0'...'9':
				state = 7;
				break;

				case '.':
				bufferPosition1--;
				bufferPosition1--;
				temp -> tokenName = "NUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;

			  default:
				printf("stray '.' on line: %u\n",line_num);
				bufferPosition1--;
				temp -> tokenName = "NUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;

			}
			break;

			case 7:
			switch(nextChar){
				case '0'...'9':
					state = 7;
			  	break;

				case 'E':
				case 'e':
					state = 8;
				break;

				default:
					bufferPosition1--;
					temp->tokenName = "RNUM";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 8:
			switch(nextChar){
				case '+':
				case '-':
					state = 9;
				break;

				case '0'...'9':
					state = 10;
				break;

				default:
				bufferPosition1--;
				bufferPosition1--;
				temp -> tokenName = "RNUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			break;

			case 9:
			switch(nextChar){
				case '0'...'9':
					state = 10;
				break;
			}
			break;

			case 10:
			switch(nextChar){
				case '0'...'9':
					state = 10;
				break;

				default:
					bufferPosition1--;
					buffer2[count-1] = '\0';
					temp->tokenName ="RNUM";
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 11:
			printf("Lexical Error on line: %u lexeme:'%s'\n",line_num,buffer2);
			count=0;
			state=0;
			break;

			case 1:
			switch(nextChar){
				case 'a'...'z':
				case 'A'...'Z':
				case '0'...'9':
				case '_':
				state = 2;
				break;

				default:
				//printf("yaha");
					bufferPosition1--;
					temp -> tokenName = "ID";
					buffer2[count-1] = '\0';
					char* token = searchInHASH(buffer2);
					if(token != NULL){
						temp -> tokenName = token;
					}
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 2:
			if(idcount==18){
				temp->tokenName = "ID";
				bufferPosition1--;
				idcount =0;
				buffer2[count-1] = '\0';
				char* token = searchInHASH(buffer2);
				if(token != NULL){
					temp -> tokenName = token;
				}
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			switch(nextChar){
				case 'a'...'z':
				case 'A'...'Z':
				case '0'...'9':
				case '_':
				idcount++;
				state = 2;
				break;

				default:
				bufferPosition1--;
				temp -> tokenName = "ID";
				buffer2[count-1] = '\0';
				char* token = searchInHASH(buffer2);
				if(token != NULL){
					temp -> tokenName = token;
				}
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			break;
		}
		if (nextChar==26){
			buffer2[0] = (char)(26);
			temp -> tokenName = "EOF";
			temp -> lineNum = line_num;
			strcpy(temp->lexeme,buffer2);
			return temp;
		}
	}
}

void commentremove(FILE *fp){
  int starcount = 0;
  char nextChar;
  int state = 0;
  while(1){
		nextChar = getCharacter(fp);
    switch (state){
      case 0:
      switch(nextChar){
        case '*':
        state = 1;
        break;

        case 26:
        return;

        default:
        state = 0;
        printf("%c",nextChar);
        break;
      }
      break;

      case 1:
      switch(nextChar){
        case '*':
        state = 2;
        break;

        case 26:
        printf("*");
        return;

        default:
        printf("*%c",nextChar);
        state = 0;
        break;
      }
      break;

      case 2:
      switch(nextChar){
        case '*':
        state = 3;
        break;

        case 26:
        return;

        default:
        if (nextChar=='\n'){
          printf("%c",nextChar);
        }
        state = 2;
        break;
      }
      break;

      case 3:
      switch(nextChar){
        case '*':
        state = 0;
        break;

        case 26:
        return;

        default:
        state = 2;
        break;
      }
      break;
    }

  }
}

void printToken(tokenInfo* t) {
    printf("%u %s lexeme: %s\n", t -> lineNum, t -> tokenName, t->lexeme);
}
