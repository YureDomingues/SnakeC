#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "cobrinha.h"
#include "mapa.h"

Mapa m;
Cobra cobra;
Posicao comidinha;

int terminou = 0;

void inicializar_partes(void){
    int todas_partes = 100;

    cobra.tam_calda = 0;

    cobra.partes[0] = CABECA_COBRA;

    int i;

    for(i=1; i <= todas_partes; i++){
        cobra.partes[i] = '#';
    }

    cobra.partes[i] = '\0';

}


void acabou(int x, int y){
   
    if(tem_objeto(PAREDE_HORIZONTAL, x, y)||
       tem_objeto(PAREDE_VERTICAL, x, y)||
       tem_objeto(CORPO_COBRA, x, y)){

        terminou = 1;
        printw("Foi de comes e bebes x.x\n");

    }
}

int direcao_valida(char direcao){
    return (direcao == CIMA || direcao == BAIXO || direcao == DIREITA || direcao == ESQUERDA);
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

void spawn_objeto(char objeto){

    srand(time(NULL));

    Posicao aleatoria;
    
    do{
        aleatoria.x = rand()%m.linhas;
        aleatoria.y = rand()%m.colunas;
    }while(!tem_objeto(ESPACO, aleatoria.x, aleatoria.y));

    m.mapa[aleatoria.x][aleatoria.y] = objeto;
}

int eh_parte_corpo(int parte){
    if(cobra.partes[parte] == CORPO_COBRA || cobra.partes[parte] == CABECA_COBRA) return 1;

    return 0;
}

int comeu(int origem_x, int origem_y, int destino_x, int destino_y){

    if(!tem_objeto(COMIDINHA, destino_x, destino_y)) return 0;

    spawn_objeto(COMIDINHA);

    cobra.tam_calda++;

    int ultima_parte = cobra.tam_calda;

    cobra.partes[ultima_parte] = CORPO_COBRA;
    
    return 1;
}

int main(void){

    initscr();	

    ler_mapa();
    spawn_objeto(CABECA_COBRA);
    spawn_objeto(COMIDINHA);

    inicializar_partes();

    encontrar_no_mapa(CABECA_COBRA, &cobra.pos_partes[0]);
    
    do{	
        clear();
        imprimir_mapa();
        char comando = 'z';
        comando = getch();
        mover(comando);
    }while(!terminou);

    endwin();
    
    liberar_mapa();
    
    return EXIT_SUCCESS;
}