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
        printf("\n Client : %s \n",buffer);
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
    struct sockaddr_in ServerAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(80);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    int ServerSock;
    if((ServerSock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        printf("Failed to Create Socket... \n");
        exit(1);
    }
    if(bind(ServerSock,(struct sockaddr *)&ServerAddress,sizeof(ServerAddress)) == -1) {
        printf("Failed To bind\n");
        exit(1);
    }
    if(listen(ServerSock,0) == -1){
        printf("Failed To listen... \n");
        exit(1);
    }
    printf("Listening on port 80... \n");
    struct sockaddr_in ClientAddress;
    int lenAddr = sizeof(ClientAddress);
    int ClientSock = accept(ServerSock,(struct sockaddr *)&ClientAddress,&lenAddr);
    printf("Client Connected\n");
    pthread_create(&Th_Recv,NULL,&Recv,&ClientSock);
    pthread_create(&Th_Send,NULL,&Send,&ClientSock);
    pthread_join(Th_Send,NULL);
    pthread_join(Th_Recv,NULL);
    return 0;
}