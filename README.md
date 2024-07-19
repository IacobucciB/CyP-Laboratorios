# CyP-Laboratorios
Laboratorio de Concurrencia y Paralelismo con Lenguaje C

Los ejercicios del Laboratorio se dividen en dos tematicas: Memoria Compartida y Pasaje de Mensajes.
Para compilar y correr los diferentes programas es necesario tener en cuenta los siguientes comandos:


## Memoria Compartida

- OPENMP :
```
gcc -fopenmp -o salidaEjecutable archivoFuente
```
- PThreads :
```
gcc -pthread -o salidaEjecutable archivoFuente
```
## Pasaje de Mensajes

- OpenMPI
```
mpicc -o salidaEjecutable archivoFuente
mpirun -np cantidadDeProcesos ejecutable
```