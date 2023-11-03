#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*             2n
     N     <-------->
     [] -> [        ]   ^ 
     [] -> [        ]   | n
   i [] -> [   4    ]   |
     [] -> [        ]   V
               j
    N[n][n]
    float **N;
*/

/*
   1   0
     1 0
       1
       0
       0
*/

double **alloc_matrix(int height, int width) {
  double **X = malloc(sizeof(double *) * height);
  for (int i = 0; i < height; i++) {
    X[i] = malloc(sizeof(double) * width);
  }
  return X;
}

double **free_matrix(int height, int width, double **A) {
  for (int i = 0; i < height; i++) {
    free(A[i]);
  }
  free(A);
}

/*
procedure invert(M : n × n matrix)
  N ← n × n identity matrix
  for p ← 0, 1, · · · , n − 1 do
    f ← M[p][p]
    divide Mp by f
    divide Np by f
    for i ← p + 1, · · · , n − 1 do
      f ← Mi,p
      subtract Mp × f from Mi
      subtract Np × f from Ni
    end for
  end for
  for p ← n − 1, · · · , 0 do
    for i ← p − 1, · · · , 0 do
      f ← Mi,p
      subtract Mp × f from Mi
      subtract Np × f from Ni
    end for
  end for
  return N
end procedure

  */
double **invert(int n, double **M) {
  double f;
  double **N = alloc_matrix(n, n);

  // Make identy matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      N[i][j] = 0;
    }
  }
  for (int i = 0; i < n; i++) {
    N[i][i] = 1;
  }
  
  for (int p = 0; p < n; p++) {
    f = M[p][p];
    for (int j = 0; j < n; j++) {
      M[p][j] /= f;
    }
    for (int j = 0; j < n; j++) {
      N[p][j] /= f;
    }
    for (int i = p + 1; i < n; i++) {
      f = M[i][p];
      for (int j = 0; j < n; j++) {
        M[i][j] -= M[p][j] * f;
      }
      for (int j = 0; j < n; j++) {
        N[i][j] -= N[p][j] * f;
      }
    }
  }

  for (int p = n - 1; p >= 0; p--) {
    for (int i = p - 1; i >= 0; i--) {
      f = M[i][p];
      for (int j = 0; j < n; j++) {
        M[i][j] -= M[p][j] * f;
      }
      for (int j = 0; j < n; j++) {
        N[i][j] -= N[p][j] * f;
      }
    }
  }
  
  return N;
}

/* A_width == B_height */
double **multiply(int A_height, int A_width, int B_width,
    double **A, double **B) {

  double **X = alloc_matrix(A_height, B_width);
  for (int i = 0; i < A_height; i++) {
    for (int j = 0; j < B_width; j++) {
      double f = 0;
      for (int k = 0; k < A_width; k++) {
        f += A[i][k] * B[k][j];
      }
      X[i][j] = f;
    }
  }
  return X;
}

// m, t, X
double **transpose(int height, int width, double **A) {
  double **X = alloc_matrix(width /*t*/, height /*m*/);
  alloc_matrix(t, m);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      X[j][i] = A[i][j];
    }
  }
  return X;
}

/*
   estimate.c
       |
     make 
       V
   estimate

  */


void train() {
  
}

void estimate()

// estimate argument1 argument2
////
// argv = {"estimate" "train.txt" "data.txt"}
// argc = 3
// argv[1] -- first argument
int main(int argc, char *argv[]) {
    printf("You gave me %d ingredients!\n", argc);

    for(int i = 0; i < argc; i++)
    {
        printf("Ingredient %d: %s\n", i, argv[i]);
    }

    return 0;
 }

int main(void) {
  // Read input
  int k, m;
  char train_string[100];
  scanf("%s", train_string);
  if (strcmp(train_string, "train") != 0) {
    printf("Input must start with train\n");
    return 1;
  }
  scanf("%d%d", &k, &m);

  int t = k + 1;
  double **X = alloc_matrix(m, t);
  double **Y = alloc_matrix(m, 1);
  for (int i = 0; i < m; i++) {
    X[i][0] = 1;
    for (int j = 0; j < k; j++) {
      scanf("%lf", &X[i][j + 1]);
    }
    scanf("%lf", &Y[i][0]);
  }

  // Transpose X
  int n = m; // Swap the dimensions for transposing
  double **XT = transpose(m, t, X);
  free_matrix(, XT);
  //double **multiply(int A_height, int A_width, int B_width,
  //    double **A, double **B);
  // A_height = k,
  // A_width = m,
  // B_width = ,
  // A = ,
  // B =
  double **XTX = multiply(t, m, t, XT, X); 
  double **Inv = invert(t, XTX);
  double **S = multiply(t, t, m, Inv, XT);
  double **W = multiply(t, m, 1, S, Y);

  //X : m . k
  //XT : k . m
  //XTX = (XT * X) : k . k
  //Inv = XTX-1 : k . k
  //S = Inv * XT : k . m
  //W = S : k.m * Y : m.1

  // Rest of your code

  // Print result
  
  // Clean up allocated memory
  free_matrix(m, X);
  free_matrix(t, XT);
  free_matrix(Y);

  return 0;
}