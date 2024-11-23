#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <semaphore.h>


int n ;
sem_t* semaphores;


void *thread_function(void * arg){
	int thread_id = *((int*)arg);
	
	while(1){
			sem_wait(&semaphores[thread_id]);
			printf("thread %d  s'execute\n", thread_id +1 );
			sem_post(&semaphores[(thread_id + 1) % n]) ;
			sleep(1); //pose pour rendre la sortie plus lisible::
	}
	pthread_exit(NULL);
	
}



int main(int argc , char* argv[])
{
	if(argc < 2){
		printf("Nombre d'arguments insuffisant .\n");
		printf("Usage :%s nomfichier <N> nombre de threads .\n",argv[0]);
		return 0 ;
	}
	n = atoi(argv[1]);
	semaphores = malloc(n*sizeof(sem_t));
	if(!semaphores){
		perror("Erreur d'allocation mémoire");
		return 0;
	}
	int thread_id[n]; 
	pthread_t threads[n];
	for(int i=0 ; i<n ; i++){
		sem_init(&semaphores[i],0,(i==0) ? 1 : 0); //initiale tous les semaphores::
	}

	//Creation des threads::

	for (int i = 0; i < n; ++i)
	{
		thread_id[i] = i ;
		if(pthread_create(&threads[i] , NULL , thread_function , &thread_id[i]) !=0){
			perror("Erreur lors de la creation du thread .\n");
			exit(1);
		}
	}

	//Attendre la fin des threads (ici il tourne enn boucle infinie)::

	for(int i=0 ; i < n ; i++)
		pthread_join(threads[i],NULL);

	//Destruction des semaphores::

	for(int i=0 ; i<n ;i++)
		sem_destroy(&semaphores[i]);
	free(semaphores);

	return 0 ;
}