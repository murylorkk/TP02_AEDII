#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "TAD_vetor.h"
#include "TAD_arv_bin_pesquisa.h"
#define TAMANHO 1000000
#define NUM_BUSCAS 30

// função que retorna o tempo atual em segundos como um número decimal de alta precisão.
double get_tempo_em_segundos(){
#ifdef _WIN32                          // verifica se está compilando no windows
    LARGE_INTEGER freq, counter;       // variaveis inteiras de 64 bits no windows
    QueryPerformanceFrequency(&freq);  // pergunta ao hardware: "quantos ticks você conta por segundo?".
    QueryPerformanceCounter(&counter); // lê o valor atual do contador de hardware neste exato instante.
    return (double)counter.QuadPart / freq.QuadPart;
    /*acessa o valor de 64 bits dentro do LARGE_INTEGER. Divide os ticks atuais pela frequência — resultado é o tempo em segundos desde que o sistema ligou.
    Quando você subtrai duas chamadas dessa função, obtém o tempo decorrido entre elas.*/
#else // caso esteja em outro SO
    struct timespec ts;                  // declara uma estrutura com dois campos: tv_sec (segundos inteiros) e tv_nsec (nanossegundos). vai receber o tempo atual.
    clock_gettime(CLOCK_MONOTONIC, &ts); // relógio monotônico do sistema e preenche ts.
    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
#endif
}

int main(){
    inicializar_semente(time(NULL));
    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 1 =-=-=-=-=-=-=-=-=-=-=|\n");

    Arvore_bin *a = criar_arv_bin_pesquisa();
    
    for(int i = 0; i < 20; i++){
        int valor = rand64() % 100;    
        a = inserir_arv_bin_pesquisa(a, valor);
    }

    printf("\n | --- impressao pre-ordem: --- |\n");
    imprimir_pre_ordem(a);
    printf("\n | --- impressao em ordem: --- |\n");
    imprimir_em_ordem(a);
    printf("\n | --- impressao pos-ordem: --- | \n");
    imprimir_pos_ordem(a);

    destruir_arv_bin_pesquisa(a);
    printf("\n");

    //espaço para a questão 2


    // '-'

    int *vetor = criar_vetor(TAMANHO);
    Arvore_bin *arv = criar_arv_bin_pesquisa();
    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 3 =-=-=-=-=-=-=-=-=-=-=|\n");
    printf("1. Gerando %d valores aleatorios...\n", TAMANHO);

    preencher_vetor(vetor, TAMANHO, 10000000);
    printf("2. Inserindo dados na Arvore Binaria de Pesquisa...\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        arv = inserir_arv_bin_pesquisa(arv, obter_elemento(vetor, i));
    }

    printf("3. Ordenando o vetor para a Busca Binaria...\n");
    ordenar_vetor(vetor, TAMANHO);

    printf("4. Sorteando os alvos de busca...\n");
    int alvos[NUM_BUSCAS];

    for (int i = 0; i < 15; i++)
    {
        int indice_aleatorio = rand64() % TAMANHO;
        alvos[i] = obter_elemento(vetor, indice_aleatorio);
    }
    for (int i = 15; i < NUM_BUSCAS; i++)
    {
        alvos[i] = rand64() % 10000000;
    }

    double tempos_arv[NUM_BUSCAS], tempos_vet[NUM_BUSCAS];
    double soma_arv = 0, soma_vet = 0;

    printf("\n--- INICIANDO BUSCAS ---\n");
    for (int i = 0; i < NUM_BUSCAS; i++) {
        int alvo = alvos[i];

        // --- medindo a Árvore ---
        double inicio_arv = get_tempo_em_segundos();
        int achou_arv = buscar_arv_bin_pesquisa(arv, alvo); //busca na arvore binaria de pesquisa
        double fim_arv = get_tempo_em_segundos();
        
        // --- medindo o Vetor ---
        double inicio_vet = get_tempo_em_segundos();
        int achou_vet = busca_binaria(vetor, TAMANHO, alvo); //busca binária 
        double fim_vet = get_tempo_em_segundos();

        // calculando os tempos
        tempos_arv[i] = fim_arv - inicio_arv;
        tempos_vet[i] = fim_vet - inicio_vet;

        soma_arv += tempos_arv[i];
        soma_vet += tempos_vet[i];

        printf("Busca %2d | Alvo: %8d | Arv: %.9fs (%s) | Vet: %.9fs (%s)\n",
               i+1, alvo, 
               tempos_arv[i], achou_arv ? "OK " : "Nao", 
               tempos_vet[i], achou_vet != -1 ? "OK " : "Nao");
    }

    printf("\n--- RESULTADOS GERAIS (Media de %d buscas) ---\n", NUM_BUSCAS);
    printf("Media de tempo Arvore Binaria: %.9f segundos\n", soma_arv / NUM_BUSCAS);
    printf("Media de tempo Busca Binaria:  %.9f segundos\n", soma_vet / NUM_BUSCAS);

    liberar_vetor(vetor);
    destruir_arv_bin_pesquisa(arv);

    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questão 4 =-=-=-=-=-=-=-=-=-=-=|\n");


    return 0;
}