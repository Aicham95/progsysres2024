#include "common.h"

int main(int argc , char *argv[]){

	if(argc < 2){
              printf("Erreur : nombre d'arguments insuffisant\n");
              printf("Usage : %s adresse_IP_PORT \n",argv[0]);
              return 0 ;
       }


	// 1.Creation de socket TCP::
	int socketServerTCP = socket(AF_INET , SOCK_STREAM , 0);
	if(socketServerTCP == -1){
		perror("Erreur de la creation de la socket TCP\n");
		return 0 ;
	}
	printf("Creation de la socket TCP avec succès\n");

	//2. Initialiation de la structure d'adresse::
	struct sockaddr_in addrServer ;

	memset(&addrServer, 0 , sizeof(struct sockaddr_in));

       addrServer.sin_family = AF_INET; // Toujours::
       addrServer.sin_port   = htons(atoi(argv[1]));
       addrServer.sin_addr.s_addr = inet_addr("0.0.0.0"); // addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");

       //3 Appel de bind::

       int resultat = bind(socketServerTCP , (struct sockaddr *) &addrServer , sizeof(struct sockaddr_in));

       if(resultat == -1){
       	perror("Erreur de lancement de bind::\n");
       	return 0 ;
       }

       printf("Execution de bind avec succès:\n");

       resultat = listen(socketServerTCP,5);
       if(resultat == -1){
       	perror("Erreur de lancement de listen::\n");
       	return 0 ;
       }

       printf("Execution de listen avec succès:\n");

       // Accept
       		// Declarer la structure qui va contenir l'addresse distante::
       struct sockaddr_in addrClient ;
       int taille = sizeof(struct sockaddr_in) ;

       //Compteur

       int compteur = 0;
       int i=0;

       int socketClientTCP = accept(socketServerTCP, (struct sockaddr *) &addrClient , &taille);

       printf("Connexion acceptée pour le client %s : %d \n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

        while(1){

       		send(socketClientTCP , &compteur , sizeof(int), 0);
       		afficheServerSend(i,addrServer,addrClient,compteur);

       		sleep(1);

       		//recevoir la valeur increment
       		memset(&compteur,0,sizeof(int));
       		recv(socketClientTCP, &compteur ,sizeof(int), 0);
       		afficheServerRcv(i,addrClient,addrServer,compteur);
       		compteur ++;
       		i++;
      
   		}
    	close(socketClientTCP);

       	return 0 ;


}




void afficheServerRcv(int i,struct sockaddr_in addrClient,struct sockaddr_in addrServer,int compteur)
{
	printf("[#server# %d]  %s : %d > %s: %d ( Server ) : %d \n",i,
                inet_ntoa(addrClient.sin_addr),
                ntohs(addrClient.sin_port),
                inet_ntoa(addrServer.sin_addr),
                ntohs(addrServer.sin_port),
                compteur );
}
void afficheServerSend(int i,struct sockaddr_in addrServer,struct sockaddr_in addrClient,int compteur){
	printf("[#server# %d] ( Server ) %s : %d > %s: %d : %d \n",i,
                inet_ntoa(addrServer.sin_addr),
                ntohs(addrServer.sin_port),
                inet_ntoa(addrClient.sin_addr),
                ntohs(addrClient.sin_port),
                compteur );
}