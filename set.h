/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
  
Baseado no código disponibilizado pelo professor
*/

#ifndef _SET_H
#define _SET_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

  typedef struct set SET;

  // Função responsável por criar um set
  SET *set_criar(unsigned char tipo);

  // Função responsável por verificar se um elemento está em um set
  bool set_pertence(SET *A, int elemento);

  // Função responsável por inserir um elemento em um set
  bool set_inserir (SET *A, int elemento);

  // Função responsável por remover um elemento de um set
  bool set_remover(SET *A, int elemento);

  // Função responsável por apagar um set
  void set_apagar(SET **A);

  // Função responsável por imprimir os valores de um set
  void set_imprimir(SET *A);

  // Função responsável por fazer a união de 2 sets
  SET *set_uniao(SET *A, SET *B);

  // Função responsável por fazer a intersecção entre 2 sets 
  SET *set_interseccao(SET *A, SET *B);
  
#endif