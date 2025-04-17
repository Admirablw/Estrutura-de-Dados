#ifndef LISTA_H
#define LISTA_H

#define MAX_PRODUTOS 100
#define TAM_NOME 100

typedef struct {
	char nome[TAM_NOME];
	char tipo[TAM_NOME];
	float preco_minimo;
	char loja[TAM_NOME];
} Produto;

typedef struct {
	Produto lista[MAX_PRODUTOS];
	int total;
} BancoProdutos;

void inicializar(BancoProdutos *bp);
int adicionar_produto(BancoProdutos *bp, const char *nome, const char *tipo);
int remover_produto(BancoProdutos *bp, const char *nome);
int alterar_nome_produto(BancoProdutos *bp, const char *nome_atual, const char *novo_nome);
void listar_produtos(BancoProdutos *bp);
char *strcasestr_custom(const char *haystack, const char *needle);
void ler_csv(BancoProdutos *bp, const char *nome_arquivo);

#endif
