#include "TAD_arv_pacotes.h"

struct NoPacote {
    Pacote pacote;
    struct NoPacote* esq;
    struct NoPacote* dir;
};

NoPacote* criar_arvore_pacotes() {
    return NULL;
}

NoPacote* inserir_pacote(NoPacote* raiz, Pacote p) {
    if (raiz == NULL) {
        NoPacote* novo = (NoPacote*)malloc(sizeof(NoPacote));
        if (novo == NULL) {
            exit(EXIT_FAILURE);
        }
        novo->pacote = p;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (p.id < raiz->pacote.id) {
        raiz->esq = inserir_pacote(raiz->esq, p);
    } else if (p.id > raiz->pacote.id) {
        raiz->dir = inserir_pacote(raiz->dir, p);
    }

    return raiz;
}

static void in_order_arquivo(NoPacote* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        in_order_arquivo(raiz->esq, arquivo);
        fprintf(arquivo, "%s", raiz->pacote.conteudo);
        in_order_arquivo(raiz->dir, arquivo);
    }
}

void montar_arquivo(NoPacote* raiz, const char* nome_arquivo) {
    if (raiz == NULL || nome_arquivo == NULL) {
        return;
    }

    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        return;
    }

    in_order_arquivo(raiz, arquivo);
    fclose(arquivo);
}

void liberar_arvore_pacotes(NoPacote* raiz) {
    if (raiz != NULL) {
        liberar_arvore_pacotes(raiz->esq);
        liberar_arvore_pacotes(raiz->dir);
        free(raiz);
    }
}