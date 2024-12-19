/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
*/

#include <stdbool.h>

#ifndef LISTA_H
	#define LISTA_H

	#define TAM_MAX 50000
	#define ERRO -32000

	typedef struct lista_ LISTA;

    // Função responsável por criar a lista
	LISTA *lista_criar(void);

    // Função responsável por verificar se um elemento está na lista
	bool lista_pertence(LISTA *lista, int chave);

    // Função responsável por inserir um elemento na lista
	bool lista_inserir(LISTA *lista, int elemento);

    // Função responsável por remover um elemento da lista
	bool lista_remover(LISTA *lista, int elemento);

    // Função responsável por apagar a lista
	void lista_apagar(LISTA **lista);

    // Função responsável por imprimir os nós da lista
	void lista_imprimir(LISTA *lista);

    // Função responsável por fazer a união de 2 listas
	LISTA *lista_uniao(LISTA *c1, LISTA *c2);

    // Função responsável por fazer a intersecção entre 2 listas 
	LISTA *lista_interseccao(LISTA *c1, LISTA *c2);

#endif