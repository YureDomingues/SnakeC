#ifndef _MAPA_H
#define _MAPA_H

#define PAREDE_HORIZONTAL '-'
#define PAREDE_VERTICAL '|'
#define ESPACO '.'

typedef struct Posicao{
    int x;
    int y;
}Posicao;

typedef struct Mapa{
    char** mapa;
    int linhas;
    int colunas;
}Mapa;


void ler_mapa(void);
void imprimir_mapa(void);
void imprimir_mapa(void);
void alocar_mapa(void);
void liberar_mapa(void);
void encontrar_no_mapa(char objeto, Posicao *coordenadas);
int tem_objeto(char objeto, int x, int y);
void mover(char direcao);
void PorPartesMapa(Posicao cabeca);
void teste_posicoes(int numero_posicoes);
void teste_corpo(int numero_posicoes);
void posicao_comidinha();
int eh_parede(int x, int y);

#endif