#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include <stdlib.h>

void inicializar(BancoProdutos *bp) {
    bp->total = 0;
}

int adicionar_produto(BancoProdutos *bp, const char *nome, const char *tipo) {
    if (bp->total >= MAX_PRODUTOS) return 0;

    for (int i = 0; i < bp->total; i++) {
        if (_stricmp(bp->lista[i].nome, nome) == 0) return 0;
    }

    strcpy(bp->lista[bp->total].nome, nome);
    strcpy(bp->lista[bp->total].tipo, tipo);
    bp->lista[bp->total].preco_minimo = 0.0;
    bp->lista[bp->total].loja[0] = '\0';
    bp->total++;

    return 1;
}

int remover_produto(BancoProdutos *bp, const char *nome) {
    for (int i = 0; i < bp->total; i++) {
        if (_stricmp(bp->lista[i].nome, nome) == 0) {
            for (int j = i; j < bp->total - 1; j++) {
                bp->lista[j] = bp->lista[j + 1];
            }
            bp->total--;
            return 1;
        }
    }
    return 0;
}

int alterar_nome_produto(BancoProdutos *bp, const char *nome_atual, const char *novo_nome) {
    for (int i = 0; i < bp->total; i++) {
        if (_stricmp(bp->lista[i].nome, nome_atual) == 0) {
            strcpy(bp->lista[i].nome, novo_nome);
            return 1;
        }
    }
    return 0;
}

void listar_produtos(BancoProdutos *bp) {
    int opcao;
    char filtro[TAM_NOME];
    printf("Escolha o tipo de listagem:\n");
    printf("1. Todos os produtos\n");
    printf("2. Produtos por nome (parcial)\n");
    printf("3. Produtos por tipo\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            for (int i = 0; i < bp->total; i++) {
                printf("Nome: %s | Tipo: %s | Preco: %.2f | Loja: %s\n",
                    bp->lista[i].nome,
                    bp->lista[i].tipo,
                    bp->lista[i].preco_minimo,
                    bp->lista[i].loja);
            }
            break;

        case 2:
            printf("Digite parte do nome: ");
            scanf(" %[^\n]", filtro);
            for (int i = 0; i < bp->total; i++) {
                if (strcasestr_custom(bp->lista[i].nome, filtro)) {
                    printf("Nome: %s | Tipo: %s | Preco: %.2f | Loja: %s\n",
                        bp->lista[i].nome,
                        bp->lista[i].tipo,
                        bp->lista[i].preco_minimo,
                        bp->lista[i].loja);
                }
            }
            break;

        case 3:
            printf("Digite o tipo: ");
            scanf(" %[^\n]", filtro);
            for (int i = 0; i < bp->total; i++) {
                if (_stricmp(bp->lista[i].tipo, filtro) == 0) {
                    printf("Nome: %s | Tipo: %s | Preco: %.2f | Loja: %s\n",
                        bp->lista[i].nome,
                        bp->lista[i].tipo,
                        bp->lista[i].preco_minimo,
                        bp->lista[i].loja);
                }
            }
            break;

        default:
            printf("Opcao inválida.\n");
            break;
    }
}

void inicializar_listas(BancoListas *bl) {
    bl->total_listas = 0;
}

int adicionar_lista_compras(BancoListas *bl, const char *nome) {
    if (bl->total_listas >= MAX_LISTAS) return 0;
    strcpy(bl->listas[bl->total_listas].nome, nome);
    bl->listas[bl->total_listas].total_produtos = 0;
    bl->total_listas++;
    return 1;
}

int adicionar_produto_lista(BancoListas *bl, const char *nome_lista, Produto produto) {
    for (int i = 0; i < bl->total_listas; i++) {
        if (_stricmp(bl->listas[i].nome, nome_lista) == 0) {
            if (bl->listas[i].total_produtos < MAX_PRODUTOS) {
                bl->listas[i].produtos[bl->listas[i].total_produtos] = produto;
                bl->listas[i].total_produtos++;
                return 1;
            }
        }
    }
    return 0;
}

void listar_listas_compras(BancoListas *bl) {
    for (int i = 0; i < bl->total_listas; i++) {
        printf("Lista de Compras: %s\n", bl->listas[i].nome);
    }
}

void listar_produtos_lista(BancoListas *bl, const char *nome_lista) {
    for (int i = 0; i < bl->total_listas; i++) {
        if (_stricmp(bl->listas[i].nome, nome_lista) == 0) {
            printf("Produtos na lista: %s\n", nome_lista);
            for (int j = 0; j < bl->listas[i].total_produtos; j++) {
                printf("Nome: %s | Tipo: %s | Preço: %.2f | Loja: %s\n",
                    bl->listas[i].produtos[j].nome,
                    bl->listas[i].produtos[j].tipo,
                    bl->listas[i].produtos[j].preco_minimo,
                    bl->listas[i].produtos[j].loja);
            }
            return;
        }
    }
    printf("Lista de compras não encontrada.\n");
}

char *strcasestr_custom(const char *haystack, const char *needle) {
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        while (*n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
            h++;
            n++;
        }

        if (*n == '\0') return (char *)haystack;
        haystack++;
    }
    return NULL;
}

void ler_csv(BancoProdutos *bp, const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    // Pular o cabecalho
    char linha[256];
    fgets(linha, sizeof(linha), file);

    // Ler produtos do CSV
    while (fgets(linha, sizeof(linha), file)) {
        Produto produto;
        char preco[20]; // Para ler o preco como string e depois converter

        // Lê o nome, tipo, preco e loja
        sscanf(linha, "%99[^,],%99[^,],%19[^,],%99[^\n]",
               produto.nome, produto.tipo, preco, produto.loja);

        // Converte o preco para float
        produto.preco_minimo = atof(preco);

        // Adiciona o produto ao banco de produtos
        adicionar_produto(bp, produto.nome, produto.tipo);
        bp->lista[bp->total - 1].preco_minimo = produto.preco_minimo;
        strcpy(bp->lista[bp->total - 1].loja, produto.loja);
    }

    fclose(file);
}
