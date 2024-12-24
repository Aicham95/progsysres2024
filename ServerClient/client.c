#include "common.h"

int main(int argc , char *argv[]){

	if(argc < 3){
              printf("Erreur : nombre d'arguments insuffisant\n");
              printf("Usage : %s adresse_IP_PORT \n",argv[0]);
              return 0 ;
    }
    // Creation de la socket::
    int socketClient = socket(AF_INET,SOCK_STREAM,0);
    if(socketClient == -1)
    {
        perror("Erreur de creation  du socket..");
        return 0 ;
    }

    //2. Preparation de la structure vers le server::
    struct sockaddr_in addrServer;

    memset(&addrServer, 0 , sizeof(struct sockaddr_in));

    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[2]));
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);

     //3)connect

    int resultat = connect(socketClient, (struct sockaddr *) &addrServer,sizeof(struct sockaddr_in));

    if(resultat == -1)
    {
        perror("Erreur d'ouverture de connexion");
        return 0 ;
    }

    //4. logique de l'application

   int compteur;
   int nbreceive = 0;
   int i= 0;

   while(1){
   		memset(&compteur,0,sizeof(int));    
   		nbreceive = recv(socketClient,&compteur ,sizeof(int),0);
   		if(nbreceive > 0){
   			afficheClientRcv(i,compteur);
   		}
   		compteur++ ;
   		sleep(1);
        send(socketClient, &compteur, sizeof(int),0);
        afficheClientSend(i,compteur);
        i++ ;
   }
   close(socketClient);
   return 0 ;

}


void afficheClientRcv(int i,int compteur){
	printf(" [%d] Client > Server / %d\n",i,compteur);
}

void afficheClientSend(int i,int compteur){
	printf(" [%d] Server > Client / %d\n",i,compteur);
}