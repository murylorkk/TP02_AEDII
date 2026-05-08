#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TAD_arv_bin_pesquisa.h"

int main(){
    int contador = 0;
    srand(time(NULL));

    Arvore *a = criar_arvore();
    for(int i = 0; i < 20; i++){
        int valor = rand() % 100;    
        inserir(a, valor);
    }

    printf("\n | --- impressao pre-ordem: --- |\n");
    imprimir_pre_ordem(a);
    printf("\n | --- impressao em ordem: --- |\n");
    imprimir_em_ordem(a);
    printf("\n | --- impressao pos-ordem: --- | \n");
    imprimir_pos_ordem(a);
}