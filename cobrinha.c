#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobrinha.h"
#include "mapa.h"

MAPA m;
COBRA cobra;
POSICAO comidinha;

int terminou = 0;

void inicializar_partes(){
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
        printf("Foi de comes e bebes x.x\n");

    }
}

int direcao_valida(char direcao){
    return (direcao == CIMA || direcao == BAIXO || direcao == DIREITA || direcao == ESQUERDA);
}

void spawn_objeto(char objeto){

    srand(time(NULL));

    POSICAO aleatoria;
    
    do{
        aleatoria.x = rand()%m.linhas;
        aleatoria.y = rand()%m.colunas;
    }while(!tem_objeto(ESPACO, aleatoria.x, aleatoria.y));

    m.mapa[aleatoria.x][aleatoria.y] = objeto;

}

int ehParteCorpo(int parte){
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

void colocar_vazio(POSICAO cabeca){

    POSICAO possiveis[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(int i=0; i<4; i++){
        int pos_valida = !ehparede(cabeca.x + possiveis[i].x, cabeca.y + possiveis[i].y);
        
        if(pos_valida){
            cobra.pos_partes[cobra.tam_calda+1].x = cabeca.x + possiveis[i].x;
            cobra.pos_partes[cobra.tam_calda+1].y = cabeca.y + possiveis[i].y;
        }

    }
}



int main(){

    ler_mapa();
    spawn_objeto(CABECA_COBRA);
    spawn_objeto(COMIDINHA);

    inicializar_partes();

    encontrar_no_mapa(CABECA_COBRA, &cobra.pos_partes[0]);
    
    do{
        imprimirmapa();
        char comando;
        scanf("%c", &comando); 
        mover(comando);
        
        
    }while(!terminou);

    printf("oi");
    
    liberar_mapa();
    
    return EXIT_SUCCESS;
}