#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

no_t *iterative_tree_search(arvoreRB_t *T, no_t *x, void *k){
	while(x != NULO(T) && COMPARA(T)(k, DADO(x))!=0){
		if(COMPARA(T)(k, DADO(x))<0){ // Primeiro menor que o segundo
			x = ESQUERDO(x);
		}else{
			x = DIREITO(x);
		}
	}

	return x;
}

no_t *tree_search(arvoreRB_t *T, no_t *x, void *k){
    return iterative_tree_search(T, x, k);
}

void left_rotate(arvoreRB_t *T, no_t *x){
	no_t *y;
	y = DIREITO(x);
	DIREITO(x) = ESQUERDO(y);
	if (ESQUERDO(y) != NULO(T)){
		PAI(ESQUERDO(y)) = x;
	}
	PAI(y) = PAI(x);
	if(PAI(x) == NULO(T)){
		RAIZ(T) = y;
	}else if (x == ESQUERDO(PAI(x))){
		ESQUERDO(PAI(x)) = y;
	}else{
		DIREITO(PAI(x)) = y;
	}
	ESQUERDO(y) = x;
	PAI(x) = y;
}

void right_rotate(arvoreRB_t *T, no_t *x){
	no_t *y;
	//printf("ENTER_RIGHT_ROTATE\n");
	//T->print(x);
	y = ESQUERDO(x);
	//printf("DEBUG RIGHT 00\n");
	//T->print(y);
	ESQUERDO(x) = DIREITO(y);
	//printf("DEBUG RIGHT 01\n");
	if (DIREITO(y) != NULO(T)){
		//printf("DEBUG RIGHT 02\n");
		PAI(DIREITO(y)) = x;
		//printf("DEBUG RIGHT 03\n");
	}
	//printf("DEBUG RIGHT 04\n");
	PAI(y) = PAI(x);
	//printf("DEBUG RIGHT 05\n");
	if(PAI(x)== NULO(T)){
		//printf("DEBUG RIGHT 06\n");
		RAIZ(T) = y;
		//printf("DEBUG RIGHT 07\n");
	}else if(x == DIREITO(PAI(x))){
		//printf("DEBUG RIGHT 08\n");
		DIREITO(PAI(x)) = y;
		//printf("DEBUG RIGHT 09\n");
	}else{
		//printf("DEBUG RIGHT 10\n");
		ESQUERDO(PAI(x)) = y;
		//printf("DEBUG RIGHT 11\n");
	}
	//printf("DEBUG RIGHT 12\n");
	DIREITO(y) = x;
	//printf("DEBUG RIGHT 13\n");
	PAI(x) = y;
	//printf("EXIT_RIGHT_ROTATE\n");
}

no_t *tree_minimum(arvoreRB_t *T, no_t	*x){
	while(ESQUERDO(x) != NULO(T)){
		x = ESQUERDO(x);
	}

	return x;
}

no_t *tree_maximum(arvoreRB_t *T, no_t *x){
	while(DIREITO(x) != NULO(T)){
		x = DIREITO(x);
	}

	return x;
}

no_t *tree_sucessor(arvoreRB_t *T, no_t *x){
	no_t	*y;
	if(DIREITO(x) != NULO(T)){
		return tree_minimum(T, DIREITO(x));
	}
	y = PAI(x);
	while((y != NULO(T)) && (x == DIREITO(y))){
		x = y;
		y = PAI(y);
	}

	return y;
}

no_t *tree_predecessor(arvoreRB_t *T, no_t *x){
	no_t	*y;

	if(ESQUERDO(x) != NULO(T)){
		return tree_maximum(T, ESQUERDO(x));
	}
	y = PAI(x);
	while((y != NULO(T)) && (x == ESQUERDO(y))){
		x = y;
		y = PAI(y);
	}

	return y;
}

void rb_tree_insert_fixup(arvoreRB_t *T, no_t *z){
    no_t *y;
    while(COR(PAI(z)) == RED){
        if(PAI(z) == ESQUERDO(PAI(PAI(z)))){
            y = DIREITO(PAI(PAI(z)));
            if(COR(y) == RED){
                COR(PAI(z)) = BLACK;
                COR(y) = BLACK;
                COR(PAI(PAI(z))) = RED;
                z = PAI(PAI(z));
            }else{
                if(z == DIREITO(PAI(z))){
                    z = PAI(z);
                    left_rotate(T, z);
                }
                COR(PAI(z)) = BLACK;
                COR(PAI(PAI(z))) = RED;
                right_rotate(T, PAI(PAI(z)));
            }
        }else{
            y = ESQUERDO(PAI(PAI(z)));
            if(COR(y) == RED){
                COR(PAI(z)) = BLACK;
                COR(y) = BLACK;
                COR(PAI(PAI(z))) = RED;
                z = PAI(PAI(z));
            }else{
                if(z == ESQUERDO(PAI(z))){
                    z = PAI(z);
                    right_rotate(T, z);
                }
                COR(PAI(z)) = BLACK;
                COR(PAI(PAI(z))) = RED;
                left_rotate(T, PAI(PAI(z)));
            }
        }
    }
    COR(RAIZ(T)) = BLACK;
}

