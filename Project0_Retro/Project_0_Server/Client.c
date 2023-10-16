#include <winsock.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){ 
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
    int clientSocket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(54928);
    serverAddress.sin_addr.s_addr = inet_addr("");
    while(1){
        if(connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress)) == -1){
            printf("Failed To Connect To Server\n");
            sleep(1);
        }
        else{
            printf("Connected To Server\n");
            break;
        }
    }
    char buffer[1024]; // 1Kb of Memory For Ready Data over the Network
    if((recv(clientSocket,buffer,sizeof(buffer),0))==-1){
        printf("Failed to Read from Server\n");
        exit(1);
    }
    printf("From Server :%s\n",buffer);
    return 0;
}