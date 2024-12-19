/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lista.h"

#ifndef STRUCTS_
    #define STRUCTS_

    // Define a struct lista
    struct lista_{ 
        int lista[TAM_MAX]; // Lista com TAM_MAX definido em 50000
        int inicio;         // index do inicio da lista
        int fim;            // index do fim da lista
        int tamanho;        // tamanho total da lista
    };
#endif

// Cria a lista
LISTA *lista_criar(void){
    LISTA *lista;

    // Aloca dinamicamente espaço para ela
    lista = (LISTA *) malloc(sizeof(LISTA));

    // Define os valores iniciais caso seja possível criar a lista
    if (lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        lista->tamanho = 0;
        return(lista);
    }
    return(NULL);
}

// Apaga a lista alocada da memória
void lista_apagar(LISTA **lista)
{
    if (*lista != NULL)
    {
        free(*lista);
        *lista = NULL;
    }
}

// Retorna o tamanho da lista
int lista_tamanho(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho);
    return(ERRO);
}

// Retorna se a lista se encontra vazia, verificando se seu tamanho é 0
bool lista_vazia(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho == 0);
    return(false);
}

// Retorna se a lista está cheia, verificando se alcançou seu tamanho máximo
bool lista_cheia(LISTA *lista){
    if (lista != NULL)
        return(lista->tamanho == TAM_MAX);
    return(false);
}

// Printa a lista com todos seus elementos a partir do seu index de inicio e o de fim
void lista_imprimir(LISTA *lista)
{
    for (int i = lista->inicio; i < lista->fim; i++)
        printf("%d ", (lista->lista[i]));
    printf("\n");
}

// Insere os valores já ordenados na lista
bool lista_inserir(LISTA *lista, int novo_elemento) {
    // Verifica se é possível inserir, verificando se a lista existe ou se está cheia
    if (lista == NULL || lista_cheia(lista))
        return false;

    // A lista não permite a inserção de elemntos duplicados, então verifica se certo elemento já pertence a lista antes de inserir,
    // caso já exista, simplesmente não irá inserir o valor
    if (lista_pertence(lista, novo_elemento))
        return false;

    // Inicia um processo de busca binária para procurar o lugar correto de se inserir o novo elemento
    int esquerda = lista->inicio;
    int direita = lista->fim - 1;
    int meio, posicao = lista->fim;

    // Dentro do while, vai verificando se é maior ou menor que o elemento do meio, e vai dividindo o tamanho do conjunto até encontrar
    // a posicao correta, um espaço onde o anterior é menor que o número a ser inserido e o próximo é maior
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;

        if (novo_elemento < lista->lista[meio]) {
            direita = meio - 1;
            posicao = meio;
        } else {
            esquerda = meio + 1;
        }
    }

    // Desloca os valores, "abrindo espaço" para o novo elemento
    for (int i = lista->fim; i > posicao; i--) {
        lista->lista[i] = lista->lista[i - 1];
    }

    // De fato, insere o novo elemente na lista na posicao encontrada pela busca binaria e aumenta em o index de seu ultimo termo e tamanho
    lista->lista[posicao] = novo_elemento;
    lista->fim++;
    lista->tamanho++;

    // Retorna true após conseguir com sucesso inserir o novo elemento
    return true;
}

// Remove certo elemento da lista com base em seu valor
bool lista_remover(LISTA *lista, int elemento)
{
    // Primeiramente se verifica condições iniciais que ocasionariam em uma falha da remoção
    // caso a lista seja nula, caso nao exista esse valor no conjunto ou caso a lista esteja vazia
    if (lista == NULL || !lista_pertence(lista, elemento) || lista_vazia(lista))
        return false;

    // Inicia um processo de busca binária para procurar o lugar correto de se remover o elemento, de maneira similar a inserção
    int esquerda = lista->inicio;
    int direita = lista->fim - 1;
    int meio;

    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        // Quando encontra o elemento, se prepara para deslocar os elementos para a esquerda e remover o elemento desejado
        if (lista->lista[meio] == elemento)
        {
            for (int i = meio; i < lista->fim - 1; i++)
                lista->lista[i] = lista->lista[i + 1];
            lista->fim--;  // Decrementa o fim da lista
            lista->tamanho--;  // Decrementa o tamanho
            return true;
        }
        // Caso não encontre o elemento, divide a lista pela metade para esquerda ou para esquerda, a depender do valor do elemento
        else if (elemento < lista->lista[meio])
            direita = meio - 1;
        else
            esquerda = meio + 1;
    }   
}

// Retorna o index do inicio da lista
int lista_obter_inicio(LISTA *lista) {
    return lista->inicio;
}

// Retorna o index do fim da lista
int lista_obter_fim(LISTA *lista) {
    return lista->fim;
}

// Retorna um elemento especifico com base em seu index
int lista_obter_elemento(LISTA *lista, int pos) {
    if (lista == NULL || pos < lista->inicio || pos >= lista->fim) {
        return -1;
    }
    return (lista->lista[pos]);
}

