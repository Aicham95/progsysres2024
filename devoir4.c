#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
 #include <semaphore.h>



int compteur= 0 , i=0 ;
sem_t semSecondaire , semTertiare;
int n = 10, m = 0;

void *ftheardsecondaire(void * arg){
	
	while(1){
		if(compteur < n){
			sem_wait(&semSecondaire);
			printf("%d  %10d \n",++i, compteur++ );
		}
		else{
			m = 10;n= -10;
			sem_post(&semTertiare) ; 
		}
	}
	pthread_exit(NULL);
	
}

void *ftheardtertiare(void * arg){
	//return NULL ;
	
	while(1){
		if(compteur > -(m)){
			sem_wait(&semTertiare);
			printf("%d  %10d \n",++i, compteur--);
		}
		else{
			n = 10; m=-10;
			sem_post(&semSecondaire);
		}
	}
	pthread_exit(NULL);
}

int main(int argc , char* argv[])
{
	pthread_t th1 , th2;
	int resultat ;

	//initialisation des semaphores

	resultat = sem_init(&semSecondaire, 0, n);
	if(resultat == -1){
		perror("Erreur d'initialisation de la semaphore");
		return 0 ;
	}

	resultat = sem_init(&semTertiare, 0, m);
	if(resultat == -1){
		perror("Erreur d'initialisation de la semaphore");
		return 0 ;
	}

	resultat = pthread_create(&th1 , NULL, ftheardsecondaire , (void *)NULL);
	if(resultat==-1){
		perror("Erreur de lancement du thread secondaire");
		return 0 ;
	}

	resultat = pthread_create(&th2 , NULL, ftheardtertiare , (void *)NULL);
	if(resultat==-1){
		perror("Erreur de lancement du thread tertiare");
		return 0 ;
	}
	
	// while(1)
		//printf("%d %10d %10d %10d\n",i++, compteurPrincipal++, compteurSecondaire,compteurTertiare);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
		

	return 0 ;
}