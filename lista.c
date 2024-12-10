#include "aresta.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef STRUCTS_
    #define STRUCTS_

    struct lista_{ 
        ARESTA *lista[TAM_MAX];
        int inicio;
        int fim;
        int tamanho;
    };
#endif

LISTA *lista_criar(void){
    LISTA *lista;

    lista = (LISTA *) malloc(sizeof(LISTA));

    if (lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        lista->tamanho = 0;
        return(lista);
    }
    return(NULL);
}

void lista_apagar(LISTA **lista){
    if (*lista != NULL){
        for(int i = (*lista)->inicio; i < (*lista)->fim; i++){
            aresta_apagar(&(*lista)->lista[i]);
        }

        free(*lista);
        *lista = NULL;
    }
}

int lista_tamanho(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho);
    return(ERRO);
}

bool lista_vazia(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho == 0);
    return(false);
}

bool lista_cheia(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho == TAM_MAX);
    return(false);
}

void lista_imprimir(LISTA *lista){
    if (lista != NULL){
        for(int i = lista->inicio; i < lista->fim; i++){
            printf("Origem: %d - ", aresta_get_origem(lista->lista[i]));
            printf("Destino: %d - ", aresta_get_destino(lista->lista[i]));
            printf("Tamanho: %d - ", aresta_get_distancia(lista->lista[i]));
            printf("Visitada?: %d - ", aresta_get_status(lista->lista[i]));
        }
    }
}

bool lista_inserir(LISTA *lista, ARESTA *aresta){
    if(lista_cheia(lista)){
        return false;
    }

    lista->lista[lista->fim] = aresta;
    lista->fim++;
    lista->tamanho++;

    return true;
}

ARESTA* lista_get_aresta(LISTA *lista, int or, int dest)
{
    for(int i = lista->inicio; i < lista->fim; i++)
    {
        if(aresta_get_origem(lista->lista[i]) == or && aresta_get_destino(lista->lista[i]) == dest)
            return lista->lista[i];
    }
}