// Busca binária que verifica se certo elemento pertence ao conjunto
// Possui complexidade O(log n)
bool lista_pertence(LISTA *lista, int chave)
{
    // Verifica se a lista é nula ou se está vazia
    if (lista == NULL || lista_vazia(lista))
        return false;

    int esquerda = lista->inicio;
    int direita = lista->fim - 1;

    // Novamente, compara se a direita é maior que a esquerda, a ponto de busca de maneira binária o valor passado como parâmetro
    while (esquerda <= direita)
    {
        int meio = (esquerda + direita) / 2;

        // Caso a lista->lista[meio] seja igual a chave procurada, signfica que o elemento foi encontrado
        if ((lista->lista[meio]) == chave)
            return true;
        // Caso contrário, divide a lista para esquerda ou para direita, a depender de qual é o valor do elemento
        else if (chave < (lista->lista[meio]))
            direita = meio - 1;
        else
            esquerda = meio + 1;
    }

    // Caso não encontre, retorna false
    return false;
}

// Complexidade O(n + m) -> n representando ao conjunto 1 e m representando o conjunto 2
LISTA *lista_uniao(LISTA *c1, LISTA *c2) {
    // Verifica se algum dos conjuntos é nulo
    if (c1 == NULL || c2 == NULL)
        return NULL;

    // Cria a lista que será retornada ao final da funcao
    LISTA *uni = lista_criar();
    if (uni == NULL)
        return NULL;

    // Utiliza-se de dois índices para percorres simultaneamente as duas listas simultaneamente
    int i = c1->inicio;
    int j = c2->inicio;

    // Primeiramente se verifica se ambos os conjuntos não chegaram ao fim
    while (i < c1->fim && j < c2->fim) {
        // Verifica se o valor do conjunto1 no index i é menor que do conjunto2 no index j, uma vez que se busca ja inserir de maneira ordenada na união
        if (c1->lista[i] < c2->lista[j]) {
            // Insere o valor de c1 no index i no final do conjunto da união e incrementa em 1 tanto i, quanto o fim da uniao
            uni->lista[uni->fim++] = c1->lista[i++];
            uni->tamanho++; // Incrementa o tamanho do conjunto uniao
        } 
        // Verifica entao se é menor
        else if (c1->lista[i] > c2->lista[j]) {
            // Insere o valor de c2 no index j no final do conjunto da união e incrementa em 1 tanto j, quanto o fim da uniao
            uni->lista[uni->fim++] = c2->lista[j++];
            uni->tamanho++; // Incrementa o tamanho do conjunto uniao
        } 
        // Caso sejam iguais, adiciona apenas uma vez o elemento na uniao, mesmo que haja elementos iguais em ambos os conjuntos
        else {
            uni->lista[uni->fim++] = c1->lista[i++];
            uni->tamanho++;
            j++;
        }
    }

    // Caso apenas um dos conjuntos tenha acabado, apenas percorre eles separadamente, adicionando seus valores no conjunto da união
    while (i < c1->fim) {
        uni->lista[uni->fim++] = c1->lista[i++];
        uni->tamanho++;
    }

    while (j < c2->fim) {
        uni->lista[uni->fim++] = c2->lista[j++];
        uni->tamanho++;
    }

    // Retorna a uniao dos conjuntos
    return uni;
}


// Complexidade O(n + m) -> n representando ao conjunto 1 e m representando o conjunto 2
LISTA *lista_interseccao(LISTA *c1, LISTA *c2) {
    // verifica se algum dos conjuntos é nulo
    if (c1 == NULL || c2 == NULL)
        return NULL;

    // Cria a lista que sera retornada ao fim do programa
    LISTA *intersec = lista_criar();
    if (intersec == NULL)
        return NULL;

    // Utiliza-se de dois índices para percorrer simultaneamente as duas listas, assim como na união
    int i = c1->inicio;
    int j = c2->inicio;

    // Percorre até que ambos os vetores tenham chego ao seu fim
    while (i < c1->fim && j < c2->fim) {
        // Caso o valor de c1 no index i seja maior
        if (c1->lista[i] < c2->lista[j]) {
            i++; // Incrementa o indice do conjunto 1
        }
        // Caso seja menor
        else if (c1->lista[i] > c2->lista[j]) {
            j++; // Incrementa o indice do conjunto 2
        }
        // Caso sejam iguais, significa que houve uma interseção, portanto irá adicionar o valor encontrado coincidente dos dois conjuntos
        // no conjunto de interseção
        else {
            // Insere ao fim de intersecao o valor e incrementa 1 ao seu final, assim como ao indice i, j e o tamanho do conjunto intersec
            intersec->lista[intersec->fim++] = c1->lista[i++];
            intersec->tamanho++;
            j++;
        }
    }

    // Retrona o conjunto de intersecao
    return intersec;
}
