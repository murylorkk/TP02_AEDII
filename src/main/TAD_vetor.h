
int busca_sequencial(int *vetor, int tamanho, int alvo);

int busca_binaria(int *vetor, int tamanho, int alvo);

void ordenar_vetor(int *vetor, int tamanho);

int maior(int *vetor, int tamanho);

int menor(int *vetor, int tamanho);

int comparar(const void *a, const void *b);

int *criar_vetor(int tamanho);

void preencher_vetor(int *vetor, int tamanho, int intervalo);

int obter_elemento(int *vetor, int indice);

void liberar_vetor(int *vetor);

void inicializar_semente(unsigned long long s);

unsigned long long rand64();