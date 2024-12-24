#ifndef COMMON_H
#define COMMON_H
 #include <sys/types.h>          
 #include <sys/socket.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <arpa/inet.h>
 #include <unistd.h>


void afficheClientRcv(int,int);
void afficheClientSend(int,int);
void afficheServerRcv(int,struct sockaddr_in ,struct sockaddr_in ,int );
void afficheServerSend(int,struct sockaddr_in ,struct sockaddr_in ,int );

#endif