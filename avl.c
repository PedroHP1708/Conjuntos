#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "avl.h"

typedef struct no NO;

struct no 
{
    int chave;
    NO *esq;
    NO *dir;
    int FB;
};

struct avl
{
    NO *raiz;
    int altura;
};

int avl_altura_no(NO* raiz) 
{
    if (raiz == NULL)
    {
        return -1;
    } 
    else 
    {
        return raiz->altura;
    }
}

NO *avl_cria_no(int chave) 
{
    NO *no = (NO *) malloc(sizeof (NO));
    if (no != NULL) {
        no->FB = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->chave = chave;
    }
    return no;
}

AVL *avl_criar(void) 
{
    AVL *arvore = (AVL *) malloc(sizeof (AVL));
    if (arvore != NULL) {
        arvore->raiz = NULL; arvore->altura = -1;
    }
    return arvore;
}

void avl_apagar_aux(NO *raiz) 
{
    if (raiz != NULL) {
        avl_apagar_aux(raiz->esq);
        avl_apagar_aux(raiz->dir);
        free(raiz);
    }
}

void avl_apagar(AVL **arvore) 
{
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

NO *rodar_direita(NO *a) 
{
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = 0;
    b->FB = 0;

    return b;
}

NO *rodar_esquerda(NO *a) 
{
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    
    a->FB = 0;
    b->FB = 0;

    return b;
}

NO *rodar_esquerda_direita(NO *a) 
{
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

NO *rodar_direita_esquerda(NO *a) 
{
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

NO *avl_inserir_no(NO *raiz, ITEM *item) 
{
    if (raiz == NULL)
        raiz = avl_cria_no(item);
    
    else if (item_chave(item) < item_chave(raiz->item))
        raiz->esq = avl_inserir_no(raiz->esq, item);
    
    else if (item_chave(item) > item_chave(raiz->item))
        raiz->dir = avl_inserir_no(raiz->dir, item);


    raiz->FB = (avl_altura2(raiz->esq)) - (avl_altura2(raiz->dir));

    if (raiz->FB == -2)
    {
        if (raiz->dir->FB <= 0)
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }  

    if (raiz->FB == 2)
    {
        if (raiz->esq->FB >=0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
        

    return raiz;
}

bool avl_inserir(AVL *arvore, int chave) 
{
    return ((arvore->raiz = avl_inserir_no(arvore->raiz, chave)) != NULL);
}

void atualiza_maximo(NO *troca, NO *raiz, NO *ant)
{
    if(troca->dir != NULL)
    {
        atualiza_maximo(troca->dir, raiz, troca);
        return;
    }

    if(raiz == ant)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

NO *avl_remover_no(NO *raiz, int chave)
{
    NO *aux;

    if(raiz == NULL)
        return NULL;
    else if(chave == raiz->chave)
    {
        if(raiz->esq == NULL || raiz->dir == NULL)
        {
            aux = raiz;
            if(raiz->esq == NULL)
                raiz = raiz->dir;
            else
                raiz = raiz->esq; 

            free(aux);
            aux = NULL;
        }
        else
            atualiza_maximo(raiz->esq, *raiz, *raiz);
    }

    else if(chave < raiz->chave)
        raiz-> esq = avl_remover_no(raiz->esq, chave);

    else if(chave > raiz->chave)
        raiz-> dir = avl_remover_no(raiz->dir, chave);

    raiz->FB = avl_altura2(raiz->esq) - avl_altura2(raiz->dir);
    if(raiz->FB == 2)
    {
        if (raiz->esq->FB >= 0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
    if(raiz->FB == -2)
    {
        if (raiz->dir->FB <= 0)
            raiz = rodar_esquerda(raiz);
        else   
            raiz = rodar_direita_esquerda(raiz);  
    }
    return raiz;
}

bool avl_remover(AVL *arvore, int chave) 
{
    return ((arvore->raiz = avl_remover_no(arvore->raiz, chave)) != NULL);
}