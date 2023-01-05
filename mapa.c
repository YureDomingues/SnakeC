#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "cobrinha.h"

extern Mapa m;
extern Cobra cobra;
extern Posicao comidinha;
extern int terminou;

void imprimir_mapa(void){
    for(int i=0; i< m.linhas; i++){
        printw("%s\n", m.mapa[i]);
    }

}

void alocar_mapa(void){

    m.mapa = malloc(sizeof(char*) * m.linhas);

    for(int i=0; i< m.linhas; i++){
        m.mapa[i] = malloc(sizeof(char) * (m.colunas+1));
    }

}

void liberar_mapa(void){
    for(int i=0; i < m.linhas; i++){
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
            }
        }
    }
}

int eh_parede(int x, int y){
    return (m.mapa[x][y] == PAREDE_HORIZONTAL || m.mapa[x][y] == PAREDE_VERTICAL);
}

void atualizar_posicoes(int destino_x, int destino_y){

    int obj_x = destino_x;
    int obj_y = destino_y;

    int tamanho_cobra = cobra.tam_calda+1;

    for(int i = 0; i < tamanho_cobra; i++){
        int atual_x = cobra.pos_partes[i].x;
        int atual_y = cobra.pos_partes[i].y;

        cobra.pos_partes[i].x = obj_x;
        cobra.pos_partes[i].y = obj_y; 

        m.mapa[obj_x][obj_y] = cobra.partes[i];
        m.mapa[atual_x][atual_y] = ESPACO; 

        obj_x = atual_x;
        obj_y = atual_y;
         
    }
    
}

void teste_corpo(int numero_partes){
    printf("Partes Corpo:\n");
    for(int i=0; i < numero_partes; i++){
        printf("[%d] = %c\n", i, cobra.partes[i]);
    }
}

void teste_posicoes(int numero_posicoes){
    printf("Posicoes:\n");
    for(int i=0; i < numero_posicoes; i++){
        printf("[%d]: (%d, %d)\n", i, cobra.pos_partes[i].x, cobra.pos_partes[i].y);
    }
}


void mover(char direcao){

    if(!direcao_valida(direcao)) return;

    int old_x = cobra.pos_partes[0].x;
    int old_y = cobra.pos_partes[0].y;
    int novo_x = old_x;
    int novo_y = old_y;

    m.mapa[old_x][old_x] = ESPACO;
   

    switch (direcao){
        case CIMA:
            novo_x--;
            break;
        case BAIXO:
            novo_x++;
            break;
        case ESQUERDA:
            novo_y--;
            break;
        case DIREITA:
            novo_y++;
            break;
            
    }

    //coloquei essa função antes do mover_cobra para não trocar o caractere que precisa ser verificado em acabou()
    acabou(novo_x, novo_y);
    comeu(old_x, old_y, novo_x, novo_y);
    atualizar_posicoes(novo_x, novo_y);
    
}

int tem_objeto(char objeto, int x, int y){
    if(m.mapa[x][y] == objeto) return 1;
    return 0;
}

void posicao_comidinha(void){
    Posicao comida;
    encontrar_no_mapa(COMIDINHA, &comida);
    printf("Comida:\n(x, y) = (%d, %d)\n", comida.x, comida.y);
}