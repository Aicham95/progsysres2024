#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>


int main(int argc , char *argv[]){

	if(argc < 2){
              printf("Erreur : nombre d'arguments insuffisant\n");
              printf("Usage : %s adresse_IP \n",argv[0]);
              return 0 ;
       }

    int socketServer;
    struct sockaddr_in addrServer ;
    int i = 0;
	// Parcours de 0 à 3000
    for (int port = 0; port <= 3000; port++) {
        // Création du socket
        socketServer = socket(AF_INET , SOCK_STREAM , 0);
		if(socketServer == -1){
			perror("Erreur de la creation de la socket TCP\n");
			return 0 ;
		}

		//2. Initialiation de la structure d'adresse::
		

		memset(&addrServer, 0 , sizeof(struct sockaddr_in));

       addrServer.sin_family = AF_INET; // Toujours::
       addrServer.sin_port   = htons(port);
       addrServer.sin_addr.s_addr = inet_addr(argv[1]);
    
    	int resultat = connect(socketServer, (struct sockaddr *) &addrServer,sizeof(struct sockaddr_in));
    	if(resultat == -1)
    	{
        	// Si la connexion échoue, on passe au port suivant
        	close(socketServer);
        	continue;
    	}

    	// affichage de port active

    	printf("Port  : %d --> ouvert",port);
    	close(socketServer);
    }
    return 0;
}
