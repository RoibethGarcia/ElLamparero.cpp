#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Roibeth Garcia 6.322.423-9
// Joaquin Poblete 5.627.541-5

#define tamTab 12
#define tamLamparero 5
#define tamLampara 3


void actualizarVisibilidad(bool vis[][tamTab], char tablero[][tamTab], int filaJ, int colJ);
void imprimirLampara(char lampara[][tamLampara]) ;
void leer_linea(char str[], int tam);
void actualizarLamparero(char lamp[][tamLamparero], char tablero[][tamTab], int pos1, int pos2);
void actualizarVisionJugador(bool vis[][tamTab], int filaJ, int colJ);
void iniciarTablero(char mat[][tamTab]);
void inicializarVisibilidad(bool vis[][tamTab]);
void imprimirTableroVisible(char tablero[][tamTab], bool vis[][tamTab]);
void imprimirLamparero(char lamp[][tamLamparero]);
void EncenderLampara(char lampara[][tamLampara], char tablero[][tamTab], int pos1, int pos2, bool vis[][tamTab]);
void MensajeRamdom();
int ContarCasillasVisibles(bool visible[][tamTab]);

int main() {
    srand(time(NULL));
    char Lamp[tamLamparero][tamLamparero], tablero[tamTab][tamTab], lampara[tamLampara][tamLampara], mov[10];
    int posStr = 0, pos1A = 6, pos2A = 6, pos1AF, pos2AF;
    int ObsDest = 5, tamStr = 10;
    int totalCasillas = tamTab * tamTab, casillasVisibles=0;
    bool puedeMover = true;
    bool visible[12][12];
    int salir=0;

    pos1A = rand() % tamTab;
    pos2A = rand() % tamTab;
    iniciarTablero(tablero);
    tablero[pos1A][pos2A] = '*';

    actualizarLamparero(Lamp, tablero, pos1A, pos2A);
    inicializarVisibilidad(visible);
    actualizarVisionJugador(visible, pos1A, pos2A);

    printf("Bienvenido al juego del lamparero\n");
    imprimirTableroVisible(tablero, visible);

    while (salir!=1) {
        actualizarVisibilidad(visible, tablero, pos1A, pos2A);
        casillasVisibles=ContarCasillasVisibles(visible);

        printf("\nPueden destruirse %d obstaculos. Utilice WASD para moverse", ObsDest);
        printf(", o puede digitar -Rendirse- para terminar:\n");
        leer_linea(mov, tamStr);

        if (strcmp(mov, "Rendirse") == 0 || strcmp(mov, "rendirse") == 0) {
            MensajeRamdom();
            salir=1;
        }

        pos1AF = pos1A;
        pos2AF = pos2A;
        puedeMover = true;

        switch (mov[posStr]) {
            case 'a': case 'A': pos2AF--; break;
            case 'w': case 'W': pos1AF--; break;
            case 's': case 'S': pos1AF++; break;
            case 'd': case 'D': pos2AF++; break;
            default:
                printf("Entrada Invalida, vuelva a intentarlo\n");
                break;
        }

        if (pos1AF >= 0 && pos1AF < tamTab && pos2AF >= 0 && pos2AF < tamTab) {
            if (tablero[pos1AF][pos2AF] != 'O') {
                if (tablero[pos1AF][pos2AF] == 'i') {
                    EncenderLampara(lampara, tablero, pos1AF, pos2AF, visible);
                }
                if (tablero[pos1AF][pos2AF] == '/') {
                    if (ObsDest > 0) {
                        ObsDest--;
                        tablero[pos1AF][pos2AF] = ' ';
                    } else {
                        printf("Ya no puedes romper mas obstaculos rompibles!\n");
                        puedeMover = false;
                    }
                }
                if (puedeMover) {
                    if (tablero[pos1A][pos2A] == '*') {
                        if (lampara[1][1] == 'Y')
                            tablero[pos1A][pos2A] = 'Y';
                        else
                            tablero[pos1A][pos2A] = ' ';
                    }
                    if (tablero[pos1AF][pos2AF] != 'Y')
                        tablero[pos1AF][pos2AF] = '*';

                    pos1A = pos1AF;
                    pos2A = pos2AF;
                }
            } else
                printf("Hay un obstaculo irrompible!\n");
        } else
            printf("Movimiento fuera del tablero!\n");

        actualizarLamparero(Lamp, tablero, pos1A, pos2A);
        imprimirTableroVisible(tablero, visible);
         if (casillasVisibles >= totalCasillas / 2) {
            printf("¡Felicidades!, ahora anda a buscar la pala.\n");
            salir=1;
        }
    }

    return 0;
}

void actualizarLamparero(char lamp[][tamLamparero], char tablero[][tamTab], int pos1, int pos2) {
    int mitad = tamLamparero / 2;
    for (int i = 0; i < tamLamparero; i++) {
        for (int j = 0; j < tamLamparero; j++) {
            int filaT = pos1 - mitad + i;
            int colT = pos2 - mitad + j;
            lamp[i][j] = (filaT >= 0 && filaT < tamTab && colT >= 0 && colT < tamTab) ? tablero[filaT][colT] : ' ';
        }
    }
    lamp[mitad][mitad] = '*';
}

