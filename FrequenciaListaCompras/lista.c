#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include <stdlib.h>

void inicializar(BancoProdutos *bp) {
    bp->total = 0;
    bp->capacidade = 10; 
    bp->lista = (Produto *)malloc(bp->capacidade * sizeof(Produto));
    if (bp->lista == NULL) {
      
        printf("Erro ao alocar memória para produtos.\n");
        exit(1);
    }
}

int adicionar_produto(BancoProdutos *bp, const char *nome, const char *tipo) {
    if (bp->total >= bp->capacidade) {
       
        bp->capacidade *= 2;
        bp->lista = (Produto *)realloc(bp->lista, bp->capacidade * sizeof(Produto));
        if (bp->lista == NULL) {
            printf("Erro ao realocar memória para produtos.\n");
            return -1;
        }
    }

    
    Produto novo_produto;
    strncpy(novo_produto.nome, nome, TAM_NOME);
    strncpy(novo_produto.tipo, tipo, TAM_NOME);
    
    novo_produto.preco_minimo = 0.0;
    strncpy(novo_produto.loja, "Desconhecida", TAM_NOME);

    bp->lista[bp->total++] = novo_produto;
    return 0;
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
                if (strcasestr_custom(bp->lista[i].tipo, filtro) == 0) {
                    printf("Nome: %s | Tipo: %s | Preco: %.2f | Loja: %s\n",
                        bp->lista[i].nome,
                        bp->lista[i].tipo,
                        bp->lista[i].preco_minimo,
                        bp->lista[i].loja);
                }
            }
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }
}

void inicializar_listas(BancoListas *bl) {
    bl->total_listas = 0;
    bl->capacidade_listas = 10; 
    bl->listas = (ListaCompras *)malloc(bl->capacidade_listas * sizeof(ListaCompras));
    if (bl->listas == NULL) {
        printf("Erro ao alocar memória para listas de compras.\n");
        exit(1);
    }
}


int adicionar_lista_compras(BancoListas *bl, const char *nome) {
    if (bl->total_listas >= bl->capacidade_listas) {
        
        bl->capacidade_listas *= 2;
        bl->listas = (ListaCompras *)realloc(bl->listas, bl->capacidade_listas * sizeof(ListaCompras));
        if (bl->listas == NULL) {
            printf("Erro ao realocar memória para listas de compras.\n");
            return 0;
        }
    }

   
    strcpy(bl->listas[bl->total_listas].nome, nome);
    bl->listas[bl->total_listas].produtos = (Produto *)malloc(MAX_PRODUTOS * sizeof(Produto)); 
    if (bl->listas[bl->total_listas].produtos == NULL) {
        printf("Erro ao alocar memória para produtos da lista.\n");
        return 0;
    }
    bl->listas[bl->total_listas].total_produtos = 0;
    bl->total_listas++;
    return 1;
}

int adicionar_produto_lista(BancoListas *bl, const char *nome_lista, Produto produto, BancoProdutos *bp) {
    for (int i = 0; i < bl->total_listas; i++) {
        if (_stricmp(bl->listas[i].nome, nome_lista) == 0) {
            
            if (bl->listas[i].total_produtos < MAX_PRODUTOS) {
                
                for (int j = 0; j < bp->total; j++) {
                    
                    if (_stricmp(bp->lista[j].nome, produto.nome) == 0) {
                       
                        Produto prod = bp->lista[j];   
                        
                        bl->listas[i].produtos[bl->listas[i].total_produtos] = prod;
                        bl->listas[i].total_produtos++;
                        return 1;
                    }
                }
                
                bl->listas[i].produtos[bl->listas[i].total_produtos] = produto;
                bl->listas[i].total_produtos++;
                return 1;
            }
        }
    }
    return 0; 
}

int remover_produto_lista(BancoListas *bl, const char *nome_lista, Produto produto) {
	
	for (int i = 0; i < bl->total_listas; i++) {
		if (_stricmp(bl->listas[i].nome, nome_lista) == 0) {
			

			
			for (int j = 0; j < bl->listas[i].total_produtos; j++) {
				if (_stricmp(bl->listas[i].produtos[j].nome, produto.nome) == 0) {
					for (int k = j; k < bl->listas[i].total_produtos - 1; k++) {
						bl->listas[i].produtos[k] = bl->listas[i].produtos[k + 1];
					}
					bl->listas[i].total_produtos--;

					printf("Produto '%s' removido com sucesso da lista '%s'.\n", produto.nome, nome_lista);
					return 1;  
				}
			}

			
			printf("Produto '%s' nao encontrado na lista '%s'.\n", produto.nome, nome_lista);
			return 0;  
		}
	}

	
	printf("Lista de compras '%s' nao encontrada.\n", nome_lista);
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
				printf("Nome: %s | Tipo: %s | Preco: %.2f | Loja: %s | Status: %s\n",
					bl->listas[i].produtos[j].nome,
					bl->listas[i].produtos[j].tipo,
					bl->listas[i].produtos[j].preco_minimo,
					bl->listas[i].produtos[j].loja,
					bl->listas[i].produtos[j].comprado ? "Comprado" : "Pendente");
			}
			return;
		}
	}
	printf("Lista de compras nao encontrada.\n");
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

    
    char linha[256];
    fgets(linha, sizeof(linha), file);

    
    while (fgets(linha, sizeof(linha), file)) {
        Produto produto;
        char preco[20]; 

        
        sscanf(linha, "%99[^,],%99[^,],%19[^,],%99[^\n]",
               produto.nome, produto.tipo, preco, produto.loja);

        
        produto.preco_minimo = atof(preco);

       
        adicionar_produto(bp, produto.nome, produto.tipo);
        bp->lista[bp->total - 1].preco_minimo = produto.preco_minimo;
        strcpy(bp->lista[bp->total - 1].loja, produto.loja);
    }

    fclose(file);
}

int marcar_produto_lista(BancoListas *bl, const char *nome_lista, const char *nome_produto, int status) {
	for (int i = 0; i < bl->total_listas; i++) {
		if (_stricmp(bl->listas[i].nome, nome_lista) == 0) {
			for (int j = 0; j < bl->listas[i].total_produtos; j++) {
				if (_stricmp(bl->listas[i].produtos[j].nome, nome_produto) == 0) {
					bl->listas[i].produtos[j].comprado = status;

					if (status == 1) {
						printf("Informe o preco pago: ");
						scanf("%f", &bl->listas[i].produtos[j].preco_minimo); 

						printf("Informe a loja onde foi comprado: ");
						scanf(" %[^\n]", bl->listas[i].produtos[j].loja);
					}

					printf("Produto '%s' %s com sucesso.\n", nome_produto, status ? "marcado como comprado" : "marcado como pendente");
					return 1;
				}
			}
			printf("Produto '%s' nao encontrado na lista '%s'.\n", nome_produto, nome_lista);
			return 0;
		}
	}
	printf("Lista '%s' nao encontrada.\n");
	return 0;
}

void destruir(BancoProdutos *bp) {
    free(bp->lista);  
}
void destruir_listas(BancoListas *bl) {
    for (int i = 0; i < bl->total_listas; i++) {
        free(bl->listas[i].produtos);  
    }
    free(bl->listas);
}