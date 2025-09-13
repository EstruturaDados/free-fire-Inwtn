#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enum para critérios de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

// Variável global para indicar o critério atual de ordenação
CriterioOrdenacao criterioAtual = 0;

// Função para comparar dois itens conforme critério
int compararItens(const Item *a, const Item *b, CriterioOrdenacao criterio) {
    switch (criterio) {
        case ORDENAR_NOME:
            return strcmp(a->nome, b->nome);
        case ORDENAR_TIPO:
            return strcmp(a->tipo, b->tipo);
        case ORDENAR_PRIORIDADE:
            // Ordem crescente de prioridade (1 menor que 5)
            return a->prioridade - b->prioridade;
        default:
            return 0;
    }
}

// Função para adicionar item com prioridade
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item: ");
    getchar(); // limpar buffer
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    do {
        printf("Digite a prioridade do item (1 a 5): ");
        scanf("%d", &novoItem.prioridade);
        if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
            printf("Prioridade invalida! Deve ser entre 1 e 5.\n");
        }
    } while (novoItem.prioridade < 1 || novoItem.prioridade > 5);

    mochila[totalItens++] = novoItem;
    criterioAtual = 0; // lista não está ordenada após inserção
    printf("Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    getchar();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    criterioAtual = 0; // lista pode estar desordenada após remoção
    printf("Item removido com sucesso!\n");
}

// Função para listar itens em tabela
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n%-30s %-20s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d %-10d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// Função para ordenar a mochila pelo critério escolhido usando insertion sort
void ordenarMochila() {
    if (totalItens < 2) {
        printf("Itens insuficientes para ordenar.\n");
        return;
    }

    printf("Escolha o criterio de ordenacao:\n");
    printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n");
    printf("Opcao: ");
    int opcao;
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 3) {
        printf("Opcao invalida.\n");
        return;
    }

    CriterioOrdenacao criterio = (CriterioOrdenacao)opcao;
    int comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        // Compara e desloca itens maiores para direita
        while (j >= 0 && compararItens(&mochila[j], &chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = chave;
        comparacoes++;
    }

    criterioAtual = criterio;
    printf("Mochila ordenada por %s com %d comparacoes.\n",
           (criterio == ORDENAR_NOME) ? "nome" :
           (criterio == ORDENAR_TIPO) ? "tipo" : "prioridade",
           comparacoes);
}

// Função para busca binária por nome
void buscaBinariaPorNome() {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    if (criterioAtual != ORDENAR_NOME) {
        printf("A mochila precisa estar ordenada por nome para realizar a busca binaria.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item para busca binaria: ");
    getchar();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0, fim = totalItens - 1;
    int comparacoes = 0;
    bool encontrado = false;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
    printf("Comparacoes realizadas na busca binaria: %d\n", comparacoes);
}

int main() {
    int opcao;

    do {
        printf("\n=== Menu da Mochila Virtual - Nivel Mestre ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Buscar item por nome (busca binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                ordenarMochila();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("Encerrando programa. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}



/*Campo prioridade: adicionado na struct Item, com valor entre 1 e 5.
Enum CriterioOrdenacao: para facilitar a escolha do critério de ordenação.
Insertion sort: usado para ordenar o vetor conforme o critério escolhido, contando comparações.
Busca binária: só funciona se a mochila estiver ordenada por nome, caso contrário avisa o usuário.
Variável global criterioAtual: indica o critério pelo qual a mochila está ordenada, para validar a busca binária.
Menu: inclui opções para todas as funcionalidades, com mensagens claras e validação de entrada*/