no_t *rb_tree_insert(arvoreRB_t *T, no_t *z){
	no_t	*y;
	no_t	*x;
	y = NULO(T);
	x = RAIZ(T);
	while(x != NULO(T)){
		y = x;
		if(COMPARA(T)(DADO(z), DADO(x))<0){
			x = ESQUERDO(x);
		}else if(COMPARA(T)(DADO(z), DADO(x))>0){
			x = DIREITO(x);
		}else{
		    return NULL;
		}
	}

	PAI(z) = y;
	if(y == NULO(T)){
		RAIZ(T) = z;
	}else if(COMPARA(T)(DADO(z), DADO(y))<0){
		ESQUERDO(y) = z;
	}else{
		DIREITO(y) = z;
	}

    ESQUERDO(z) = NULO(T);
    DIREITO(z)  = NULO(T);

    if(RB(T) == REDBLACK){
        COR(z) = RED;
        rb_tree_insert_fixup(T, z);
    }
	T->count++;

	return z;
}

void rb_transplant(arvoreRB_t *T, no_t *u, no_t *v){
    if(PAI(u) == NULO(T)){
        RAIZ(T) = v;
    }else if(u == ESQUERDO(PAI(u))){
        ESQUERDO(PAI(u)) = v;
    }else{
        DIREITO(PAI(u)) = v;
    }
    PAI(v) = PAI(u);
}

void rb_delete_fixup(arvoreRB_t *T, no_t *x){
    no_t *w;
    // printf("%d\n", COR(x));
    while(x != RAIZ(T) && COR(x) == BLACK){
        if(x == ESQUERDO(PAI(x))){
            w = DIREITO(PAI(x));
            if(COR(w) == RED){
                COR(w) = BLACK;
                COR(PAI(x)) = RED;
                left_rotate(T, PAI(x));
                w = DIREITO(PAI(x));
            }
            if(COR(ESQUERDO(w)) == BLACK && COR(DIREITO(w)) == BLACK){
                COR(w) = RED;
                x = PAI(x);
            }else{
				if(COR(DIREITO(w)) == BLACK){
					COR(ESQUERDO(w)) = BLACK;
					COR(w) = RED;
					right_rotate(T, w);
					w = DIREITO(PAI(x));
				}
				COR(w) = COR(PAI(x));
				COR(PAI(x)) = BLACK;

				COR(DIREITO(w)) = BLACK;
				left_rotate(T, PAI(x));
				x = RAIZ(T);
            }
        }else{
        	//printf("DIREITO\n");
            w = ESQUERDO(PAI(x));
            if(COR(w) == RED){
                COR(w) = BLACK;
                COR(PAI(x)) = RED;
                right_rotate(T, PAI(x));
                w = ESQUERDO(PAI(x));
            }
            if(COR(DIREITO(w)) == BLACK && COR(ESQUERDO(w)) == BLACK){
                COR(w) = RED;
                x = PAI(x);
            }else{
				if(COR(ESQUERDO(w)) == BLACK){
					COR(DIREITO(w)) = BLACK;
					COR(w) = RED;
					left_rotate(T, w);
					w = ESQUERDO(PAI(x));
				}
				COR(w) = COR(PAI(x));
				COR(PAI(x)) = BLACK;

				COR(ESQUERDO(w)) = BLACK;
				right_rotate(T, PAI(x));
				x = RAIZ(T);
            }
        }
    }
    COR(x) = BLACK;
}

no_t *rb_tree_delete(arvoreRB_t *T, no_t *z){
    no_t *y, *x, *aux;
    uint8_t y_cor_original;

    aux = z;
    y = z;
    y_cor_original = COR(y);

    if(ESQUERDO(z) == NULO(T)){
        x = DIREITO(z);
        rb_transplant(T, z, DIREITO(z));
    }else if(DIREITO(z) == NULO(T)){
        x = ESQUERDO(z);
        rb_transplant(T, z, ESQUERDO(z));
    }else{
        y = tree_minimum(T, DIREITO(z));
        y_cor_original = COR(y);
        x = DIREITO(y);
        if(PAI(y) == z){
            PAI(x) = y;
        }else{
            rb_transplant(T, y, DIREITO(y));
            DIREITO(y) = DIREITO(z);
            PAI(DIREITO(y)) = y;
        }
        rb_transplant(T, z, y);
        ESQUERDO(y) = ESQUERDO(z);
        PAI(ESQUERDO(y)) = y;
        if(RB(T) == REDBLACK){
            COR(y) = COR(z);
        }
    }
    if(y_cor_original == BLACK && RB(T) == REDBLACK){
        rb_delete_fixup(T, x);
    }
    T->count--;
    return aux;
}

