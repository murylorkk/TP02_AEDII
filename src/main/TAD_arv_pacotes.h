#ifndef TAD_ARV_PACOTES_H
#define TAD_ARV_PACOTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pacote {
    int id;
    char conteudo[512];
} Pacote;

typedef struct NoPacote NoPacote;

NoPacote* criar_arvore_pacotes();
NoPacote* inserir_pacote(NoPacote* raiz, Pacote p);
void montar_arquivo(NoPacote* raiz, const char* nome_arquivo);
void liberar_arvore_pacotes(NoPacote* raiz);

#endif