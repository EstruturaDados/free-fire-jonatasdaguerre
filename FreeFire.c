#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// STRUCTS
// -----------------------------

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// -----------------------------
// CONSTANTES PARA O VETOR
// -----------------------------

#define MAX_ITENS 100
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Contadores
int compSequencialVetor = 0;
int compBinariaVetor = 0;
int compSequencialLista = 0;

// Ponteiro inicial da lista
No* mochilaLista = NULL;

// -----------------------------
// FUNÇÕES DO VETOR
// -----------------------------

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);
    printf("Tipo: ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;

    printf("Item inserido no vetor!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("Item removido do vetor!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarVetor() {
    printf("\n--- Itens no Vetor ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%s | %s | qtd: %d\n",
                mochilaVetor[i].nome,
                mochilaVetor[i].tipo,
                mochilaVetor[i].quantidade);
    }
    printf("-----------------------\n");
}

void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }

    printf("Vetor ordenado por nome!\n");
}

void buscarSequencialVetor() {
    char nome[30];
    compSequencialVetor = 0;

    printf("Nome para buscar: ");
    scanf("%s", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        compSequencialVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd=%d\n",
                   mochilaVetor[i].nome,
                   mochilaVetor[i].tipo,
                   mochilaVetor[i].quantidade);
            printf("Comparacoes: %d\n", compSequencialVetor);
            return;
        }
    }

    printf("Item nao encontrado. Comparacoes: %d\n", compSequencialVetor);
}

void buscarBinariaVetor() {
    char nome[30];
    compBinariaVetor = 0;

    printf("Nome para buscar (binaria): ");
    scanf("%s", nome);

    int inicio = 0;
    int fim = totalItensVetor - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBinariaVetor++;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("Item encontrado: %s (%s), qtd=%d\n",
                   mochilaVetor[meio].nome,
                   mochilaVetor[meio].tipo,
                   mochilaVetor[meio].quantidade);
            printf("Comparacoes: %d\n", compBinariaVetor);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Item nao encontrado. Comparacoes: %d\n", compBinariaVetor);
}

// -----------------------------
// FUNÇÕES DA LISTA ENCADEADA
// -----------------------------

void inserirItemLista() {
    No* novo = malloc(sizeof(No));
    if (!novo) return;

    printf("Nome do item: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    No *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
}

void listarLista() {
    No* aux = mochilaLista;

    printf("\n--- Itens na Lista ---\n");
    while (aux != NULL) {
        printf("%s | %s | qtd: %d\n",
                aux->dados.nome,
                aux->dados.tipo,
                aux->dados.quantidade);
        aux = aux->proximo;
    }
    printf("-----------------------\n");
}

void buscarSequencialLista() {
    char nome[30];
    compSequencialLista = 0;

    printf("Nome para buscar: ");
    scanf("%s", nome);

    No* aux = mochilaLista;

    while (aux != NULL) {
        compSequencialLista++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd=%d\n",
                   aux->dados.nome,
                   aux->dados.tipo,
                   aux->dados.quantidade);
            printf("Comparacoes: %d\n", compSequencialLista);
            return;
        }
        aux = aux->proximo;
    }

    printf("Item nao encontrado. Comparacoes: %d\n", compSequencialLista);
}

// -----------------------------
// MENU PRINCIPAL
// -----------------------------

void menuVetor() {
    int opc;

    do {
        printf("\n--- Mochila (Vetor) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar binaria\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }
    } while (opc != 0);
}

void menuLista() {
    int opc;

    do {
        printf("\n--- Mochila (Lista Encadeada) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4: buscarSequencialLista(); break;
        }
    } while (opc != 0);
}

// -----------------------------
// FUNÇÃO PRINCIPAL
// -----------------------------

int main() {
    int escolha;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1 - Usar vetor\n");
        printf("2 - Usar lista encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) menuVetor();
        else if (escolha == 2) menuLista();

    } while (escolha != 0);

    return 0;
}