void actualizarVisionJugador(bool vis[][tamTab], int filaJ, int colJ) {
    for (int i = 0; i < tamTab; i++)
        for (int j = 0; j < tamTab; j++)
            vis[i][j] = false;

    int mitad = tamLamparero / 2;
    for (int i = filaJ - mitad; i <= filaJ + mitad; i++) {
        for (int j = colJ - mitad; j <= colJ + mitad; j++) {
            if (i >= 0 && i < tamTab && j >= 0 && j < tamTab)
                vis[i][j] = true;
        }
    }
}

void iniciarTablero(char mat[][tamTab]) {
    int pos1, pos2, obstI = 40, obstR = 20, lampsA = 9;
    for (pos1 = 0; pos1 < tamTab; pos1++)
        for (pos2 = 0; pos2 < tamTab; pos2++)
            mat[pos1][pos2] = ' ';

    while (obstI > 0) {
        pos1 = rand() % tamTab;
        pos2 = rand() % tamTab;
        if (mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = 'O';
            obstI--;
        }
    }

    while (lampsA > 0) {
        pos1 = 1 + rand() % (tamTab - 2);
        pos2 = 1 + rand() % (tamTab - 2);
        int valido = 1;
        for (int i = pos1 - 1; i <= pos1 + 1; i++)
            for (int j = pos2 - 1; j <= pos2 + 1; j++)
                if (mat[i][j] == 'i') valido = 0;

        if (valido && mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = 'i';
            lampsA--;
        }
    }

    while (obstR > 0) {
        pos1 = rand() % tamTab;
        pos2 = rand() % tamTab;
        if (mat[pos1][pos2] == ' ') {
            mat[pos1][pos2] = '/';
            obstR--;
        }
    }
}

void inicializarVisibilidad(bool vis[][tamTab]) {
    for (int i = 0; i < tamTab; i++)
        for (int j = 0; j < tamTab; j++)
            vis[i][j] = false;
}

void imprimirTableroVisible(char tablero[][tamTab], bool vis[][tamTab]) {
    for (int i = 0; i < tamTab; i++) {
        for (int j = 0; j < tamTab; j++) {
            printf("|%c", vis[i][j] ? tablero[i][j] : ' ');
        }
        printf("|\n");
    }
}

void imprimirLamparero(char lamp[][tamLamparero]) {
    for (int i = 0; i < tamLamparero; i++) {
        for (int j = 0; j < tamLamparero; j++) {
            printf("|%c", lamp[i][j]);
        }
        printf("|\n");
    }
}

void EncenderLampara(char lampara[][tamLampara], char tablero[][tamTab], int pos1, int pos2, bool vis[][tamTab]) {
    int mitad = tamLampara / 2;
    for (int i = -mitad; i <= mitad; i++) {
        for (int j = -mitad; j <= mitad; j++) {
            int fila = pos1 + i;
            int col = pos2 + j;
            if (fila >= 0 && fila < tamTab && col >= 0 && col < tamTab) {
                lampara[i + mitad][j + mitad] = tablero[fila][col];
                vis[fila][col] = true;
            } else {
                lampara[i + mitad][j + mitad] = ' ';
            }
        }
    }
    tablero[pos1][pos2] = 'Y';
    imprimirLampara(lampara);
}

void leer_linea(char str[], int tam) {
    int pos = 0;
    char letra;

    do {
        letra = getchar();
        if (letra != '\n' && pos < tam - 1) {
            str[pos] = letra;
            pos++;
        }
    } while (letra != '\n');

    str[pos] = '\0';

    while (letra != '\n' )
        letra = getchar();
}
void imprimirLampara(char lampara[][tamLampara]) {
    for (int i = 0; i < tamLampara; i++) {
        for (int j = 0; j < tamLampara; j++) {
            printf("|%c", lampara[i][j]);
        }
        printf("|\n");
    }
}

void actualizarVisibilidad(bool vis[][tamTab], char tablero[][tamTab], int filaJ, int colJ) {
    // Apagar toda visibilidad
    for (int i = 0; i < tamTab; i++) {
        for (int j = 0; j < tamTab; j++) {
            vis[i][j] = false;
        }
    }

    // Encender visibilidad por lámparas encendidas ('Y')
    for (int i = 0; i < tamTab; i++) {
        for (int j = 0; j < tamTab; j++) {
            if (tablero[i][j] == 'Y') {
                for (int a = i - 1; a <= i + 1; a++) {
                    for (int b = j - 1; b <= j + 1; b++) {
                        if (a >= 0 && a < tamTab && b >= 0 && b < tamTab) {
                            vis[a][b] = true;
                        }
                    }
                }
            }
        }
    }

    // Encender visibilidad por el jugador (5x5)
    for (int i = filaJ - 2; i <= filaJ + 2; i++) {
        for (int j = colJ - 2; j <= colJ + 2; j++) {
            if (i >= 0 && i < tamTab && j >= 0 && j < tamTab) {
                vis[i][j] = true;
            }
        }
    }
}
void MensajeRamdom(){
    int aleatorio = rand() % 3;
    switch (aleatorio) {
        case 0:
            printf("HEAVEN ISN'T FOR THE WEAK!\n");
            break;
        case 1:
            printf("TE FALTO CALLE MANITO!\n");
            break;
        case 2:
            printf("EPA!, REVISATE EL PANTALON\n");
            break;
    }
}

int ContarCasillasVisibles(bool visible[][tamTab]) {
    int contador = 0;
    int pos1, pos2;

    for (pos1 = 0; pos1 < tamTab; pos1++)
        for (pos2 = 0; pos2 < tamTab; pos2++)
            if (visible[pos1][pos2])
                contador++;

    return contador;
}