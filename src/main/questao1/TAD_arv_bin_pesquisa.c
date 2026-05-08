#include <stdio.h>
#include <stdlib.h>
#include "TAD_arv_bin_pesquisa.h"

Arvore* criar_arvore() {
    Arvore *arv = (Arvore*) malloc(sizeof(Arvore));
    if (arv != NULL) {
        arv->raiz = NULL;
    }
    return arv;
}

int inserir(Arvore *arv, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    if (arv->raiz == NULL) {
        arv->raiz = novo;
        return 1;
    }

    No *atual = arv->raiz;
    No *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (valor == atual->info) {
            free(novo);
            return 0; 
        }
        if (valor < atual->info) atual = atual->esq;
        else atual = atual->dir;
    }

    if (valor < pai->info) pai->esq = novo;
    else pai->dir = novo;

    return 1;
}

void recursiva_em_ordem(No* raiz){
    if(raiz != NULL){
        recursiva_em_ordem(raiz->esq);
        printf("%d ", raiz->info);
        recursiva_em_ordem(raiz->dir);
    }
}

void imprimir_em_ordem(Arvore *arv){
    if(arv != NULL){
        recursiva_em_ordem(arv->raiz);
    }
}

void recursiva_pre_ordem(No *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->info);
        recursiva_pre_ordem(raiz->esq);
        recursiva_pre_ordem(raiz->dir);
    }
}

void imprimir_pre_ordem(Arvore *arv){
    if(arv != NULL){
        recursiva_pre_ordem(arv->raiz);
    }
}

void recursiva_pos_ordem(No *raiz){
    if(raiz != NULL){
        recursiva_pos_ordem(raiz->esq);
        recursiva_pos_ordem(raiz->dir);
        printf("%d ", raiz->info);
    }

}


void imprimir_pos_ordem(Arvore *arv){
    if(arv != NULL){
        recursiva_pos_ordem(arv->raiz);
    }
}


