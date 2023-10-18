#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock.h>
#include <string.h>
#include <pthread.h>

void * Recv(void * ClientSocket){
    char buffer[1024];
    memset(&buffer,'\0',sizeof(buffer));
    while(1){
        recv(*((int *)ClientSocket),buffer,sizeof(buffer),0);
        printf("\n Server : %s \n",buffer);
    }
}
void * Send(void * ClientSocket){
    char Msg[1024];
    memset(&Msg,'\0',sizeof(Msg));
    while(1){
        scanf("%s",&Msg);
        send(*((int *)ClientSocket),Msg,sizeof(Msg),0);
    }
}

int main(){
    pthread_t Th_Recv,Th_Send;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
    int ClientSock = socket(AF_INET,SOCK_STREAM,0);
    if( ClientSock == -1){
        printf("Failed To Create Socket");
        exit(1);
    }
    struct sockaddr_in ClientAddress;
    ClientAddress.sin_family =  AF_INET;
    ClientAddress.sin_port = htons(80);
    ClientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(connect(ClientSock,(struct sockaddr *)&ClientAddress,sizeof(ClientAddress)) == -1) printf("Failed To Connect to Server \n");
    printf("Connected To Server \n");
    pthread_create(&Th_Recv,NULL,&Recv,&ClientSock);
    pthread_create(&Th_Send,NULL,&Send,&ClientSock);
    pthread_join(Th_Send,NULL);
    pthread_join(Th_Recv,NULL);
    return 0;
}