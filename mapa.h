#ifndef _MAPA_H
#define _MAPA_H

#define PAREDE_HORIZONTAL '-'
#define PAREDE_VERTICAL '|'
#define ESPACO '.'

typedef struct{
    int x;
    int y;
}POSICAO;

typedef struct{
    char** mapa;
    int linhas;
    int colunas;
}MAPA;


void ler_mapa();
void imprimirmapa();
void imprimirmapa();
void alocar_mapa();
void liberar_mapa();
void encontrar_no_mapa(char objeto, POSICAO *coordenadas);
int tem_objeto(char objeto, int x, int y);
void mover(char direcao);
void PorPartesMapa(POSICAO cabeca);
void teste_posicoes(int numero_posicoes);
void teste_corpo(int numero_posicoes);
void posicao_comidinha();
int ehparede(int x, int y);

#endif