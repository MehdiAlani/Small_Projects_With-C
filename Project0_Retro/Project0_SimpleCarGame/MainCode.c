#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <windows.h>
#include <pthread.h>


#define ResoltionX 40
#define ResoltionY 15
#define WallSize 3


typedef struct Object{
    unsigned int x;
    unsigned int y;
}Object;
// GeneralStuff
double Distance(int X1,int X2 ,int Y1,int Y2){
    double Dist;
    Dist = sqrt( pow(X2-X1,2) + pow(Y2-Y1,2) );
    return Dist;
}
int EnnemyRandom(){
    srand(time(NULL));
    short int Random_x;
    do{
        Random_x = rand() % ResoltionX; 
    }while(Random_x > ResoltionX - 2 || Random_x < 2 );
    return Random_x;
}
// Generate Sound
void * Sound (){
    while(1){
       for(int i = 1000;i<7000;i+=1000){
            Beep(i,500);
            Beep(7000-i,500);
            Beep(i+2000,500);
            Beep(8000-i,500);
       }
    }
}
//Get UserInputSection
char UserInput(){
    char Key_Code;
    while(1){
        if(_kbhit()){
            Key_Code = _getch(); 
            if(Key_Code == 'd' || Key_Code == 'z' || Key_Code == 'q'|| Key_Code == 's' ){
                return Key_Code;
            }
            else
                continue;
        }
    }
}
//Load The Game

int LoadGame(){
    return 1;
}

// Display Section
void *Generate_Frame(void* args){
    char MatriceDisplay[ResoltionY][ResoltionX];
    time_t StartTime,EndTime;
    StartTime = time(NULL);
    Object *player = (Object *)args;
    Object Ennemy;
    Ennemy.x = EnnemyRandom();
    Ennemy.y = 2; 
    int X,Y;
    // Generate Frame
    while(1){
        //printf("X=%d Y=%d\n",X,Y);
        X = player -> x;
        Y = player -> y;
        for(int i = 0; i < ResoltionY; i++){
            for(int j = 0; j < ResoltionX; j++){
                if(j < WallSize || j >= ResoltionX - WallSize) MatriceDisplay[i][j] = '#';
                else {
                    if(Distance(X,j,Y,i) <= sqrt(2)) MatriceDisplay[i][j]='@';
                    else if(Distance(Ennemy.x,j,Ennemy.y,i) <= sqrt(2)) MatriceDisplay[i][j]='*';
                    else MatriceDisplay[i][j]= ' ';
                    if(Distance(Ennemy.x,X,Ennemy.y,Y) <= sqrt(2)) return 0 ;
                }
            }
        }
        Ennemy.y++;
        if(Ennemy.y == ResoltionY) {
            Ennemy.y = 2;
            Ennemy.x = EnnemyRandom();
        }
        // Display Image and Time
        
        EndTime = time(NULL);
        printf("Time Passed %d Seconds\n",EndTime-StartTime);
        printf("X=%d,Y=%d\n",X,Y);
        for(int i = 0; i < ResoltionY; i++){
            for(int j = 0; j < ResoltionX; j++){
                printf("%c",MatriceDisplay[i][j]);
            }
            printf("\n");
        }
        sleep(0.5);
        system("cls");
        
    }
}
int Engine() {
    // Init The Threads
    Object player;
    pthread_t RenderThread ,SoundTread;
    char UserKey;
    player.x = ResoltionX / 2;
    player.y = ResoltionY - 5;
    int Status=1;
    pthread_create(&RenderThread,NULL,&Generate_Frame,&player);
    pthread_create(&SoundTread,NULL,&Sound,NULL);
    //pthread_join(RenderThread,NULL);
    // Change Player Status
    while(Status){
            UserKey = UserInput();
            switch(UserKey){
                case 'z':
                    player.y--;
                    break;
                case 's':
                    player.y++;
                    break;
                case 'q':
                    player.x--;
                    break;
                case 'd':
                    player.x++;
                    break;
            }
            if(player.y < 2) player.y++;
            else if(player.y > ResoltionY - 3) player.y--;
            else if(player.x < 4) player.x++;
            else if(player.x > ResoltionX - 5) player.x--;
        //Beep(1000, 10);
        //printf("Time Passed %ld\n",EndTime-StartTime);
        //printf("X:%d Y:%d\n",player.x,player.y);
    }
    return Status;
}
// Main Program
int main(){
    int Status = LoadGame();
    if(Status == 1){
        Engine();
        return 0;
    }
    else {
        printf("An Error has Occured !\n");
        return 0;
    }
}