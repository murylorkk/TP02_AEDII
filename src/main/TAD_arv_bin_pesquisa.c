#include <stdio.h>
#include <stdlib.h>
#include "TAD_arv_bin_pesquisa.h"

Arvore_bin* criar_arv_bin_pesquisa(){
    return NULL;  //cria arvore vazia
}

void destruir_arv_bin_pesquisa(Arvore_bin* a) {
    if (a != NULL) {
        destruir_arv_bin_pesquisa(a->esq); // destrói os filhos da esquerda
        destruir_arv_bin_pesquisa(a->dir); // destrói os filhos da direita
        free(a);                 // libera o nó atual da memória
    }
}

Arvore_bin* inserir_arv_bin_pesquisa(Arvore_bin* a, int valor) {
    if (a == NULL) {
        a = (Arvore_bin*) malloc(sizeof(Arvore_bin));
        a->info = valor;
        a->esq = a->dir = NULL;
    }
    else if (valor < a->info) {
        a->esq = inserir_arv_bin_pesquisa(a->esq, valor);
    }
    else if (valor > a->info) {
        a->dir = inserir_arv_bin_pesquisa(a->dir, valor);
    }
    return a;
}

int buscar_arv_bin_pesquisa(Arvore_bin* arv, int valor){
    if (arv == NULL){
        return 0;
    }

    if (arv->info == valor){
        return 1;
    }

    if (valor < arv->info){
        return buscar_arv_bin_pesquisa(arv->esq, valor);
    }
    else{
        return buscar_arv_bin_pesquisa(arv->dir, valor);
    }
}

void imprimir_em_ordem(Arvore_bin *arv){
    if (arv != NULL){
        imprimir_em_ordem(arv->esq);
        printf("%d ", arv->info);
        imprimir_em_ordem(arv->dir);
    }
}

void imprimir_pre_ordem(Arvore_bin *arv){
    if (arv != NULL){
        printf("%d ", arv->info);
        imprimir_pre_ordem(arv->esq);
        imprimir_pre_ordem(arv->dir);
    }
}

void imprimir_pos_ordem(Arvore_bin *arv){
    if (arv != NULL){
        imprimir_pos_ordem(arv->esq);
        imprimir_pos_ordem(arv->dir);
        printf("%d ", arv->info);
    }
}
