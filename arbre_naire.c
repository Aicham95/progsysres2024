#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	if(argc < 3){
		printf("Nombre d'argument sur la ligne de commande inuffisant\n");
        printf("Usage : %s <n> <k>\n",argv[0]);
        return 0;
	}
	int n = atoi(argv[1]), k=atoi(argv[2]);
	int nb_fils, profondeur = 0;
	pid_t pid_fils;
	for (nb_fils = 0; nb_fils < n;)
	{
		pid_fils = fork();
		switch(pid_fils){
		case -1:
			perror("Erreur de fork");
			break;
		case 0:
			printf("%d->%d ;\n",getppid(),getpid() );
			profondeur++;
			if(profondeur >= k)
				return 0;
			nb_fils = 0;
			break;
		default :
			wait(NULL);++nb_fils;
			if(nb_fils >= n)
				return 0;
		}
	}
	return 0;
}