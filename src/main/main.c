#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "TAD_vetor.h"
#include "TAD_arv_bin_pesquisa.h"
#include "TAD_arv_pacotes.h"
#include "TAD_arv_AVL.h"

#define TAMANHO 1000000
#define NUM_BUSCAS 30

double get_tempo_em_segundos() {
#ifdef _WIN32
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
#endif
}

int main() {
    inicializar_semente(time(NULL));

    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 1 =-=-=-=-=-=-=-=-=-=-=|\n");

    Arvore_bin *a = criar_arv_bin_pesquisa();

    for(int i = 0; i < 20; i++) {
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

    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 2 =-=-=-=-=-=-=-=-=-=-=|\n");

    NoPacote* arvore_pacotes = criar_arvore_pacotes();

    Pacote pacotes[] = {
        {3, "terceiro trecho do arquivo. "},
        {1, "Inicio do arquivo. "},
        {5, "Fim da transmissao.\n"},
        {2, "Este e o segundo trecho, "},
        {4, "Penultimo trecho do texto. "},
        {2, "Este e o segundo trecho, "},
        {1, "Inicio do arquivo. "}
    };

    int qtd_pacotes = sizeof(pacotes) / sizeof(pacotes[0]);

    for (int i = 0; i < qtd_pacotes; i++) {
        arvore_pacotes = inserir_pacote(arvore_pacotes, pacotes[i]);
    }

    montar_arquivo(arvore_pacotes, "saida_pacotes.txt");
    liberar_arvore_pacotes(arvore_pacotes);

    printf("Arquivo de pacotes montado e salvo como 'saida_pacotes.txt'.\n");

    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 3 =-=-=-=-=-=-=-=-=-=-=|\n");

    int *vetor = criar_vetor(TAMANHO);
    Arvore_bin *arv = criar_arv_bin_pesquisa();

    printf("1. Gerando %d valores aleatorios...\n", TAMANHO);
    preencher_vetor(vetor, TAMANHO, 10000000);

    printf("2. Inserindo dados na Arvore Binaria de Pesquisa...\n");
    for (int i = 0; i < TAMANHO; i++) {
        arv = inserir_arv_bin_pesquisa(arv, obter_elemento(vetor, i));
    }

    printf("3. Ordenando o vetor para a Busca Binaria...\n");
    ordenar_vetor(vetor, TAMANHO);

    printf("4. Sorteando os alvos de busca...\n");
    int alvos[NUM_BUSCAS];

    for (int i = 0; i < 15; i++) {
        int indice_aleatorio = rand64() % TAMANHO;
        alvos[i] = obter_elemento(vetor, indice_aleatorio);
    }
    for (int i = 15; i < NUM_BUSCAS; i++) {
        alvos[i] = rand64() % 10000000;
    }

    double tempos_arv[NUM_BUSCAS], tempos_vet[NUM_BUSCAS];
    double soma_arv = 0, soma_vet = 0;

    printf("\n--- INICIANDO BUSCAS ---\n");
    for (int i = 0; i < NUM_BUSCAS; i++) {
        int alvo = alvos[i];

        double inicio_arv = get_tempo_em_segundos();
        int achou_arv = buscar_arv_bin_pesquisa(arv, alvo);
        double fim_arv = get_tempo_em_segundos();

        double inicio_vet = get_tempo_em_segundos();
        int achou_vet = busca_binaria(vetor, TAMANHO, alvo);
        double fim_vet = get_tempo_em_segundos();

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

    printf("\n|=-=-=-=-=-=-=-=-=-=-= Questao 4 =-=-=-=-=-=-=-=-=-=-=|\n");

    int num_execucoes = 10;

    int *dados_q4 = (int *)malloc(TAMANHO * sizeof(int));
    int alvos_q4[NUM_BUSCAS];

    if (dados_q4 == NULL){
        printf("Erro de alocacao de memoria para a Questao 4!\n");
        return 1;
    }

    printf("Iniciando %d execucoes para arvores com %d elementos...\n", num_execucoes, TAMANHO);
    printf("--------------------------------------------------------------------------------------\n");
    printf("| Exec | Tempo Cria BST | Altura BST | T. Busca BST | T. Cria AVL | Altura AVL | T. Busca AVL |\n");
    printf("--------------------------------------------------------------------------------------\n");

    for (int e = 0; e < num_execucoes; e++) {
        // preparando dados aleatórios
        for (int i = 0; i < TAMANHO; i++) {
            dados_q4[i] = rand64() % (TAMANHO * 2); 
        }
        
        // escolhendo alvos para busca (garantindo que estão no vetor)
        for (int i = 0; i < NUM_BUSCAS; i++) {
            alvos_q4[i] = dados_q4[rand64() % TAMANHO];
        }

        Arvore_bin *bst = criar_arv_bin_pesquisa();
        
        double inicio = get_tempo_em_segundos();
        for (int i = 0; i < TAMANHO; i++) {
            bst = inserir_arv_bin_pesquisa(bst, dados_q4[i]);
        }
        double tempo_cria_bst = get_tempo_em_segundos() - inicio;
        
        int altura_bst = obter_altura_bin(bst);

        inicio = get_tempo_em_segundos();
        for (int i = 0; i < NUM_BUSCAS; i++) {
            buscar_arv_bin_pesquisa(bst, alvos_q4[i]);
        }
        // Calculando a média das 30 consultas
        double tempo_busca_bst = (get_tempo_em_segundos() - inicio) / NUM_BUSCAS;

        Arvore_AVL *avl = criar_avl();
        
        inicio = get_tempo_em_segundos();
        for (int i = 0; i < TAMANHO; i++) {
            avl = inserir_avl(avl, dados_q4[i]);
        }
        double tempo_cria_avl = get_tempo_em_segundos() - inicio;
        
        int altura_avl = obter_altura_avl(avl);

        inicio = get_tempo_em_segundos();
        for (int i = 0; i < NUM_BUSCAS; i++) {
            buscar_avl(avl, alvos_q4[i]);
        }

        // calculando a média das 30 consultas 
        double tempo_busca_avl = (get_tempo_em_segundos() - inicio) / NUM_BUSCAS;

        printf("| %4d | %11.6fs | %10d | %12.9fs | %11.6fs | %10d | %12.9fs |\n", 
               e + 1, tempo_cria_bst, altura_bst, tempo_busca_bst, tempo_cria_avl, altura_avl, tempo_busca_avl);

        destruir_arv_bin_pesquisa(bst);
        destruir_avl(avl);
    }
    
    printf("--------------------------------------------------------------------------------------\n");

    free(dados_q4);
    return 0;
}