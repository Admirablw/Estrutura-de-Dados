#include <stdio.h>
#include "lista.h"
#include <string.h>

int main() {
    BancoProdutos banco;
    BancoListas listas;
    inicializar(&banco);
    inicializar_listas(&listas);

    
    ler_csv(&banco, "./FrequenciaListaCompras/produtos.csv");

    int opcao;
    char nome[TAM_NOME], tipo[TAM_NOME], novo_nome[TAM_NOME], nome_lista[TAM_NOME];

 	do {
        printf("\n==== MENU ====\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Alterar nome do produto\n");
        printf("4. Listar produtos\n");
        printf("5. Criar lista de compras\n");
        printf("6. Adicionar produto à lista de compras\n");
        printf("7. Remover produto da lista de compras\n");
        printf("8. Listar listas de compras\n");
        printf("9. Listar produtos em uma lista de compras\n");
        printf("10. Marcar ou Desmarcar Produto em uma lista de compras");
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
	
			case 5:
				printf("Nome da nova lista de compras: ");
				scanf(" %[^\n]", nome_lista);
				if (adicionar_lista_compras(&listas, nome_lista))
					printf("Lista de compras criada!\n");
				else
					printf("Erro ao criar lista de compras.\n");
				break;
	
			case 6:
				printf("Nome da lista de compras: ");
				scanf(" %[^\n]", nome_lista);
                listar_produtos(&banco);
				printf("Nome do produto a adicionar: ");
				scanf(" %[^\n]", nome);
				Produto produto = {0};
				strcpy(produto.nome, nome);
				
				if (adicionar_produto_lista(&listas, nome_lista, produto, &banco))
					printf("Produto adicionado à lista!\n");
				else
					printf("Erro ao adicionar produto à lista.\n");
				break;
            case 7:
                printf("Nome da lista de compras: ");
                scanf(" %[^\n]", nome_lista);
            
                listar_produtos_lista(&listas, nome_lista);
            
                printf("Nome do produto a remover: ");
                scanf(" %[^\n]", nome);
            
                
                strcpy(produto.nome, nome);
                
                if (remover_produto_lista(&listas, nome_lista, produto)) {
                    printf("Produto removido da lista com sucesso!\n");
                } else {
                    printf("Erro ao remover produto da lista.\n");
                }
                break;
            
			case 8:
				listar_listas_compras(&listas);
				break;
	
			case 9:
				printf("Nome da lista de compras: ");
				scanf(" %[^\n]", nome_lista);
				listar_produtos_lista(&listas, nome_lista);
				break;
            case 10:
	            printf("Nome da lista: ");
	            scanf(" %[^\n]", nome_lista);
                listar_produtos_lista(&listas, nome_lista);
	            printf("Nome do produto: ");
	            scanf(" %[^\n]", nome);
	            printf("1 - Marcar como comprado\n0 - Marcar como pendente\nEscolha: ");
	            int status;
	            scanf("%d", &status);
	            if (marcar_produto_lista(&listas, nome_lista, nome, status)) {
		            printf("Status atualizado!\n");
	            } else {
		            printf("Erro ao atualizar o status.\n");
	            }
	            break;

			case 0:
				printf("Saindo...\n");
				break;
	
			default:
				printf("Opcao invalida!\n");
			}
		} while (opcao != 0);
        destruir(&banco);
        destruir_listas(&listas);
		return 0;
	}
