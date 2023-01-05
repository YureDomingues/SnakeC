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
    cobra.tam_calda = 1;
    cobra.partes[0] = CABECA;
    cobra.partes[1] = CORPO;
    cobra.partes[2] = '\0';
}

void acabou(int x, int y){
   
    if(tem_objeto(PAREDE_HORIZONTAL, x, y)||
       tem_objeto(PAREDE_VERTICAL, x, y)||
       tem_objeto(CORPO, x, y)) terminou = 1;
    
}

int direcao_valida(char direcao){
    return (direcao == CIMA || 
            direcao == BAIXO || 
            direcao == DIREITA || 
            direcao == ESQUERDA);
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

    int pos_inicial_x = cobra.pos_partes[0].x; //cabeça da cobra x
    int pos_inicial_y = cobra.pos_partes[0].y; //cabeça da cobra y
    int pos_final_x = pos_inicial_x;
    int pos_final_y = pos_inicial_y;
   
    switch (direcao){
        case CIMA:
            pos_final_x--;
            break;
        case BAIXO:
            pos_final_x++;
            break;
        case ESQUERDA:
            pos_final_y--;
            break;
        case DIREITA:
            pos_final_y++;
            break;
            
    }

    comeu(pos_inicial_x, pos_inicial_y, pos_final_x, pos_final_y);
    acabou(pos_final_x, pos_final_y);
    atualizar_posicoes(pos_final_x, pos_final_y);
    
}

void spawn_objeto(char objeto){

    srand(time(NULL));

    Posicao aleatoria;
    
    do{
        if(objeto == CABECA){
            aleatoria.x = rand()%(m.linhas-1) +1;
            aleatoria.y = rand()%(m.colunas-1)+1;
        }else{
            aleatoria.x = rand()%(m.linhas-1) +1;
            aleatoria.y = rand()%(m.colunas-1)+1;
        }
        
    }while(!tem_objeto(ESPACO, aleatoria.x, aleatoria.y));

    m.mapa[aleatoria.x][aleatoria.y] = objeto;
}

int eh_parte_corpo(int parte){
    if(cobra.partes[parte] == CORPO || cobra.partes[parte] == CABECA) return 1;

    return 0;
}

int comeu(int origem_x, int origem_y, int destino_x, int destino_y){

    if(!tem_objeto(COMIDINHA, destino_x, destino_y)) return 0;

    cobra.tam_calda++;
    int ultima_parte = cobra.tam_calda;
    cobra.partes[ultima_parte] = CORPO;
    
    spawn_objeto(COMIDINHA);
    
    return 1;
}

int main(void){
    WINDOW *tela = initscr();	

    ler_mapa();
    spawn_objeto(COMIDINHA);
    spawn_objeto(CABECA);
    encontrar_no_mapa(CABECA, &cobra.pos_partes[0]);
    inicializar_partes();
    
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