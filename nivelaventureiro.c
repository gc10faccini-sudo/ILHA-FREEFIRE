#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ==============================
// STRUCTS PRINCIPAIS
// ==============================

// Representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==============================
// VARIÁVEIS GLOBAIS
// ==============================
int compSequencial = 0;
int compBinaria = 0;

// ==============================
// FUNÇÕES PARA VETOR
// ==============================

// Inserir item no vetor
void inserirItemVetor(Item mochila[], int *tamanho) {
    if (*tamanho >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*tamanho] = novo;
    (*tamanho)++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// Remover item do vetor
void removerItemVetor(Item mochila[], int *tamanho, char nome[]) {
    int encontrado = 0;
    for (int i = 0; i < *tamanho; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *tamanho - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*tamanho)--;
            encontrado = 1;
            printf("\n🗑️ Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) printf("\n❌ Item não encontrado.\n");
}

// Listar todos os itens do vetor
void listarVetor(Item mochila[], int tamanho) {
    if (tamanho == 0) {
        printf("\n⚠️ Mochila vazia.\n");
        return;
    }
    printf("\n📦 Itens na mochila (vetor):\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item mochila[], int tamanho, char nome[]) {
    compSequencial = 0;
    for (int i = 0; i < tamanho; i++) {
        compSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("\n❌ Item não encontrado.\n");
    return -1;
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor(Item mochila[], int tamanho) {
    Item temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\n✅ Mochila ordenada por nome!\n");
}

// Busca binária no vetor
int buscarBinariaVetor(Item mochila[], int tamanho, char nome[]) {
    int inicio = 0, fim = tamanho - 1, meio;
    compBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        compBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\n🔍 Item encontrado (busca binária)!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n❌ Item não encontrado (busca binária).\n");
    return -1;
}

// ==============================
// FUNÇÕES PARA LISTA ENCADEADA
// ==============================

No* inserirItemLista(No* inicio) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nErro de alocação!\n");
        return inicio;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    printf("\n✅ Item adicionado à lista!\n");
    return novo;
}

No* removerItemLista(No* inicio, char nome[]) {
    No *atual = inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n❌ Item não encontrado.\n");
        return inicio;
    }

    if (anterior == NULL) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\n🗑️ Item removido da lista!\n");
    return inicio;
}

void listarLista(No* inicio) {
    if (inicio == NULL) {
        printf("\n⚠️ Lista vazia.\n");
        return;
    }

    printf("\n📦 Itens na mochila (lista encadeada):\n");
    No* aux = inicio;
    while (aux != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

No* buscarSequencialLista(No* inicio, char nome[]) {
    compSequencial = 0;
    No* aux = inicio;
    while (aux != NULL) {
        compSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("\n🔍 Item encontrado na lista!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            return aux;
        }
        aux = aux->proximo;
    }
    printf("\n❌ Item não encontrado na lista.\n");
    return NULL;
}

// ==============================
// MENUS
// ==============================

void menuVetor() {
    Item mochila[MAX_ITENS];
    int tamanho = 0, opcao;
    char nome[30];

    do {
        printf("\n===== MOCHILA (VETOR) =====\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n");
        printf("4. Buscar sequencial\n5. Ordenar\n6. Buscar binária\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItemVetor(mochila, &tamanho); break;
            case 2:
                printf("Nome do item a remover: ");
                scanf(" %[^\n]", nome);
                removerItemVetor(mochila, &tamanho, nome);
                break;
            case 3: listarVetor(mochila, tamanho); break;
            case 4:
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                buscarSequencialVetor(mochila, tamanho, nome);
                printf("Comparações: %d\n", compSequencial);
                break;
            case 5: ordenarVetor(mochila, tamanho); break;
            case 6:
                printf("Nome do item a buscar (binária): ");
                scanf(" %[^\n]", nome);
                buscarBinariaVetor(mochila, tamanho, nome);
                printf("Comparações: %d\n", compBinaria);
                break;
        }
    } while (opcao != 0);
}

void menuLista() {
    No* inicio = NULL;
    int opcao;
    char nome[30];

    do {
        printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n");
        printf("4. Buscar item\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inicio = inserirItemLista(inicio); break;
            case 2:
                printf("Nome do item a remover: ");
                scanf(" %[^\n]", nome);
                inicio = removerItemLista(inicio, nome);
                break;
            case 3: listarLista(inicio); break;
            case 4:
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                buscarSequencialLista(inicio, nome);
                printf("Comparações: %d\n", compSequencial);
                break;
        }
    } while (opcao != 0);
}

// ==============================
// FUNÇÃO PRINCIPAL
// ==============================

int main() {
    int escolha;
    do {
        printf("\n=== NIVEL AVENTUREIRO ===\n");
        printf("1. Usar mochila com VETOR\n");
        printf("2. Usar mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
        }
    } while (escolha != 0);

    printf("\n🏁 Fim do jogo. Mochila fechada!\n");
    return 0;
}
