/*
 Desafio: mestre - Sistema de priorização e montagem de componentes
 Implementa: Bubble sort por nome, Insertion sort por tipo, Selection sort por prioridade,
 busca binária por nome (aplicável apenas após ordenação por nome), contagem de comparações,
 e medição de tempo (clock()).

 Autor: Gerado para exercício didático
 Limites: até 20 componentes
 Compilar: gcc -o desafio Desafio_Mestre_Ordenacao_Busca.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];   // ex: "chip central"
    char tipo[MAX_TIPO];   // ex: "controle"
    int prioridade;        // 1 a 10
} Componente;

// --- Prototipos ---
void bubbleSortNome(Componente arr[], int n, long *comparacoes);
void insertionSortTipo(Componente arr[], int n, long *comparacoes);
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes);
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long *comparacoes);
void mostrarComponentes(Componente arr[], int n);

// Wrappers para medir tempo e comparações
typedef void (*SortFunc)(Componente[], int, long *);

double medirTempoSort(SortFunc algoritmo, Componente arr[], int n, long *comparacoes);

// Funções utilitarias
void limparBuffer();
void lerString(char *dest, int tamanho);

// --- Implementacoes ---

// Conta cada chamada a strcmp ou comparacao de int como 1 comparacao
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    int i, j;
    *comparacoes = 0;
    for (i = 0; i < n-1; ++i) {
        for (j = 0; j < n-1-i; ++j) {
            (*comparacoes)++; // comparacao entre nomes
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; ++i) {
        Componente key = arr[i];
        int j = i - 1;
        // desloca enquanto arr[j].tipo > key.tipo
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, key.tipo) > 0) {
                arr[j+1] = arr[j];
                j--;
            } else break;
        }
        arr[j+1] = key;
    }
}

void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i+1; j < n; ++j) {
            (*comparacoes)++; // comparacao entre prioridades
            if (arr[j].prioridade < arr[min_idx].prioridade)
                min_idx = j;
        }
        if (min_idx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

// Busca binaria por nome - assume arr está ordenado por nome ascendente
// Retorna index ou -1 se nao encontrado. Conta comparacoes comparando strings.
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long *comparacoes) {
    int low = 0, high = n - 1;
    *comparacoes = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparacoes)++; // comparacao entre chave e arr[mid].nome
        int cmp = strcmp(chave, arr[mid].nome);
        if (cmp == 0) return mid;
        else if (cmp < 0) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

void mostrarComponentes(Componente arr[], int n) {
    printf("\nLista de componentes (total: %d):\n", n);
    printf("%-3s | %-30s | %-20s | %-9s\n", "#", "Nome", "Tipo", "Prioridade");
    printf("----+--------------------------------+----------------------+-----------\n");
    for (int i = 0; i < n; ++i) {
        printf("%-3d | %-30s | %-20s | %-9d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
}

// mede tempo do algoritmo de ordenacao (em segundos) e preenche comparacoes
// algoritmo deve modificar o array passado (faz copia antes, se necessario)
double medirTempoSort(SortFunc algoritmo, Componente arr[], int n, long *comparacoes) {
    // Faz copia dos dados para que o array original seja preservado pelo chamador, se desejar
    Componente copia[MAX_COMPONENTES];
    for (int i = 0; i < n; ++i) copia[i] = arr[i];

    clock_t inicio = clock();
    algoritmo(copia, n, comparacoes);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return tempo;
}

// --- Utilitarios de IO ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *dest, int tamanho) {
    if (fgets(dest, tamanho, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len-1] == '\n') dest[len-1] = '\0';
        else {
            // Se excedeu, limpar restante
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } else {
        // Em caso de erro, garante string vazia
        dest[0] = '\0';
        limparBuffer();
    }
}

// --- Programa principal com menu interativo ---
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao;
    printf("=== Desafio Mestre: Organização e Montagem da Torre de Fuga ===\n");

    // Entrada dos componentes
    printf("Quantos componentes deseja cadastrar? (1-%d): ", MAX_COMPONENTES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_COMPONENTES) {
        printf("Entrada invalida. Encerrando.\n");
        return 1;
    }
    limparBuffer();

    for (int i = 0; i < n; ++i) {
        printf("\nComponente %d\n", i+1);
        printf("Nome (ex: chip central): ");
        lerString(componentes[i].nome, MAX_NOME);
        printf("Tipo (ex: controle, suporte, propulsao): ");
        lerString(componentes[i].tipo, MAX_TIPO);
        printf("Prioridade (1-10): ");
        if (scanf("%d", &componentes[i].prioridade) != 1) {
            printf("Prioridade invalida. Definindo 1.\n");
            componentes[i].prioridade = 1;
        }
        limparBuffer();
    }

    // Menu de operacoes
    while (1) {
        printf("\n-- Menu --\n");
        printf("1) Ordenar por NOME (Bubble Sort) e mostrar (recomendado para busca binaria)\n");
        printf("2) Ordenar por TIPO (Insertion Sort) e mostrar\n");
        printf("3) Ordenar por PRIORIDADE (Selection Sort) e mostrar\n");
        printf("4) Executar busca binaria por NOME (necessita ordenacao por nome)\n");
        printf("5) Mostrar componentes atual (ordem atual)\n");
        printf("6) Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); printf("Entrada invalida\n"); continue; }
        limparBuffer();

        if (opcao == 6) break;

        long comparacoes = 0;
        double tempo = 0.0;

        if (opcao == 1) {
            // aplica diretamente e mostra resultados (modifica o array)
            clock_t inicio = clock();
            bubbleSortNome(componentes, n, &comparacoes);
            clock_t fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\n[Bubble Sort por NOME] Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
            mostrarComponentes(componentes, n);

        } else if (opcao == 2) {
            clock_t inicio = clock();
            insertionSortTipo(componentes, n, &comparacoes);
            clock_t fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\n[Insertion Sort por TIPO] Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
            mostrarComponentes(componentes, n);

        } else if (opcao == 3) {
            clock_t inicio = clock();
            selectionSortPrioridade(componentes, n, &comparacoes);
            clock_t fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\n[Selection Sort por PRIORIDADE] Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
            mostrarComponentes(componentes, n);

        } else if (opcao == 4) {
            // Busca binaria - pede nome da chave
            char chave[MAX_NOME];
            printf("Insira o nome do componente-chave para busca binaria: ");
            lerString(chave, MAX_NOME);

            // Recomendamos checar se o array está ordenado por nome.
            // Aqui, para garantir correção, vamos criar uma copia ordenada localmente
            Componente copia[MAX_COMPONENTES];
            for (int i = 0; i < n; ++i) copia[i] = componentes[i];
            long compsSort = 0;
            bubbleSortNome(copia, n, &compsSort);

            long compsBusca = 0;
            clock_t inicio = clock();
            int idx = buscaBinariaPorNome(copia, n, chave, &compsBusca);
            clock_t fim = clock();
            double t = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\n[Busca Binaria por NOME]\n");
            printf("Comparacoes (ordenacao local para garantira): %ld | Comparacoes (busca): %ld | Tempo busca: %.6f s\n", compsSort, compsBusca, t);
            if (idx >= 0) {
                printf("Componente-chave encontrado na posicao %d na lista ordenada:\n", idx+1);
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n", copia[idx].nome, copia[idx].tipo, copia[idx].prioridade);
            } else {
                printf("Componente-chave NAO encontrado.\n");
            }

        } else if (opcao == 5) {
            mostrarComponentes(componentes, n);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    printf("\nEncerrando. Boa sorte na fuga da ilha!\n");
    return 0;
}
