#ifndef __RB_TREE__
#define __RB_TREE__

#ifdef _WIN32

#include <stdint.h>
#include <inttypes.h>

#else
#ifdef __FreeBSD__
#include <sys/types.h>
#else
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#endif

#endif


enum{RED, BLACK};

enum{REDBLACK, NORMAL};

typedef struct no_s{
	void		    *dado;
	uint8_t         cor;
	struct no_s 	*p;			//pai
	struct no_s 	*esquerdo;
	struct no_s 	*direito;
}no_t;

// Assinatura da rotina que compara dois nós
typedef int chave_cmp(void *payload1, void *payload2);

// Copia dado de source para destino
typedef void copia_sig(void *destino, void *origem);

// Rotina chamada no *order_tree_walk
typedef void 	walk_sig(void *arvore, no_t *no, void *p);

typedef struct arvoreRB_s{
	no_t		*raiz;
	no_t        *folha_NULL;
	uint32_t	count;
	char		rb;
	chave_cmp	*compara;
	copia_sig	*copia;
	walk_sig	*walk;
}arvoreRB_t;

#define ESQUERDO(x)	(x->esquerdo)
#define DIREITO(x)	(x->direito)
#define PAI(x)		(x->p)
#define COR(x)		(x->cor)
#define RAIZ(T)		((T)->raiz)
#define NULO(T)		((T)->folha_NULL)
#define COUNT(T)	((T)->count)
#define DADO(x)		(x->dado)
#define COMPARA(T)	((T)->compara)
#define	RB(T)		((T)->rb)

/**
 * Inicializa os campos da árvore binária.
 *
 * @param T Arvore binária.
 * @param rb REDBLACK para uma árvore vermelho-preto, NORMAL caso contrário.
 * @param compara Rotina que compara dois nós
 * @param copia Rotina que realiza a cópia dos dados de origem para o destinho. Esta rotina é necessária porque as rotinas de manipulação da árvore binária não sabem o tamanho do payload.
 * @param print Rotina chamada para impressão dos dados por inorder_tree_walk.
 * @return retorna o endereço passado em T ou NULL caso a árvore nao tenha sido criada.
 */
arvoreRB_t *ArvoreRB_t(arvoreRB_t *T, char rb, chave_cmp *compara, copia_sig *copia, walk_sig *walk);

// Realiza a busca na árvore binária
// x na maioria das vezes eh dado por RAIZ(T)
// k é o payload que queremos comparar
no_t *tree_search(arvoreRB_t *T, no_t *x, void *k);

// Realiza a busca na árvore binária
// x na maioria das vezes é dado por RAIZ(T)
no_t *iterative_tree_search(arvoreRB_t *T, no_t *x, void *k);

/**
 * Prepara um nó com o bloco de dados apontado por dado para ser adicionado na árvore binária.
 *
 * @param T Ponteiro para a árvore binária.
 * @param dado Ponteiro para o bloco de dados a ser adicionado na árvore binária. ATENÇÃO! O dado não é copiado. Ele é apontado pelo nó da árvore binária.
 * @return Retorna um ponteiro para o nó onde o dado se encontra.
 */
no_t *alloc_no(arvoreRB_t *T, void *dado);

/**
 *  Retorna o mínimo de uma árvore binária
 *
 *  @param T Ponteiro para a árvore
 *  @param x Ponteiro para o nó de onde a busca deve ser iniciada. Para começar pela raiz da árvore utilize <BR>
 *  RAIZ(arvore)
 *  @return Ponteiro para o nó de menor chave. Não leva em cosideração colisões.
 */
no_t *tree_minimum(arvoreRB_t *T, no_t	*x);

/**
 *
 * Retorna um ponteiro para o nó de maior chave.
 *
 * @param T Ponteiro para a árvore
 * @param x Ponteiro para o nó de onde deve ser iniciada a busca. Para começar pela raiz da árvore utilize
 * RAIZ(arvore)
 * @return Retorna um ponteiro para o nó de maior chave.
 *
 */
no_t *tree_maximum(arvoreRB_t *T, no_t *x);

// Retorna o sucessor de um elemento
no_t *tree_sucessor(arvoreRB_t *T, no_t *x);

// Retorna o predecessor de um elemento
no_t *tree_predecessor(arvoreRB_t *T, no_t *x);

// Adiciona um nó na árvore binária
// Se adicionar retorna o endereço em z. Caso contrário NULL
no_t *rb_tree_insert(arvoreRB_t *T, no_t *z);

/**
 * Remove o nó da árvore binária. ATENÇÃO! Esta rotina não libera a memória alocada para o dado satélite do nó.
 * Depois de chamar a rotina você deve chamar<BR>
 * free(DADO(no));<BR>
 * free(no);<BR>
 *
 * @param T Ponteiro para a árvore binária.
 * @param z Ponteiro para o nó que desejamos remover.
 * @return Retorna um ponteiro para o nó removido da árvore.
 *
 */
no_t *rb_tree_delete(arvoreRB_t *T, no_t *z);

// x na maioria das vezes é dado por RAIZ(T)
void inorder_tree_walk(arvoreRB_t *T, no_t *x, void *p);

// x na maioria das vezes é dado por RAIZ(T)
void preorder_tree_walk(arvoreRB_t *T, no_t *x, void *p);

void posorder_tree_walk(arvoreRB_t *T, no_t *x, void *p);

/**
 * Libera a memória alocada para o nó.
 *
 * @param x Ponteiro para a posição de memória alocada para o nó.
 *
 */
void free_no(no_t *x);

void free_arvore(arvoreRB_t *T);

/**
 * Retorna o nó de indice especificado.
 *
 * @param T Ponteiro para a árvore
 * @param x Ponteiro para o nó a partir do qual a busca deve ser iniciada. Para iniciar da raiz use RAIZ(T)
 * @param max Indice do nó que estamos buscando.
 * @return Ponteiro para o no de indice max ou NULL caso ele não tenha sido encontrado.
 */
no_t *inorder_tree_walk_max(arvoreRB_t *T, no_t *x, void *p, uint32_t *max);

/**
 * Realiza a rotação do nó x à esquerda.
 *
 * @param T Raiz da árvore binária.
 * @param x Nó que desejamos fazer a rotação.
 */
void left_rotate(arvoreRB_t *T, no_t *x);

/**
 * Realiza a rotação do nó y à esquerda.
 *
 * @param T Raiz da árvore binária.
 * @param y Nó que desejamos fazer a rotação.
 */

void right_rotate(arvoreRB_t *T, no_t *y);

no_t *rb_tree_delete(arvoreRB_t *T, no_t *z);

/**
 * Checa se a árvore é uma árvore RB válida.
 *
 * @param T Raiz da árvore binária.
 * @return 1 OK 0 se a árvore não é uma árvore RB válida.
 */
int checaArvore(arvoreRB_t *T);

#endif
