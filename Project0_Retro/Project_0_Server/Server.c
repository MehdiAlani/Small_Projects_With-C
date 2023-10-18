#include <winsock.h>        // -lws2_32 Flag
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>        // -lpThread Flag
int main(){
    // init The 
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

    int ServerSock = socket(AF_INET,SOCK_STREAM,0) , ClientSocket1 ,ClientSocket2;
    if(ServerSock == - 1){
        printf("Failed To Create Socket \n");
        exit(1);
    }
    
    struct sockaddr_in ClientAddress;
    struct sockaddr_in ServerAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(80);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    char Msg[4096],buffer[4096];
    memset(&Msg,'\0',sizeof(Msg));

    if(bind(ServerSock,(struct sockaddr *)&ServerAddress,sizeof(ServerAddress)) == -1) {
        printf("Failed To bind\n");
        exit(1);
    }
    if(listen(ServerSock,5) == -1){
        printf("Listening Failed\n");
        exit(1);
    }
    printf("Listening on port 80 .. \n");
    int lenAddr = sizeof(ClientAddress);
    ClientSocket1 = accept(ServerSock,(struct sockaddr *)&ClientAddress,&lenAddr);
    printf("Client Connected\n");
    while(1){
        printf("You: ");
        scanf("%s",&Msg);
        printf("%s\n",Msg);
        fflush(stdin);
        send(ClientSocket1,Msg,sizeof(Msg)-1,0);
        if(recv(ServerSock,buffer,sizeof(buffer),0) != 1) printf("Client: %s\n",buffer);
    }
}