#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ------------------------------------------------------------
// Struct que representa um item do inventário
// ------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ------------------------------------------------------------
// Funções do sistema
// ------------------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// ------------------------------------------------------------
// Função principal
// ------------------------------------------------------------
int main() {

    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTARIO =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;

            case 2:
                removerItem(mochila, &total);
                break;

            case 3:
                listarItens(mochila, total);
                break;

            case 4:
                buscarItem(mochila, total);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ------------------------------------------------------------
// Inserção de item
// ------------------------------------------------------------
void inserirItem(Item mochila[], int *total) {

    if (*total >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, ferramenta...): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
    listarItens(mochila, *total);
}

// ------------------------------------------------------------
// Remoção de item
// ------------------------------------------------------------
void removerItem(Item mochila[], int *total) {

    if (*total == 0) {
        printf("\nNao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    int encontrado = -1;

    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("\nItem removido com sucesso!\n");
    listarItens(mochila, *total);
}

// ------------------------------------------------------------
// Listagem de itens da mochila
// ------------------------------------------------------------
void listarItens(Item mochila[], int total) {

    printf("\n===== ITENS NA MOCHILA =====\n");

    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// ------------------------------------------------------------
// Busca sequencial
// ------------------------------------------------------------
void buscarItem(Item mochila[], int total) {

    if (total == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    char nomeBuscar[30];

    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}
