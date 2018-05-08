#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>



int main (void) {

  char* eqn;
  eqn = malloc(sizeof(char));
  int i = 1;

  while(1) {
    if (eqn[i-1]=='=') {
      break;
    }
    scanf("%c", &eqn[i]);
    i++;
    eqn=realloc(eqn,sizeof(char)*i);
  }
  int eqnsize = strlen(eqn);
  eqn[eqnsize-1] = '\0';

  int numarray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    numarray[i] = 0;
  }
  for (i=0;i<eqnsize;i++) {
    if (i==0 && isdigit(eqn[i])==1) {
      numarray[i] = atoi(&eqn[i]);
    }
    else if (isdigit(eqn[i])==1 && isdigit(eqn[i-1])!=1) {
      numarray[i] = atoi(&eqn[i]);
    }
  }

  int addarray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    addarray[i] = 0;
    if (eqn[i]=='+') {
      addarray[i] = 1;
    }
  }

  int subtractarray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    subtractarray[i] = 0;
    if (eqn[i]=='-') {
      subtractarray[i] = 1;
    }
  }

  int multiplyarray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    multiplyarray[i] = 0;
    if (eqn[i]=='*') {
      multiplyarray[i] = 1;
    }
  }

  int dividearray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    dividearray[i] = 0;
    if (eqn[i]=='/') {
      dividearray[i] = 1;
    }
  }

  char signarray[eqnsize];
  for (i=0;i<eqnsize;i++) {
    signarray[i] = ' ';
    if (eqn[i]=='+') {
      signarray[i] = '+';
    }
    else if (eqn[i]=='-') {
      signarray[i] = '-';
    }
    else if(eqn[i]=='*') {
      signarray[i] = '*';
    }
    else if(eqn[i]=='/') {
      signarray[i] = '/';
    }
  }
  int j;
  for (i=0;i<eqnsize;i++) {
    if (signarray[i]=='-') {
      if (numarray[i+1]!=0) {
        numarray[i+1] = numarray[i+1]*(-1);
      }
    }
  }

  for (i=0;i<eqnsize;i++) {
    if (signarray[i]=='*') {
      for (j=i;j>=0;j--) {
        if (numarray[j]!=0 && numarray[i+1]!=0) {
          numarray[i+1] = numarray[i+1]*numarray[j];
          break;
        }
      }
    }
    if (signarray[i]=='/') {
      for (j=i;j>=0;j--) {
        if (numarray[j]!=0 && numarray[i+1]!=0) {
          numarray[i+1] = numarray[i+1]/numarray[j];
          break;
        }
      }
    }
  }

  int answer = 0;
  for (i=0;i<eqnsize;i++) {
    answer = numarray[i] + answer;
  }

  printf("Final answer is: %d", answer);

  return 0;
}
