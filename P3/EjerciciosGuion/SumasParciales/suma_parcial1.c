#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>  

int suma_total = 0;
//Declarar semaforo
sem_t sem_suma;

void * suma_parcial(void * arg) {
  int j = 0;
  int ni=((int*)arg)[0];
  int nf=((int*)arg)[1];
  for (j = ni; j <= nf; j++){
	  /* GARANTIZAR EXCLUSION MUTUA ENTRE SECCIONES CRITICAS */
	  //Cerrar semaforo
	  //   solicitar permiso para entrar en seccion critica (SENTENCIA BLOQUEANTE)
	  sem_wait(&sem_suma);
	  suma_total = suma_total + j;   /* SECCION CRITICA - se modificar un recurso compartido*/
	  //Abrir semaforo
	  //   indicar salida de seccion critica
	  sem_post(&sem_suma);
  }
  pthread_exit(0);
}

int main(void) {
  pthread_t th1, th2;
  sem_init(&sem_suma, 0, 1);
  
  int num1[2]={   0,  4999};
  int num2[2]={5000, 10000};

  /* se crean dos threads con atributos por defecto */
  pthread_create(&th1, NULL, suma_parcial, (void*)num1);
  pthread_create(&th2, NULL, suma_parcial, (void*)num2);

  printf("El thread principal continua ejecutando\n");

  /* se espera su terminacion */
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("La suma total es: %d y debería ser (50005000)\n", suma_total);
  
  sem_destroy(&sem_suma);
  
  return 0;
}
