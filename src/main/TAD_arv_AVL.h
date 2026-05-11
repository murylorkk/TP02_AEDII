#ifndef TAD_AVL_H
#define TAD_AVL_H

struct no_avl {
    int info;
    int altura;
    struct no_avl *esq;
    struct no_avl *dir;
};

typedef struct no_avl Arvore_AVL;

Arvore_AVL* criar_avl();

Arvore_AVL* inserir_avl(Arvore_AVL* a, int valor);

int buscar_avl(Arvore_AVL* a, int valor);

int obter_altura_avl(Arvore_AVL* a);

void destruir_avl(Arvore_AVL* a);

#endif