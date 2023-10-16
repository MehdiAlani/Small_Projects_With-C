#include <stdio.h>
#include <winsock2.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }


    int ServerSock = socket(AF_INET,SOCK_STREAM,0) , ClientSocket;
    if(ServerSock == - 1){
        printf("Failed To Create Socket \n");
        exit(1);
    }
    struct sockaddr_in ClientAddress;
    struct sockaddr_in ServerAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(80);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
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
    ClientSocket = accept(ServerSock,(struct sockaddr *)&ClientAddress,&lenAddr);
    printf("Client Connected\n");
    char Text[] = "Hey From LocalHost:80";
    send(ClientSocket,Text,sizeof(Text)-1,0);
    return 0;
}