#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // quantidade máxima de itens na mochila

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções
void inserirItem(Item itens[], int *qtd);
void removerItem(Item itens[], int *qtd);
void listarItens(Item itens[], int qtd);
void buscarItem(Item itens[], int qtd);

// Função principal (menu)
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    printf("===== JOGO DE SOBREVIVENCIA: MOCHILA INICIAL =====\n");

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 3:
                buscarItem(mochila, qtd);
                break;
            case 4:
                listarItens(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo... boa sorte na ilha!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ---------- FUNÇÕES ----------

// Função para inserir item
void inserirItem(Item itens[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove '\n'

    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    itens[*qtd] = novo;
    (*qtd)++;

    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover item
void removerItem(Item itens[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia! Nada para remover.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(itens[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    for (int i = encontrado; i < *qtd - 1; i++) {
        itens[i] = itens[i + 1];
    }

    (*qtd)--;
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// Função para listar itens
void listarItens(Item itens[], int qtd) {
    printf("\n===== ITENS NA MOCHILA =====\n");
    if (qtd == 0) {
        printf("Mochila vazia!\n");
    } else {
        for (int i = 0; i < qtd; i++) {
            printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                   i + 1, itens[i].nome, itens[i].tipo, itens[i].quantidade);
        }
    }
    printf("============================\n");
}

// Função para buscar item (busca sequencial)
void buscarItem(Item itens[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia! Nada para buscar.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(itens[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   itens[i].nome, itens[i].tipo, itens[i].quantidade);
            encontrado = 1;
            break;
        }
    }1

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nome);
    }
}
