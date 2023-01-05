#ifndef _COBRINHA_H
#define _COBRINHA_H

#define CABECA_COBRA 'C'
#define CORPO_COBRA 'O'
#define COMIDINHA 'x'

#define CIMA 'w'
#define ESQUERDA 'a'
#define BAIXO 's'
#define DIREITA 'd'

#include "mapa.h"

typedef struct Cobra{
    char partes[100+1];
    Posicao pos_partes[100];
    int tam_calda;
}Cobra;

void inicializar_partes(void);
void acabou(int x, int y);
int direcao_valida(char direcao);
void spawn_objeto(char objeto);
int comeu(int origem_x, int origem_y, int destino_x, int destino_y);
void atualizar_posicoes(int destino_x, int destino_y);
void mover(char direcao);

#endif