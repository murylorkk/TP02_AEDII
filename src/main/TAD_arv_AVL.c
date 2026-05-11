#include <stdio.h>
#include <stdlib.h>
#include "TAD_arv_AVL.h"

// descobre qual lado da árvore é mais alto
int maior_altura(int alt_esquerda, int alt_direita) {
    if (alt_esquerda > alt_direita) {
        return alt_esquerda;
    } else {
        return alt_direita;
    }
}

// calcula o "peso" do nó. 
// positivo = pesando para esquerda. negativo = pesando para direita.
int fator_balanceamento(Arvore_AVL* no) {
    if (no == NULL) {
        return 0;
    }
    return obter_altura_avl(no->esq) - obter_altura_avl(no->dir);
}

Arvore_AVL* rotacao_direita(Arvore_AVL* raiz_atual) {
    Arvore_AVL* nova_raiz = raiz_atual->esq;
    Arvore_AVL* sub_arvore_meio = nova_raiz->dir;

    //rotação
    nova_raiz->dir = raiz_atual;
    raiz_atual->esq = sub_arvore_meio;

    // Atualiza a altura de quem mudou de lugar (sempre de baixo para cima)
    raiz_atual->altura = maior_altura(obter_altura_avl(raiz_atual->esq), obter_altura_avl(raiz_atual->dir)) + 1;
    nova_raiz->altura  = maior_altura(obter_altura_avl(nova_raiz->esq), obter_altura_avl(nova_raiz->dir)) + 1;

    return nova_raiz;
}

Arvore_AVL* rotacao_esquerda(Arvore_AVL* raiz_atual) {
    Arvore_AVL* nova_raiz = raiz_atual->dir;
    Arvore_AVL* sub_arvore_meio = nova_raiz->esq;

    // rotação
    nova_raiz->esq = raiz_atual;
    raiz_atual->dir = sub_arvore_meio;

    // Atualiza a altura de quem mudou de lugar
    raiz_atual->altura = maior_altura(obter_altura_avl(raiz_atual->esq), obter_altura_avl(raiz_atual->dir)) + 1;
    nova_raiz->altura  = maior_altura(obter_altura_avl(nova_raiz->esq), obter_altura_avl(nova_raiz->dir)) + 1;

    return nova_raiz;
}

Arvore_AVL* criar_avl() {
    return NULL;
}

int obter_altura_avl(Arvore_AVL* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

Arvore_AVL* inserir_avl(Arvore_AVL* no, int valor) {
    // PASSO 1: Inserção normal (igual a árvore binária de pesquisa)
    if (no == NULL) {
        Arvore_AVL* novo_no = (Arvore_AVL*) malloc(sizeof(Arvore_AVL));
        novo_no->info = valor;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->altura = 1; // todo nó novo nasce como folha, logo tem altura 1
        return novo_no;
    }

    if (valor < no->info) {
        no->esq = inserir_avl(no->esq, valor);
    } 
    else if (valor > no->info) {
        no->dir = inserir_avl(no->dir, valor);
    } 
    else {
        return no; // Se o valor já existe, não fazemos nada
    }

    // atulizando a altura deste ancestral
    no->altura = 1 + maior_altura(obter_altura_avl(no->esq), obter_altura_avl(no->dir));

    // verificar se a árvore está balanceada
    int peso = fator_balanceamento(no);

    // balancear a árvore se necessário (casos de Rotação)

    // caso 1: pesado demais na esquerda, e o filho foi para a esquerda
    if (peso > 1 && valor < no->esq->info) {
        return rotacao_direita(no);
    }

    // Caso 2: Pesado demais na Direita, e o filho foi para a Direita
    if (peso < -1 && valor > no->dir->info) {
        return rotacao_esquerda(no);
    }

    // Caso 3: Pesado na Esquerda, mas o filho foi para a Direita ("Joelho" à esquerda)
    if (peso > 1 && valor > no->esq->info) {
        no->esq = rotacao_esquerda(no->esq); // Alinha tudo para a esquerda
        return rotacao_direita(no);          // Rotaciona para a direita
    }

    // Caso 4: Pesado na Direita, mas o filho foi para a Esquerda ("Joelho" à direita)
    if (peso < -1 && valor < no->dir->info) {
        no->dir = rotacao_direita(no->dir);  // Alinha tudo para a direita
        return rotacao_esquerda(no);         // Rotaciona para a esquerda
    }

    // Se chegou até aqui, a árvore continuou balanceada, só devolve o nó!
    return no;
}

int buscar_avl(Arvore_AVL* no, int valor) {
    while (no != NULL) {
        if (valor == no->info) {
            return 1; // Achou
        }
        if (valor < no->info) {
            no = no->esq;
        } else {
            no = no->dir;
        }
    }
    return 0; // Não achou
}

void destruir_avl(Arvore_AVL* no) {
    if (no != NULL) {
        destruir_avl(no->esq);
        destruir_avl(no->dir);
        free(no);
    }
}