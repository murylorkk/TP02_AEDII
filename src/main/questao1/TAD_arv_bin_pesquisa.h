#ifndef ARVORE_H
#define ARVORE_H

typedef struct no {
    int info; // Para a Tarefa 2, você adicionaria o 'payload' do pacote aqui
    struct no *esq;
    struct no *dir;
} No;

typedef struct {
    No *raiz;
} Arvore;

Arvore* criar_arvore();

void destruir_arvore(No *raiz);

int inserir(Arvore *arv, int valor);

int buscar(Arvore *arv, int valor);

void imprimir_pre_ordem(Arvore *arv);

void imprimir_em_ordem(Arvore *arv);

void imprimir_pos_ordem(Arvore *arv);

#endif