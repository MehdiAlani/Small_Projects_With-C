#include <winsock.h>        // -lws2_32 Flag
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>        // -lpThread Flag
#define GROOM_SERVER_IP "127.0.0.1"
#define GROOM_SERVER_PORT 80 

int ConnectServer(int clientSocket , struct sockaddr_in *Sp){ 
    if (connect(clientSocket,(struct sockaddr *)Sp,sizeof(*Sp)) == -1) return 0;
    else return 1;
}
void * TreadSend(void * clientSocket){
    char Msg[4096];
    while(1){
        printf("You: ");
        scanf("%s",&Msg);
        printf("\n");
        while(send(*((int *)clientSocket), Msg, sizeof(Msg) - 1, 0)==-1);
        sleep(0.5);
    }

}
void * TreadRecv(void * clientSocket){
    char buffer[4096];
    while(1){
        if(recv(*((int *)clientSocket),buffer , sizeof(buffer),0) != -1) 
            printf("Server: %s\n",buffer);
    }
}
int main(){
    // Init The Library
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
    pthread_t Th_Send,Th_Recv;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(GROOM_SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr(GROOM_SERVER_IP);

    char buffer[4096] ,Msg[4096];
    memset(&Msg,'\0',sizeof(Msg));
    int clientSocket = socket(AF_INET,SOCK_STREAM,0);

    if(clientSocket == -1){
        printf("Failed To Create Socket\n");
        WSACleanup();
        exit(1);
    }

    while (!ConnectServer(clientSocket,&serverAddress)){
        printf("Failed To Connect To Server \n");
        sleep(1);
    }
    printf("Connnected To Server \n");
    pthread_create(&Th_Recv,NULL,&TreadRecv,&clientSocket);
    pthread_create(&Th_Send,NULL,&TreadSend,&clientSocket);
    pthread_join(Th_Recv,NULL);
    pthread_join(Th_Send,NULL);
    return 0;
}