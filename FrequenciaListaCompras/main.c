#include <stdio.h>
#include "lista.h"

int main() {
    BancoProdutos banco;
    inicializar(&banco);

    // Carregar produtos do CSV
    ler_csv(&banco, "./FrequenciaListaCompras/produtos.csv");

    int opcao;
    char nome[TAM_NOME], tipo[TAM_NOME], novo_nome[TAM_NOME];

    do {
        printf("\n==== MENU ====\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Alterar nome do produto\n");
        printf("4. Listar produtos\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Nome do produto: ");
            scanf(" %[^\n]", nome);
            printf("Tipo (frios, congelados, laticinios): ");
            scanf(" %[^\n]", tipo);
            if (adicionar_produto(&banco, nome, tipo))
                printf("Produto adicionado com sucesso!\n");
            else
                printf("Erro ao adicionar produto.\n");
            break;

        case 2:
            printf("Nome do produto a remover: ");
            scanf(" %[^\n]", nome);
            if (remover_produto(&banco, nome))
                printf("Produto removido.\n");
            else
                printf("Produto nao encontrado.\n");
            break;

        case 3:
            printf("Nome atual do produto: ");
            scanf(" %[^\n]", nome);
            printf("Novo nome: ");
            scanf(" %[^\n]", novo_nome);
            if (alterar_nome_produto(&banco, nome, novo_nome))
                printf("Nome alterado.\n");
            else
                printf("Produto nao encontrado.\n");
            break;

        case 4:
            listar_produtos(&banco);
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
