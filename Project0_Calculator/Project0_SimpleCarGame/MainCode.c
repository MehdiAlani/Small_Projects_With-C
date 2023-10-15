#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define ResoltionX 30
#define ResoltionY 20
#define WallSize 3


typedef struct Player{
    unsigned int x;
    unsigned int y;
}Player;


double Distance(int X1,int X2 ,int Y1,int Y2){
    double Dist;
    Dist = sqrt( pow(X2-X1,2) + pow(Y2-Y1,2) );
    return Dist;
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
// Display Section
int Display(){
    // Init The Display
    char MatriceDisplay[ResoltionY][ResoltionX];
    time_t StartTime,EndTime;
    Player player;
    char UserKey;
    player.x = ResoltionX / 2;
    player.y = ResoltionY - 5;
    StartTime = time(NULL);
    while(1){
        // Generate Frame
        for(int i = 0; i < ResoltionY; i++){
            for(int j = 0; j < ResoltionX; j++){
                if(j < WallSize || j >= ResoltionX - WallSize) MatriceDisplay[i][j] = '#';
                else {
                    if(Distance(player.x,j,player.y,i) <= sqrt(2)) {MatriceDisplay[i][j]='@';}
                    else MatriceDisplay[i][j]= ' ';
                }
            }
        }

        // Display Image

        for(int i = 0; i < ResoltionY; i++){
            for(int j = 0; j < ResoltionX; j++){
                printf("%c",MatriceDisplay[i][j]);
            }
            printf("\n");
        }
        EndTime = time(NULL);
    // Change Player Status
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
        system("cls");
        //Beep(1000, 10);
        //printf("Time Passed %ld\n",EndTime-StartTime);
        //printf("X:%d Y:%d\n",player.x,player.y);
    }
}

// Main Program
int main(){
    Display();
    


    return 0;
}