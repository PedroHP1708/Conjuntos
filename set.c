/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "set.h"
#include "avl.h"
#include "lista.h"

#ifndef STRUCTS_
    #define STRUCTS_
    // Define a struct set
    struct set {
        void* estrutura;    // Armazena a estrutura criada (AVL ou lista). É ponteiro void para ser genérico
        unsigned char tipo; // Armazena o tipode estrutura.
    };
#endif

/*
    Foi considerado para todo o TAD set, que o tipo 0 corresponde às operações com Árvore AVL
e o tipo 1 corresponde às operações com listas sequenciais.
    De maneira geral todos os métodos possuem uma verificação do tipo da estrutura e realizam a
operação do método na respectiva estrutura, a partir do tipo da mesma.
*/

// Função responsável por alocar a memória relativa a um set, usando de base o tipo especificado
// no parâmetro. 
SET* set_criar(unsigned char tipo) {
    SET* novo_set = (SET*)malloc(sizeof(SET));
    if (novo_set != NULL) {
        novo_set->tipo = tipo;
        if (tipo == 0) 
            novo_set->estrutura = avl_criar();
        else if(tipo == 1)
            novo_set->estrutura = lista_criar();
    }
    return novo_set;
}

// Função responsável por realizar a operação de 'pertence' na estrutura do tipo especificado
bool set_pertence(SET *A, int elemento) {
    if(A->tipo == 0)
        return avl_pertence((AVL*)A->estrutura, elemento);
    else if(A->tipo == 1)
        return lista_pertence((LISTA*)A->estrutura, elemento);    
}

// Função responsável por realizar a inserção de um elemento na estrutura do tipo especificado
bool set_inserir (SET *s, int elemento) {
    if(s->tipo == 0)
        return avl_inserir((AVL*)s->estrutura, elemento);
    else if(s->tipo == 1)
        return lista_inserir((LISTA*)s->estrutura, elemento);  
}

// Função responsável por realizar a remoção de um elemento na estrutura do tipo especificado
bool set_remover(SET *s, int elemento) {
    if(s->tipo == 0)
        return avl_remover((AVL*)s->estrutura, elemento);
    else if(s->tipo == 1)
        return lista_remover((LISTA*)s->estrutura, elemento);  
}

// Função responsável por apagar a memória usada pela estrutura do tipo especificado
void set_apagar(SET **s) {
    if(s == NULL || *s == NULL)
        return;
    
    if((*s)->tipo == 0)
        avl_apagar((AVL **)&(*s)->estrutura);
    else if((*s)->tipo == 1)
        lista_apagar((LISTA**)&(*s)->estrutura);  
    
    free(*s);
}

// Função responsável por imprimir os itens da estrutura do tipo especificado
void set_imprimir(SET *s) {
    if(s->tipo == 0)
        avl_imprimir((AVL*)s->estrutura);
    else if(s->tipo == 1)
        lista_imprimir((LISTA*)s->estrutura);  
}

// Função responsável por realizar a operação de união entre 2 estruturas do tipo especificado
SET *set_uniao(SET *A, SET *B) {
    SET* uniao = (SET*)malloc(sizeof(SET));
    if(A->tipo == 0 && B->tipo == 0)
        uniao->estrutura = avl_uniao((AVL*)A->estrutura, (AVL*)B->estrutura);
    else if(A->tipo == 1 && B->tipo == 1)
        uniao->estrutura = lista_uniao((LISTA*)A->estrutura, (LISTA*)B->estrutura);  
        
    uniao->tipo = A->tipo;
    return uniao;
}

// Função responsável por realizar a operação de interseção entre 2 estruturas do tipo especificado
SET *set_interseccao(SET *A, SET *B) {
    SET* interseccao = (SET*)malloc(sizeof(SET));
    if(A->tipo == 0 && B->tipo == 0)
        interseccao->estrutura = avl_interseccao((AVL*)A->estrutura, (AVL*)B->estrutura);
    else if(A->tipo == 1 && B->tipo == 1)
        interseccao->estrutura = lista_interseccao((LISTA*)A->estrutura, (LISTA*)B->estrutura); 
        
    interseccao->tipo = A->tipo;
    return interseccao;
}