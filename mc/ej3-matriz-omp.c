#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cont = 0;
pthread_mutex_t mutex;

void *func()
{
    pthread_mutex_lock(&mutex);
    cont = cont + 1;
    printf("Contador : %d \n", cont);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
    printf("Ejercicio 3 - Libreria Pthreads \n");

    pthread_t hilo1;
    pthread_t hilo2;

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&hilo1, NULL, &func, NULL) != 0)
    {
        perror("ERROR: No se pudo crear el hilo 1");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&hilo2, NULL, &func, NULL) != 0)
    {
        perror("ERROR: No se pudo crear el hilo 2");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}
