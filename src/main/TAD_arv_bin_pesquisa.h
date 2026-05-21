#ifndef ARVORE_H
#define ARVORE_H

struct arvore_bin {
    int info;
    struct arvore_bin* esq;
    struct arvore_bin* dir;
};
typedef struct arvore_bin Arvore_bin;

Arvore_bin* criar_arv_bin_pesquisa();

void destruir_arv_bin_pesquisa(Arvore_bin* a);

Arvore_bin* inserir_arv_bin_pesquisa(Arvore_bin* a, int valor);

int buscar_arv_bin_pesquisa(Arvore_bin* a, int valor);

int obter_altura_bin(Arvore_bin* no);

void imprimir_pre_ordem(Arvore_bin* a);

void imprimir_em_ordem(Arvore_bin* a);

void imprimir_pos_ordem(Arvore_bin* a);

#endif