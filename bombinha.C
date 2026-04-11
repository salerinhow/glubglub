#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int lerInteiro(const char *msg) {
    int valor;
    printf("%s", msg);
    scanf("%d", &valor);
    return valor;
}

void gerarMapa(char mapa[MAX][MAX], int tamanho) {
    for(int i=0;i<tamanho;i++)
        for(int j=0;j<tamanho;j++)
            mapa[i][j] = '-';
}

void espalharBombas(char mapa[MAX][MAX], int tamanho, int bombas) {
    int colocadas = 0;
    while(colocadas < bombas) {
        int x = rand() % tamanho;
        int y = rand() % tamanho;
        if(mapa[x][y] != '*') {
            mapa[x][y] = '*';
            colocadas++;
        }
    }
}

void mostrarMapa(char mapa[MAX][MAX], int tamanho) {
    printf("\n   "); // margem para alinhar números das linhas
    for(int i=0;i<tamanho;i++) printf("%d ", i);
    printf("\n");
    for(int i=0;i<tamanho;i++){
        printf("%d  ", i);
        for(int j=0;j<tamanho;j++)
            printf("%c ", mapa[i][j]);
        printf("\n");
    }
}

// ===== LOGICA =====
int contarBombasVizinhas(char bombas[MAX][MAX], int x, int y, int tamanho) {
    int count=0;
    for(int i=x-1;i<=x+1;i++){
        for(int j=y-1;j<=y+1;j++){
            if(i>=0 && i<tamanho && j>=0 && j<tamanho){
                if(bombas[i][j]=='*') count++;
            }
        }
    }
    return count;
}

void abrirCelula(char mapaJogador[MAX][MAX], char mapaBombas[MAX][MAX], int x, int y, int tamanho) {
    if(x<0 || x>=tamanho || y<0 || y>=tamanho) return;
    if(mapaJogador[x][y] != '-') return;
    
    int bombas = contarBombasVizinhas(mapaBombas, x, y, tamanho);
    mapaJogador[x][y] = bombas + '0';

    if(bombas == 0){
        for(int i=x-1;i<=x+1;i++)
            for(int j=y-1;j<=y+1;j++)
                abrirCelula(mapaJogador, mapaBombas, i, j, tamanho);
    }
}

int escolherDificuldade(char *nomeDificuldade, int *tamanho, int *totalBombas) {
    printf("==== BOMBZONE ====\n");
    printf("Escolha a dificuldade:\n");
    printf("1 - Facil (5x5, 5 bombas)\n");
    printf("2 - Medio (8x8, 10 bombas)\n");
    printf("3 - Dificil (10x10, 20 bombas)\n");
    
    int op = lerInteiro("> ");
    switch(op) {
        case 1: *tamanho=5; *totalBombas=5; sprintf(nomeDificuldade, "Facil"); break;
        case 2: *tamanho=8; *totalBombas=10; sprintf(nomeDificuldade, "Medio"); break;
        case 3: *tamanho=10; *totalBombas=20; sprintf(nomeDificuldade, "Dificil"); break;
        default: *tamanho=8; *totalBombas=10; sprintf(nomeDificuldade, "Medio"); break;
    }
    return op;
}

int main() {
    srand(time(NULL));

    int tamanho, totalBombas;
    char nomeDificuldade[20];

    escolherDificuldade(nomeDificuldade, &tamanho, &totalBombas);

    char mapa[MAX][MAX];
    char bombas[MAX][MAX];

    gerarMapa(mapa, tamanho);
    gerarMapa(bombas, tamanho);
    espalharBombas(bombas, tamanho, totalBombas);

    int x, y;
    int acertou = 1;
    int abertas = 0;
    int jogadas = 0;

    while(acertou && abertas < tamanho*tamanho - totalBombas){
        printf("\nDificuldade escolhida: %s\n", nomeDificuldade);
        mostrarMapa(mapa, tamanho);
        printf("Jogadas: %d | Bombas: %d\n", jogadas, totalBombas);

        x = lerInteiro("Linha: ");
        y = lerInteiro("Coluna: ");

        if(x<0 || x>=tamanho || y<0 || y>=tamanho){
            printf("Coordenadas invalidas!\n");
            continue;
        }

        if(bombas[x][y] == '*'){
            acertou = 0;
        } else {
            abrirCelula(mapa, bombas, x, y, tamanho);
            abertas++;
        }
        jogadas++;
    }

    mostrarMapa(bombas, tamanho);
    if(acertou) {
        printf("\nPARABENS! Voce venceu!\n");
    } else {
        printf("\nBOOM! Voce acertou uma bomba!\n");
    }

    printf("Total de jogadas: %d\n", jogadas);
    return 0;
}

