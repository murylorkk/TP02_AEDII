#include "TAD_vetor.h"
#include <stdio.h>
#include <stdlib.h>

int busca_sequencial(int *vetor, int tamanho, int alvo)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] == alvo)
            return i;
    }
    return -1;
}

int busca_binaria(int *vetor, int tamanho, int alvo)
{
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == alvo)
            return meio;
        if (vetor[meio] < alvo)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

int comparar(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void ordenar_vetor(int *vetor, int tamanho)
{
    qsort(vetor, tamanho, sizeof(int), comparar);
}

int maior(int *vetor, int tamanho)
{
    int maior = vetor[0];
    for (unsigned i = 1; i < tamanho; i++)
    {
        if (vetor[i] >= maior)
        {
            maior = vetor[i];
        }
    }
    return maior;
}

int menor(int *vetor, int tamanho)
{
    int menor = vetor[0];
    for (unsigned i = 1; i < tamanho; i++)
    {
        if (vetor[i] <= menor)
        {
            menor = vetor[i];
        }
    }
    return menor;
}

int *criar_vetor(int tamanho)
{
    int *vetor = malloc(tamanho * sizeof(int));
    if(vetor == NULL){
        printf("ERRO DE MEMÓRIA!");
        exit(1);
    }
    return vetor;
}

static unsigned long long semente = 0;

void inicializar_semente(unsigned long long s)
{
    semente = s;
}

unsigned long long rand64()
{
    semente ^= semente << 13;
    semente ^= semente >> 7;
    semente ^= semente << 17;
    return semente;
}

void preencher_vetor(int *vetor, int tamanho, int intervalo)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = (int)(rand64() % intervalo);
    }
}

int obter_elemento(int *vetor, int indice)
{
    return vetor[indice];
}

void liberar_vetor(int *vetor)
{
    free(vetor);
}
