#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

/*
 * @param N La longitud del Vector
 */

int main(int argc, char *argv[])
{

  // Comprobar Error de Parametros
  if (argc != 2)
  {
    printf("Error: No se proporciono la longitud del Vector \n");
    return 1;
  }
  int N = atoi(argv[1]);
  if (N <= 0)
  {
    printf("Error: La longitud del Vector debe ser un Numero Entero Positivo \n");
    return 1;
  }

  int *numeros = (int *)malloc(N * sizeof(int));
  if (numeros == NULL)
  {
    printf("Error: Fallo en la Asignacion de Memoria \n");
    return 1;
  }

  // Asignar Valores Arbitrarios al Vector en el rango [1..30]
  for (int i = 0; i < N; i++)
  {
    numeros[i] = (rand() % 30) + 1;
  }

  // Ejecutar bucle en paralelo
#pragma omp parallel default(private) shared(numeros, N)
  {
#pragma omp for
    for (int i = 0; i < N; i++)
    {
      printf("Thread %d, Pos: %d, Sleep: %d \n", omp_get_thread_num(), i, numeros[i]);
      sleep(numeros[i]);
    }
  }

  free(numeros);
  return 0;
}
