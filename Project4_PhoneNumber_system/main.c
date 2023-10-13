#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <winsock2.h>


#define STDSIZE 100
#define STORAGE_FILE_NAME "Storage.txt"

// Phone Structure
typedef struct Phone{
    unsigned int Id;
    char Phone[9];
    char UserName[STDSIZE];
    char Password[STDSIZE];
    char Provider[STDSIZE];
    char Country[STDSIZE];
}Phone;

// Data Structure and Handling Storage System
Phone * Load_Credantioals(){
    int NumberOfEnterKeys = 0;
    char c;
    unsigned short int index ,j=0;
    char buffer[100];
    FILE *pfile = fopen(STORAGE_FILE_NAME,"r");
    if( pfile == NULL) {
        printf("Storage File Not Found\n");
        return 1;
    }
    printf("\nLoading...");
    while((fgets(buffer,sizeof(buffer),pfile)) != NULL) NumberOfEnterKeys++;
    Phone UserData[NumberOfEnterKeys];
    for(int i = 0; i < NumberOfEnterKeys;i++){
        index=1;
        while((c = fgetc(pfile)) != '\n'){
            if(c == '/'){
                switch(index){
                    case 1:
                        UserData[i].Id = (int)buffer[0];
                        break;
                    case 2:
                        snprintf(UserData[i].Phone, sizeof(buffer),buffer);
                        break;
                    case 3:
                        snprintf(UserData[i].UserName, sizeof(buffer),buffer); 
                        break;
                    case 4:
                        snprintf(UserData[i].Password, sizeof(buffer),buffer);                          // I Dont Like This Tho
                        break;
                    case 5:
                        snprintf(UserData[i].Provider, sizeof(buffer),buffer);
                        break;
                    case 6:
                        snprintf(UserData[i].Country, sizeof(buffer),buffer);
                        break;
                }
                index++;
                memset(buffer,'\0',sizeof(buffer));
                j = 0;
            }
            else{
                buffer[j]=c;
                j++;
            }
        }
    }
    return &UserData;
    // More Code Here...
}
int Add_User_info(){
    R Load_Credantioals()
    short StringValid = 1;
    do{
        printf("Please Give your Username: ");
        scanf("%s",&new_Phone.UserName);
        printf("\n");
        StringValid = 1;
        for(int i = 0; new_Phone.UserName[i]!= '\0'; i++){

        }
    }while(StringValid==0);


    return 0;
}
int Remove_User_info(){
}
int Find_User_info(){
}
int main(){
    srand(time(NULL));
    char PhoneNumber[11];
    char RandomDigit;
    int FixNumber = 1;

    
    for(int i = 0 ; i < 10; i++){
        RandomDigit = rand() % 10 + '0';
        PhoneNumber[i] = (char)RandomDigit;
        if(i == 1 ||  i == 5) { PhoneNumber[i+1] = ' ';i++; }
    }

    for(int i = 0 ; i < 10; i++){
        printf("%c",PhoneNumber[i]);
    }
    printf("\n");
    return 0;
}