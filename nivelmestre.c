/*
  nivel3_mestre.c
  Nível Mestre - Torre de Resgate
  - Implementa Bubble Sort (nome), Insertion Sort (tipo), Selection Sort (prioridade)
  - Mede comparações e tempo (clock)
  - Busca binária por nome (após ordenar por nome)
  - Cadastro de até 20 componentes (fgets para strings)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define NOME_TAM 30
#define TIPO_TAM 20

/* Estrutura principal: Componente */
typedef struct {
    char nome[NOME_TAM];
    char tipo[TIPO_TAM];
    int prioridade; // 1 (mais alta) .. 10 (mais baixa)
} Componente;

/* Assinaturas das funções exigidas */
void bubbleSortNome(Componente arr[], int n, long long *comparacoes);
void insertionSortTipo(Componente arr[], int n, long long *comparacoes);
void selectionSortPrioridade(Componente arr[], int n, long long *comparacoes);
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long long *comparacoes);

// Funções utilitárias
void mostrarComponentes(Componente arr[], int n);
void limparBuffer(void);
void lerStringSeguro(char *buffer, int tamanho);
void copiarVetores(Componente destino[], Componente origem[], int n);

/* Função que mede tempo de execução de um algoritmo de ordenação
   O tipo SortFunc é um ponteiro para função que recebe (Componente[], int, long long*)
*/
typedef void (*SortFunc)(Componente[], int, long long*);
void medirTempo(SortFunc algoritmo, Componente arr[], int n, long long *comparacoes, double *tempo_seg) {
    clock_t inicio = clock();
    *comparacoes = 0;
    algoritmo(arr, n, comparacoes);
    clock_t fim = clock();
    *tempo_seg = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/* ---------------------------
   IMPLEMENTAÇÕES DOS ALGORITMOS
   --------------------------- */

/* Bubble Sort por nome (ordena em ordem lexicográfica crescente)
   conta comparações entre nomes usando strcmp */
void bubbleSortNome(Componente arr[], int n, long long *comparacoes) {
    Componente tmp;
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização clássica
    }
}

/* Insertion Sort por tipo (ordena por campo tipo lexicograficamente) */
void insertionSortTipo(Componente arr[], int n, long long *comparacoes) {
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

/* Selection Sort por prioridade (ordena em ordem crescente: 1 .. 10)
   prioritário: menor valor = maior prioridade */
void selectionSortPrioridade(Componente arr[], int n, long long *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        int idx_min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j].prioridade < arr[idx_min].prioridade) {
                idx_min = j;
            }
        }
        if (idx_min != i) {
            Componente tmp = arr[i];
            arr[i] = arr[idx_min];
            arr[idx_min] = tmp;
        }
    }
}

/* Busca binária por nome: assume arr está ordenado por nome (lexicográfico).
   Retorna índice se encontrado, -1 caso contrário. Conta comparações entre nomes. */
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long long *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* ---------------------------
   UTILITÁRIOS DE I/O
   --------------------------- */

