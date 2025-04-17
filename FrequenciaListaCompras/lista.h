#ifndef LISTA_H
#define LISTA_H

#define MAX_PRODUTOS 100
#define MAX_LISTAS 50
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

typedef struct {
    char nome[TAM_NOME];
    Produto produtos[MAX_PRODUTOS];
    int total_produtos;
} ListaCompras;

typedef struct {
    ListaCompras listas[MAX_LISTAS];
    int total_listas;
} BancoListas;

void inicializar(BancoProdutos *bp);
int adicionar_produto(BancoProdutos *bp, const char *nome, const char *tipo);
int remover_produto(BancoProdutos *bp, const char *nome);
int alterar_nome_produto(BancoProdutos *bp, const char *nome_atual, const char *novo_nome);
void listar_produtos(BancoProdutos *bp);
char *strcasestr_custom(const char *haystack, const char *needle);
void ler_csv(BancoProdutos *bp, const char *nome_arquivo);

void inicializar_listas(BancoListas *bl);
int adicionar_lista_compras(BancoListas *bl, const char *nome);
int adicionar_produto_lista(BancoListas *bl, const char *nome_lista, Produto produto);
void listar_listas_compras(BancoListas *bl);
void listar_produtos_lista(BancoListas *bl, const char *nome_lista);
#endif
