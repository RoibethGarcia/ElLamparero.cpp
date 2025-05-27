#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

//Roibeth Garcia 6.322.423-9
//Joaquin Poblete

char iniciarLamparero(char lamp[][5]){
    int pos1,pos2;
    for(pos1=0;pos1<5;pos1++)
        for(pos2=0;pos2<5;pos2++)
            lamp[pos1][pos2]=' ';
    lamp[pos1][pos2]='*';    
}
char iniciarTablero(char mat[][12]){
    srand(time(NULL));
    int pos1,pos2,obstI=40,ObstR=20;
    int lampsA=9,cantlampsE=0;
    char lampsE[3];

    for(pos1=0;pos1<12;pos1++)
        for(pos2=0;pos2<12;pos2++)
            mat[pos1][pos2]=' ';
    do{
        pos1=rand()%12;
        pos2=rand()%12;
        if(mat[pos1][pos2]==' '){
            mat[pos1][pos2]='O';
            obstI--;
        }

    }while(obstI>0);

    do{
        pos1=rand()%12;
        pos2=rand()%12;
        if(mat[pos1][pos2]==' '){
            mat[pos1][pos2]='i';
            lampsA--;
        }
    }while(lampsA<9);

    do{
        pos1=rand()%12;
        pos2=rand()%12;
        if(mat[pos1][pos2]==' '){
            mat[pos1][pos2]='/';
            ObstR--;
        }
    }while(ObstR<20);


}

void imprimirTablero(char mat[][12]){
    int pos1,pos2;
  for(pos1=0;pos1<12;pos1++){
        for(pos2=0;pos2<12;pos2++){
                printf("|%c",mat[pos1][pos2]);
        }
        printf("|\n");
    }
}
        
int main(){
    srand(time(NULL));
    char Lamp[5][5];
    char tablero[12][12],pos1,pos2,pos1A,pos2A,pos1AF,pos2AF;
    iniciarLamparero(Lamp);
    iniciarTablero(tablero);
    printf("Bienvenido al juego del lamparero\n");
    imprimirTablero(tablero);

    return 0;
}