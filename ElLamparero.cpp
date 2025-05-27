#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

//Roibeth Garcia 6.322.423-9
//Joaquin Poblete

//int tamTab=12, tamLamp=5;
void actualizarLamparero(char lamp[5][5], char tablero[12][12], int filaJ, int colJ) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int filaT = filaJ - 2 + i;
            int colT = colJ - 2 + j;

            if (filaT >= 0 && filaT < 12 && colT >= 0 && colT < 12) {
                lamp[i][j] = tablero[filaT][colT];
            } else {
                lamp[i][j] = ' ';  // fuera del tablero
            }
        }
    }

    lamp[2][2] = '*';  // siempre el jugador está en el centro de su visión
}


void iniciarTablero(char mat[][12]) {
    srand(time(NULL));
    int pos1, pos2;
    int obstI = 40, obstR = 20;
    int lampsA = 9;

    // Inicializar todo con espacios
    for (pos1 = 0; pos1 < 12; pos1++) {
        for (pos2 = 0; pos2 < 12; pos2++) {
            mat[pos1][pos2] = ' ';
        }
    }

    // Colocar obstáculos irrompibles
    while (obstI > 0) {
        pos1 = rand() % 12;
        pos2 = rand() % 12;
        if (mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = 'O';
            obstI--;
        }
    }

    // Colocar lámparas apagadas (sin estar en los bordes ni juntas)
    while (lampsA > 0) {
        pos1 = 1 + rand() % 10; // evita bordes
        pos2 = 1 + rand() % 10;

        // Verifica que no haya lámparas adyacentes
        int valido = 1;
        for (int i = pos1 - 1; i <= pos1 + 1; i++) {
            for (int j = pos2 - 1; j <= pos2 + 1; j++) {
                if (mat[i][j] == 'i') {
                    valido = 0;
                }
            }
        }

        if (valido && mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = 'i';
            lampsA--;
        }
    }

    // Colocar obstáculos rompibles
    while (obstR > 0) {
        pos1 = rand() % 12;
        pos2 = rand() % 12;
        if (mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = '/';
            obstR--;
        }
    }
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

void imprimirLamparero(char lamp[5][5]) {
    int pos1, pos2;
    for (pos1= 0; pos1 < 5; pos1++) {
        for (pos2 = 0; pos2 < 5; pos2++) {
            printf("|%c", lamp[pos1][pos2]);
        }
        printf("|\n");
    }
}
        
int main(){
    srand(time(NULL));
    char Lamp[5][5],tablero[12][12],mov;
    int pos1,pos2,pos1A=6,pos2A=6,pos1AF,pos2AF;
    int obstI=40,ObstR=20;
    int lampsA=9,cantlampsE=0;

    pos1A=rand()%12;
    pos2A=rand()%12;
    iniciarTablero(tablero);
    tablero[pos1A][pos2A] = '*';
    actualizarLamparero(Lamp, tablero, pos1A, pos2A);

    printf("Bienvenido al juego del lamparero\n");
    imprimirTablero(tablero);

    while (1) {
    
        printf("\nMover con WASD: ");
        scanf(" %c", &mov); 

        pos1AF = pos1A;
        pos2AF = pos2A;
        switch(mov){
            case 'a': case 'A':pos2AF--;break;
            case 'w': case 'W': pos1AF--;break;
            case 's': case 'S':pos1AF++;break;
            case 'd': case 'D':pos2AF++;break;
            default:
                printf("comando erroneo\n");
            break;
        }

        // Verificar que se puede mover dentro del tablero
        if (pos1AF >= 0 && pos1AF < 12 && pos2AF >= 0 && pos2AF < 12) {
            // Verificar que no sea un obstáculo irrompible
            if (tablero[pos1AF][pos2AF] != 'O') {
                tablero[pos1A][pos2A] = ' ';           // Borrar posición anterior
                tablero[pos1AF][pos2AF] = '*';         // Nueva posición
                pos1A = pos1AF;                         // Actualizar posición actual
                pos2A = pos2AF;
            } else {
                printf("¡Obstáculo irrompible!\n");
            }
        } else {
            printf("¡Movimiento fuera del tablero!\n");
        }

        actualizarLamparero(Lamp, tablero, pos1A, pos2A);
        imprimirTablero(tablero);
    }

    return 0;
}

