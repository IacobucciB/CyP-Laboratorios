#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void llenar_matriz(int **m, int N);
void imprimir_matriz(int **m, int N);

int main(int argc, char *argv[])
{
  // Comprobar Error de Parametros
  if (argc != 3) {
    printf("Error: No se proporciono la dimension de la Matriz y el numero de Threads \n");
    return 1;
  }
  int N = atoi(argv[1]);
  int T = atoi(argv[2]);
  if (N <= 0 || T <= 0) {
    printf("Error: La dimension de la Matriz y el numero de Threads deben ser un Numero Entero Positivo \n");
    return 1;
  }

  // Asignar el Numero de Threads
  omp_set_num_threads(T);

  // Asignar Memoria para las Matrices
  int **a = (int **)malloc(N * sizeof(int *));
  int **b = (int **)malloc(N * sizeof(int *));
  int **c = (int **)malloc(N * sizeof(int *));
  if (a == NULL || b == NULL || c == NULL) {
    printf("Error: Fallo en la Asignacion de Memoria \n");
    return 1;
  }
  for (int i = 0; i < N; i++) {
    a[i] = (int *)malloc(N * sizeof(int));
    b[i] = (int *)malloc(N * sizeof(int));
    c[i] = (int *)malloc(N * sizeof(int));
    if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
      printf("Error: Fallo en la Asignacion de Memoria \n");
      return 1;
    }
  }

  // Asignar Valores Arbitrarios a la matriz
  llenar_matriz(a, N);
  llenar_matriz(b, N);

  printf("Matriz A : \n");
  imprimir_matriz(a, N);
  printf("Matriz B : \n");
  imprimir_matriz(b, N);

  // Ejecutar bucle en paralelo
#pragma omp parallel default(none) shared(a, b, c, N)
  {
#pragma omp for
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	c[i][j] = 0;
	for (int k = 0; k < N; k++) {
	  c[i][j] += a[i][k] * b[k][j];
	}
      }
    }
  }

  printf("Matriz C (Resultado de A x B): \n");
  imprimir_matriz(c, N);

  // Liberar memoria
  for (int i = 0; i < N; i++) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }
  free(a);
  free(b);
  free(c);

  return 0;
}

void llenar_matriz(int **m, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m[i][j] = (rand() % 5) + 1;
    }
  }
}

void imprimir_matriz(int **m, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}
