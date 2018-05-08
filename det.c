#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct matrixandconst {
  int constant;
  int** matrix;
} matrixconst;

typedef struct det_struct {
  int matrixdim;
  int matrixnum;
  matrixconst* matrix;
} detstruct;

typedef struct pointer_struct {
  detstruct* next;
} pointerstruct;

int power (int base, int exp) {
  int a;
  int product = 1;
  for (a=0;a<exp;a++) {
    product = product * base;
  }

  return product;
}

int certainmatrixes (int dimension,int maxdimension) {
  int total = 1;
  int i = 0;
  for (i=dimension;i<=maxdimension;i++) {
    if (i==maxdimension) {
      total = 1*total;
      break;
    }
    else {
      total = total * (i+1);
    }
  }
  return total;
}

int totalmatrixes (int row) {
  int i = 0;
  int total = 0;
  int matrixnum[row];
  for (i=0;i<row;i++) {
    matrixnum[i] = 0;
  }
  for (i=row-1;i>0;i--) {
    if (i==row-1) {
      matrixnum[i] = 1;
    }
    else {
      matrixnum[i] = (i+2)*matrixnum[i+1];
    }
  }

  for (i=0;i<row;i++) {
    total = matrixnum[i] + total;
  }

  return total;
}

int total2x2 (int row) {
  int i = 0;
  int total = 1;
  for (i=3;i<=row;i++) {
    total = total * i;
  }

  return total;
}

double nextsquarenumber (double square) {//input of 9 gives output of 16
  double value;
  square = sqrt(square);
  value = pow(square+1,2);
  return value;
}

int calculationof2x2matrix (int matrix[]) {
  int total;
  total = matrix[0]*matrix[3] - matrix[1]*matrix[2];
  return total;
}

int main (void) {

  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int m = 0;
  int n = 0;
  int o = 0;
  int y = 0;

  int** determinant;
  determinant = malloc(sizeof(int*)*1);
  for (i=0;i<1;i++) {
    determinant[i] = malloc(sizeof(int)*1);
  }//initialize determinant to a two by two matrix

  bool stopentry = false;

  int carryonvalue = -1;

  char* entry;
  entry = malloc(sizeof(char));

  printf("Enter your matrix\n");
  j=1;
  while (!stopentry) {
    scanf("%c", &entry[j-1]);
    printf("\n");
    j++;

    if (entry[j-2]=='=') {
      entry = realloc(entry,sizeof(char)*(j-1));
      stopentry = true;
      break;
    }
    else {
      entry = realloc(entry,sizeof(char)*j);
    }

  }//promting infinite entry numbers until user enters "=" sign and amount of entries fits in a perfect square matrix (1,4,9,16...)
  entry[j-1] = '\0';
  int rows = sqrt(j-2);
  int cols = sqrt(j-2);
  int dimension = sqrt(j-2); //how big of a size of the square matrix

  determinant = realloc(determinant,sizeof(int*)*rows);
  for (j=0;j<rows;j++) {
    determinant[j] = realloc(determinant,sizeof(int)*cols);
  }

  for (i=0;i<rows;i++) {
    for (j=0, k=carryonvalue+1;j<cols && k<strlen(entry)-1;j++, k++) {
        determinant[i][j] = atoi(&entry[k])/power(10,strlen(entry)-2-k);
        carryonvalue = k;
      }
    }//transferring to determinant

  printf("your matrix is \n\n");
  for (i=0;i<dimension;i++) {
    for (j=0;j<dimension;j++) {
      printf("%d\t", determinant[i][j]);
      if (j==dimension-1) {
        printf("\n\n");
      }
    }
  }//printing my matrix

  int detcalc[cols];
  for (i=0;i<cols;i++) {
    detcalc[i] = determinant[0][i];//starting determinant calculation, calculating over the first row of numbers which is row=0,col=i (Aij * cofactor(Aij))
  }

  detstruct matrix[dimension];// my matrix struct]
  pointerstruct pointer[dimension];
  for (i=1;i<dimension;i++) {
    matrix[i].matrixdim = i+1;
    matrix[i].matrixnum = certainmatrixes(i+1,dimension);
  }
  for (i=0;i<dimension;i++) {
    matrix[i].matrix = malloc(sizeof(matrixconst)*matrix[i].matrixnum);
  }
  for (i=0;i<dimension;i++) {
    for (j=0;j<matrix[i].matrixnum;j++) {
    matrix[i].matrix[j].matrix = malloc(sizeof(int*)*matrix[i].matrixdim);
      for (y=0;y<matrix[i].matrixdim;y++) {
        matrix[i].matrix[j].matrix[y] = malloc(sizeof(int)*matrix[i].matrixdim);
      }
    }
  }


  for (j=0;j<dimension;j++) {
    for (k=0;k<dimension;k++) {
      matrix[dimension-1].matrix[0].matrix[j][k] = determinant[j][k];
    }
  }// transferring entry matrix values to the struct matrix of max max dimension
  for (i=dimension-1;i>0;i--) {
    pointer[i].next = &matrix[i-1];
  }
  carryonvalue = -1;
  for (i=dimension-2;i>0;i--) {
    for (m=0;m<matrix[i+1].matrixnum;m++) {
      for (l=carryonvalue+1;l<matrix[i+1].matrixdim;l++) {
        for (o=0;o<matrix[i].matrixdim;o++) {
          for (j=0;j<matrix[i].matrixdim;j++) {
            for (k=0;k<matrix[i].matrixdim;k++) {
              if (o==k){
                matrix[i].matrix[l].matrix[j][k] = matrix[i+1].matrix[m].matrix[j+1][k+1];
              }
              else {
                matrix[i].matrix[l].matrix[j][k] = matrix[i+1].matrix[m].matrix[j+1][k];
              }
              carryonvalue = l;
            }
          }
        }
      }
    }
  }

  matrix[dimension-1].matrix[0].constant = 1;
  carryonvalue = -1;
  for (i=2;i<dimension;i++) {
    for (k=0;k<matrix[dimension-i+1].matrixdim;k++) {
      for (j=carryonvalue+1, l=0;j<matrix[dimension-i].matrixnum && l<matrix[dimension-i+1].matrixdim;j++,l++) {
        matrix[dimension-i].matrix[j].constant = matrix[dimension-i+1].matrix[k].matrix[0][l] * matrix[dimension-i+1].matrix[k].constant;
        carryonvalue = j;
      }
    }
  }

  int twobytwomatrix[total2x2(dimension)][4];
  int twobytwodetvalue[total2x2(dimension)];
  carryonvalue = -1;
  for (i=0;i<total2x2(dimension);i++) {
    for (k=0;k<2;k++) {
      for (j=carryonvalue+1, l=0;j<4 && l<2;j++, l++) {
        twobytwomatrix[i][j] = matrix[1].matrix[i].matrix[k][l];
        carryonvalue = j;
      }
    }
  }
  for (i=0;i<total2x2(dimension);i++) {
    twobytwodetvalue[i] = calculationof2x2matrix(twobytwomatrix[i]);
    twobytwodetvalue[i] = matrix[1].matrix[i].constant * twobytwodetvalue[i];
  }

  int total;
  for (i=0;i<total2x2(dimension);i++) {
    total = twobytwodetvalue[i] + total;
  }

  free(determinant);
  for (i=0;i<dimension;i++) {
    for (j=0;j<matrix[i].matrixnum;j++) {
      free(matrix[i].matrix[j].matrix);
    }
    free(matrix[i].matrix);
  }

  printf("Answer is \n%d", total);

  return 0;
}
