/*
*------------------------------------------
* pthread_hello.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

* CC3086 - Programacion de Microprocesadores
*
*------------------------------------------
* Descripción: demostracion de operaciones 
* básicas para creación de hilos posix
*------------------------------------------
*/
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
using namespace std;

#define NTHREADS 10

/* -----------------------------------------------------------
** Subrutina usada por el pthread, luego de crearse.
** Se debe declarar con punteros, debido a que los threads
** emplean referencias de memoria.  La información pasa por 
** referencia indirecta
* ---------------------------------------------------------*/
void *say_hello(void *threadNumber) {
  long tID;
  tID = (long)threadNumber;
  cout << "Sqrt de: " << tID << ", es: " << sqrt(tID)<< endl;
  pthread_exit(NULL);
}
/* -----------------------------------------------------------
** Programa principal
* ---------------------------------------------------------*/
int main() {
  int rc;
  long j;
  int i;
  // Declarar una variable tipo pthread_t
  pthread_t tid[NTHREADS];

  for (i=0; i<NTHREADS; i++) {
    j = (long)i;
	/* -----------------------------------------------------------
	** Al crear un hilo, se pasan los  siguientes parametros:	
	** el valor del ID, el valor del atributo , la subrutina a
	** ejecutar por el hilo y el puntero para el parametro de 
	** la subrutina:
	**
	** pthread_create(&id,NULL,subrutine,(void *)parameter
	* ---------------------------------------------------------*/
	  rc = pthread_create(&tid[i], NULL, say_hello, (void *)i);
	
    if (rc) {              
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
   
  }
  
  for (j=0; j<NTHREADS; j++) {
       // Esperar a que cada thread termine en orden
    rc = pthread_join(tid[j], NULL);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
      
  }
  printf("Main: program completed. Exiting.\n");
  pthread_exit(NULL);

}