no_t *palloc_no(arvoreRB_t *T){
	no_t *r;
	r = (no_t *)malloc(sizeof(no_t));
	if(r == NULL){
		return r;
	}

	PAI(r) = NULO(T);
	ESQUERDO(r) = NULO(T);
	DIREITO(r) = NULO(T);
	COR(r) = RED;

	return r;
}
no_t *alloc_no(arvoreRB_t *T, void *dado){
    no_t *r;
    r = palloc_no(T);
    if(r != NULL){
        DADO(r) = dado;
    }

	return r;
}

void free_no(no_t *x){
	free(x);
}

void inorder_tree_walk(arvoreRB_t *T, no_t *x, void *p){
	if(x != NULO(T)){
		inorder_tree_walk(T, ESQUERDO(x), p);
		T->walk(T, x, p);
		inorder_tree_walk(T, DIREITO(x), p);
	}
}

void preorder_tree_walk(arvoreRB_t *T, no_t *x, void *p){
	if(x != NULO(T)){
		T->walk(T, x, p);
		preorder_tree_walk(T, ESQUERDO(x), p);
		preorder_tree_walk(T, DIREITO(x), p);
	}
}

void posorder_tree_walk(arvoreRB_t *T, no_t *x, void *p){
	if(x != NULO(T)){
		preorder_tree_walk(T, ESQUERDO(x), p);
		preorder_tree_walk(T, DIREITO(x), p);
		T->walk(T, x, p);
	}
}

// Acho que esta rotina está errada. Depois precisa analisar com mais calma
no_t *inorder_tree_walk_max(arvoreRB_t *T, no_t *x, void *p, uint32_t *max){
	no_t *aux;
	if(x != NULO(T)){
		aux = inorder_tree_walk_max(T, ESQUERDO(x), p, max);
		if(aux == NULO(T)){
			if(*max == 0){
				return x;
			}else{
				*max = *max - 1;
				return inorder_tree_walk_max(T, DIREITO(x), p, max);
			}
		}else{
			return aux;
		}
	}else{
		return x;
	}
}

arvoreRB_t *ArvoreRB_t(arvoreRB_t *T, char rb, chave_cmp *compara, copia_sig *copia, walk_sig *walk){
    no_t *folha_nula;
	RAIZ(T) 	= NULL;
	COMPARA(T)	= compara;
	T->copia 	= copia;
	T->walk 	= walk;
	COUNT(T)	= 0;
	RB(T)		= rb;

	folha_nula = palloc_no(T);
	if(folha_nula == NULL){
        return NULL;
	}
	NULO(T) = folha_nula;
    COR(folha_nula) = BLACK;
    PAI(folha_nula) = NULO(T);
    ESQUERDO(folha_nula) = NULO(T);
    DIREITO(folha_nula) = NULO(T);
    DADO(folha_nula) = NULO(T);
    // A chave não é um apontador, aí não atribuí nada.
    RAIZ(T) = NULO(T);
    // Note que a folha nula não aponta para um pai, filho esquerdo ou direito
	return T;
}

void free_arvore(arvoreRB_t *T){
	free(NULO(T));
}

int checa_AlturaCor(arvoreRB_t *T, no_t *raiz, unsigned int *nnos){
    unsigned int nesquerdo, ndireito;
    unsigned int resquerdo, rdireito;
    if(raiz == NULO(T)){
        *nnos = 0;
        return 1;
    }

	if((ESQUERDO(raiz) != NULO(T) && COMPARA(T)(DADO(ESQUERDO(raiz)), DADO(raiz))>0 ) ||
       (DIREITO(raiz)  != NULO(T) && COMPARA(T)(DADO(DIREITO(raiz )), DADO(raiz))<0 )){
        return 0;
    }

    if(COR(raiz) == RED &&
        (
         (ESQUERDO(raiz) != NULO(T)  && COR(ESQUERDO(raiz)) == RED) ||
         (DIREITO(raiz)  != NULO(T)  && COR(DIREITO(raiz))  == RED)
        )
       ){
        return 0;
    }

    resquerdo = checa_AlturaCor(T, ESQUERDO(raiz), &nesquerdo);
    rdireito  = checa_AlturaCor(T, DIREITO(raiz),  &ndireito);

    if((resquerdo == 0) || (rdireito == 0) || (nesquerdo != ndireito)){    // Se alguma das subarvores está errada
       return 0;
    }

    if(COR(raiz) == BLACK){
        *nnos = nesquerdo + 1;
    }else{
        *nnos = nesquerdo;
    }

    return 1;
}

int checaArvore(arvoreRB_t *T){
    unsigned int nnos;
    if(COR(RAIZ(T)) != BLACK){
        return 0;
    }
    return checa_AlturaCor(T, RAIZ(T), &nnos);
}