/* Mostra vetor de componentes formatado */
void mostrarComponentes(Componente arr[], int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes (total: %d) ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("[%2d] Nome: %-28s | Tipo: %-12s | Prioridade: %d\n",
               i + 1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("-------------------------------\n");
}

/* Limpa buffer residual do stdin */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Lê uma string com fgets e remove '\n' ao final */
void lerStringSeguro(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

/* Copia vetor origem para destino (útil para comparar algoritmos sem perder original) */
void copiarVetores(Componente destino[], Componente origem[], int n) {
    for (int i = 0; i < n; i++) destino[i] = origem[i];
}

/* ---------------------------
   MENU E FLUXO PRINCIPAL
   --------------------------- */

int main(void) {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao;

    printf("=== NÍVEL MESTRE: TORRE DE RESGATE ===\n");
    printf("Cadastre até %d componentes (nome, tipo, prioridade 1..10).\n", MAX_COMPONENTES);

    /* Entrada dos componentes */
    do {
        if (n >= MAX_COMPONENTES) {
            printf("\nLimite de componentes atingido (%d).\n", MAX_COMPONENTES);
            break;
        }
        printf("\nDeseja cadastrar um componente? (1-Sim / 0-Não): ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); break; }
        limparBuffer();
        if (opcao == 0) break;

        printf("Nome do componente: ");
        lerStringSeguro(componentes[n].nome, NOME_TAM);

        printf("Tipo do componente (ex: controle, suporte, propulsao): ");
        lerStringSeguro(componentes[n].tipo, TIPO_TAM);

        int pri = 0;
        do {
            printf("Prioridade (1 a 10) - 1 = mais alta: ");
            if (scanf("%d", &pri) != 1) { limparBuffer(); pri = 0; }
            limparBuffer();
            if (pri < 1 || pri > 10) printf("Prioridade inválida. Tente novamente.\n");
        } while (pri < 1 || pri > 10);
        componentes[n].prioridade = pri;
        n++;
    } while (1);

    if (n == 0) {
        printf("\nNenhum componente cadastrado. Encerrando.\n");
        return 0;
    }

    /* Menu principal de escolhas de ordenação e busca */
    int sair = 0;
    while (!sair) {
        printf("\n=== Menu Mestre ===\n");
        printf("1 - Mostrar componentes\n");
        printf("2 - Ordenar por NOME (Bubble Sort) e medir (recomendado para busca binária)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort) e medir\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort) e medir\n");
        printf("5 - Comparar todos os algoritmos (executa cada um em cópia e mostra comparações/tempos)\n");
        printf("6 - Buscar componente-chave por NOME (busca binária) - exige ordenação por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); break; }
        limparBuffer();

        if (opcao == 1) {
            mostrarComponentes(componentes, n);
        } else if (opcao == 2) {
            Componente copia[MAX_COMPONENTES];
            copiarVetores(copia, componentes, n);
            long long comps = 0;
            double tempo = 0.0;
            medirTempo(bubbleSortNome, copia, n, &comps, &tempo);
            printf("\nResultado: Bubble Sort por NOME\n");
            printf("Comparações: %lld\n", comps);
            printf("Tempo: %.6f s\n", tempo);
            mostrarComponentes(copia, n);

            /* Perguntar se usuário quer sobrescrever o vetor original */
            printf("Deseja substituir a ordem atual pelos dados ordenados por nome? (1-Sim / 0-Não): ");
            int r; if (scanf("%d", &r) == 1 && r == 1) {
                limparBuffer();
                copiarVetores(componentes, copia, n);
                printf("Vetor original atualizado com ordenação por nome.\n");
            } else limparBuffer();
        } else if (opcao == 3) {
            Componente copia[MAX_COMPONENTES];
            copiarVetores(copia, componentes, n);
            long long comps = 0;
            double tempo = 0.0;
            medirTempo(insertionSortTipo, copia, n, &comps, &tempo);
            printf("\nResultado: Insertion Sort por TIPO\n");
            printf("Comparações: %lld\n", comps);
            printf("Tempo: %.6f s\n", tempo);
            mostrarComponentes(copia, n);

            printf("Deseja substituir a ordem atual pelos dados ordenados por tipo? (1-Sim / 0-Não): ");
            int r; if (scanf("%d", &r) == 1 && r == 1) {
                limparBuffer();
                copiarVetores(componentes, copia, n);
                printf("Vetor original atualizado com ordenação por tipo.\n");
            } else limparBuffer();
        } else if (opcao == 4) {
            Componente copia[MAX_COMPONENTES];
            copiarVetores(copia, componentes, n);
            long long comps = 0;
            double tempo = 0.0;
            medirTempo(selectionSortPrioridade, copia, n, &comps, &tempo);
            printf("\nResultado: Selection Sort por PRIORIDADE (1 = mais alta)\n");
            printf("Comparações: %lld\n", comps);
            printf("Tempo: %.6f s\n", tempo);
            mostrarComponentes(copia, n);

            printf("Deseja substituir a ordem atual pelos dados ordenados por prioridade? (1-Sim / 0-Não): ");
            int r; if (scanf("%d", &r) == 1 && r == 1) {
                limparBuffer();
                copiarVetores(componentes, copia, n);
                printf("Vetor original atualizado com ordenação por prioridade.\n");
            } else limparBuffer();
        } else if (opcao == 5) {
            /* Executa e mostra resultados comparativos */
            Componente c1[MAX_COMPONENTES], c2[MAX_COMPONENTES], c3[MAX_COMPONENTES];
            copiarVetores(c1, componentes, n);
            copiarVetores(c2, componentes, n);
            copiarVetores(c3, componentes, n);

            long long comps1 = 0, comps2 = 0, comps3 = 0;
            double t1 = 0, t2 = 0, t3 = 0;
            medirTempo(bubbleSortNome, c1, n, &comps1, &t1);
            medirTempo(insertionSortTipo, c2, n, &comps2, &t2);
            medirTempo(selectionSortPrioridade, c3, n, &comps3, &t3);

            printf("\n--- Comparação de algoritmos ---\n");
            printf("Bubble Sort (nome): Comparações=%lld | Tempo=%.6f s\n", comps1, t1);
            printf("Insertion Sort (tipo): Comparações=%lld | Tempo=%.6f s\n", comps2, t2);
            printf("Selection Sort (prioridade): Comparações=%lld | Tempo=%.6f s\n", comps3, t3);
            printf("--------------------------------\n");
            printf("Obs: cada algoritmo foi executado em cópia do vetor original (ordem preservada).\n");
        } else if (opcao == 6) {
            /* Busca binária: verifica se o vetor está ordenado por nome plausivelmente.
               Simples verificação: comparar componente i com i+1; se estiver ordenado lexicograficamente,
               prossegue; caso contrário avisar ao usuário. */
            int ordenadoPorNome = 1;
            for (int i = 0; i < n - 1; i++) {
                if (strcmp(componentes[i].nome, componentes[i+1].nome) > 0) {
                    ordenadoPorNome = 0;
                    break;
                }
            }
            if (!ordenadoPorNome) {
                printf("\nATENÇÃO: o vetor atual NÃO está ordenado por nome.\n");
                printf("Deseja ordenar agora por nome (Bubble Sort) antes da busca binária? (1-Sim / 0-Não): ");
                int r; if (scanf("%d", &r) == 1 && r == 1) {
                    limparBuffer();
                    long long comps = 0;
                    double t = 0;
                    medirTempo(bubbleSortNome, componentes, n, &comps, &t);
                    printf("Vetor ordenado por nome. Comparações=%lld | Tempo=%.6f s\n", comps, t);
                } else {
                    limparBuffer();
                    printf("Busca binária cancelada (requer vetor ordenado por nome).\n");
                    continue;
                }
            }

            char chave[NOME_TAM];
            printf("Digite o NOME do componente-chave a buscar (busca binária): ");
            lerStringSeguro(chave, NOME_TAM);
            long long compsBusca = 0;
            int idx = buscaBinariaPorNome(componentes, n, chave, &compsBusca);
            if (idx >= 0) {
                printf("\nComponente-chave encontrado no índice %d:\n", idx);
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                       componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                printf("Comparações na busca binária: %lld\n", compsBusca);
                printf("\n✅ ATIVAÇÃO: componente presente. Pode iniciar montagem da torre.\n");
            } else {
                printf("\n❌ Componente-chave não localizado.\n");
                printf("Comparações na busca binária: %lld\n", compsBusca);
            }
        } else if (opcao == 0) {
            sair = 1;
            printf("\nEncerrando módulo Mestre. Boa fuga!\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
