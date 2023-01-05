#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "mapa.h"
#include "cobrinha.h"

extern Mapa m;
extern Cobra cobra;
extern Posicao comidinha;
extern int terminou;

void imprimir_mapa(void){
    for(int i = 0; i < m.linhas; i++){
        printw("%s\n", m.mapa[i]);
    }
}

void alocar_mapa(void){

    m.mapa = (char**) malloc(sizeof(char*) * m.linhas);

    for(int i = 0; i < m.linhas; i++){
        m.mapa[i] = (char*) malloc(sizeof(char) * (m.colunas+1));
    }

}

void liberar_mapa(void){
    for(int i = 0; i < m.linhas; i++){
        free(m.mapa[i]);
    }

    free(m.mapa);
}

void ler_mapa(void){
    FILE *f;
    f = fopen("mapa.txt", "r");

    if(f == NULL){
        printw("Erro na leitura do arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d %d", &m.linhas, &m.colunas);

    alocar_mapa();
    
    for(int i=0; i < m.linhas; i++){
        fscanf(f, "%s", m.mapa[i]);
    }

    fclose(f);
}

void encontrar_no_mapa(char objeto, Posicao *coordenadas){
    for(int i=0; i < m.linhas; i++){
        for(int j=0; j < m.colunas; j++){
            if(m.mapa[i][j] == objeto){
                coordenadas->x = i;
                coordenadas->y = j;
                return;
            }
        }
    }
}

int eh_parede(int x, int y){
    return (m.mapa[x][y] == PAREDE_HORIZONTAL || m.mapa[x][y] == PAREDE_VERTICAL);
}

int tem_objeto(char objeto, int x, int y){
    if(m.mapa[x][y] == objeto) return 1;
    return 0;
}