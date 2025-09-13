#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];  // Vetor estático para armazenar os itens
int totalItens = 0;       // Quantidade atual de itens cadastrados

// Função para adicionar um item na mochila
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    getchar(); // Limpar buffer do teclado
    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // Remove '\n'

    printf("Digite o tipo do item: ");
    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
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

    // Desloca os itens para preencher o espaço do removido
    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    printf("Item removido com sucesso!\n");
}

// Função para listar os itens cadastrados em formato de tabela
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int main() {
    int opcao;

    do {
        printf("\n=== Menu da Mochila Virtual ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
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
            case 0:
                printf("Encerrando programa. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
